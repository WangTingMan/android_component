#include "message_types.h"
#include <json/json.h>
namespace data_link
{

std::atomic<uint64_t> binder_ipc_message::s_next_id{ 0 };

binder_ipc_message::binder_ipc_message()
{
    m_id = s_next_id.fetch_add( 1 );
}

void binder_ipc_message::fill_json_value( Json::Value& a_value )const noexcept
{
    a_value[s_m_is_from_service_manager_key.data()] = m_is_from_service_manager;
    a_value[s_end_point_key.data()] = m_endpoint;
    a_value[s_raw_buffer_size.data()] = m_raw_buffer_size;
}

bool binder_ipc_message::parse_from_json( Json::Value& a_value )
{
    bool is_success = true;
    Json::Value& value = a_value[static_cast<std::string>( s_m_is_from_service_manager_key )];
    if( !value.isNull() )
    {
        m_is_from_service_manager = value.asBool();
    }
    else
    {
        return false;
    }

    if( m_endpoint.empty() )
    {
        value = a_value[static_cast< std::string >( s_end_point_key )];
        m_endpoint = value.asString();
        if( m_endpoint.empty() )
        {
            is_success = false;
        }
    }

    if( is_success )
    {
        value = a_value[static_cast<std::string>( s_raw_buffer_size )];
        m_raw_buffer_size = value.asUInt();
    }

    return is_success;
}

bool binder_ipc_message::parse_from_message( std::string const& a_msg )
{
    bool ret = false;
    Json::Reader reader;
    Json::Value value;
    ret = reader.parse( a_msg, value, false );
    if( !ret )
    {
        return ret;
    }

    ret = parse_from_json( value );
    return ret;
}

std::string binder_ipc_message::to_string()
{
    Json::Value value;
    Json::StreamWriterBuilder builder;
    builder["indentation"] = " ";
    fill_json_value( value );
    std::string json_str;
    json_str = Json::writeString( builder, value );
    return json_str;
}

void binder_ping_message::fill_json_value( Json::Value& a_value )const noexcept
{
    binder_ipc_message::fill_json_value( a_value );
    a_value[s_ping_message_key.data()] = m_ping_message;
}

bool binder_ping_message::parse_from_json( Json::Value& a_value )
{
    bool is_success = binder_ipc_message::parse_from_json( a_value );
    if( !is_success )
    {
        return is_success;
    }

    Json::Value& value = a_value[static_cast<std::string>( s_ping_message_key )];
    m_ping_message = value.asString();
    if( m_ping_message.empty() )
    {
        is_success = false;
        return is_success;
    }
    return is_success;
}

void register_service_message::fill_json_value( Json::Value& a_value )const noexcept
{
    binder_ipc_message::fill_json_value( a_value );
    a_value[s_service_name_key.data()] = m_service_name;
    a_value[s_register_result_key.data()] = m_register_result;
    return;
}

bool register_service_message::parse_from_json( Json::Value& a_value )
{
    bool is_success = binder_ipc_message::parse_from_json( a_value );
    if( !is_success )
    {
        return is_success;
    }

    Json::Value& value = a_value[static_cast<std::string>( s_service_name_key )];
    m_service_name = value.asString();
    if( m_service_name.empty() )
    {
        is_success = false;
        return is_success;
    }

    value = a_value[static_cast<std::string>( s_register_result_key )];
    m_register_result = value.asUInt();
    is_success = true;
    return is_success;
}

std::shared_ptr<binder_ipc_message> create( binder_message_type a_msg_type )
{
    std::shared_ptr<binder_ipc_message> ret;
    switch( a_msg_type )
    {
    case data_link::binder_message_type::invalid:
        break;
    case data_link::binder_message_type::ping_service_manager:
        ret = std::make_shared<binder_ping_message>();
        break;
    case binder_message_type::register_service:
        ret = std::make_shared<register_service_message>();
        break;
    default:
        break;
    }
    return ret;
}


}


