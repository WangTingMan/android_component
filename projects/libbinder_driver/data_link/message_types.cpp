#include "message_types.h"
#include <json/json.h>

#include "linux/binder.h"
#include "ipc_connection_token.h"

#include "linux/binder_internal_control_block_mgr.h"

namespace data_link
{

std::atomic<uint64_t> binder_ipc_message::s_next_id{ 0 };

binder_ipc_message::binder_ipc_message( bool a_auto_incread_id )
{
    if( a_auto_incread_id )
    {
        m_id = s_next_id.fetch_add( 1 );
    }
    else
    {
        m_id = s_next_id;
    }

    m_source_connection_id = android::ipc_connection_token_mgr::get_instance()
        .get_local_connection_name();
}

void binder_ipc_message::fill_json_value( Json::Value& a_value )const noexcept
{
    a_value[s_m_is_from_service_manager_key.data()] = m_is_from_service_manager;
    a_value[s_end_point_key.data()] = m_endpoint;
    a_value[s_raw_buffer_size_key.data()] = m_raw_buffer_size;
    a_value[s_source_connection_id_key.data()] = m_source_connection_id;
    a_value[s_debug_info_key.data()] = m_debug_info;
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

    value = a_value[static_cast<std::string>( s_source_connection_id_key )];
    m_source_connection_id = value.asString();
    if( m_source_connection_id.empty() )
    {
        is_success = false;
    }

    if( is_success )
    {
        value = a_value[static_cast<std::string>( s_raw_buffer_size_key )];
        m_raw_buffer_size = value.asUInt();
    }

    value = a_value[static_cast< std::string >( s_debug_info_key )];
    m_debug_info = value.asString();

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

std::string binder_transaction_message::state_to_string( binder_transaction_message::transaction_state a_state )
{
    switch( a_state )
    {
    case transaction_state::init:
        return "init";
    case transaction_state::handling:
        return "handling";
    case transaction_state::completed:
        return "completed";
    }
    return "unknown";
}

void binder_transaction_message::fill_json_value( Json::Value& a_value )const noexcept
{
    binder_ipc_message::fill_json_value( a_value );
    a_value[s_tr_code_key.data()] = m_tr_code;
    a_value[s_tr_data_ptr_offsets_key.data()] = m_tr_data_ptr_offsets;
    a_value[s_tr_offsets_size_key.data()] = m_tr_offsets_size;
    a_value[s_is_reply_key.data()] = m_is_reply;
    a_value[s_transaction_state_key.data()] = ( uint32_t )m_transaction_state;
    a_value[s_tr_service_name_key.data()] = m_tr_service_name;
    return;
}

bool binder_transaction_message::parse_from_json( Json::Value& a_value )
{
    bool is_success = binder_ipc_message::parse_from_json( a_value );
    if( !is_success )
    {
        return is_success;
    }

    Json::Value& value = a_value[static_cast<std::string>( s_tr_code_key )];
    m_tr_code = value.asUInt();

    value = a_value[static_cast<std::string>( s_tr_data_ptr_offsets_key )];
    m_tr_data_ptr_offsets = value.asUInt();

    value = a_value[static_cast<std::string>( s_tr_offsets_size_key )];
    m_tr_offsets_size = value.asUInt();

    value = a_value[static_cast<std::string>( s_is_reply_key )];
    m_is_reply = value.asBool();

    value = a_value[static_cast<std::string>( s_transaction_state_key )];
    m_transaction_state = (transaction_state)( value.asUInt() );

    value = a_value[static_cast< std::string >( s_tr_service_name_key )];
    m_tr_service_name = value.asString();

    is_success = true;
    return is_success;
}

void binder_transaction_message::init_transaction_context( binder_transaction_data* a_binder_transaction_data )
{
    std::string buffer;
    buffer.resize( a_binder_transaction_data->data_size );
    memcpy( buffer.data(), (void*)( a_binder_transaction_data->data.ptr.buffer ),
            a_binder_transaction_data->data_size );
    set_raw_buffer( std::move( buffer ) );

    m_tr_code = a_binder_transaction_data->code;
    m_tr_offsets_size = a_binder_transaction_data->offsets_size;
    m_tr_data_ptr_offsets = a_binder_transaction_data->data.ptr.offsets;
    m_tr_service_name.assign( a_binder_transaction_data->service_name );
    set_connection_name( a_binder_transaction_data->source_connection_name );
    set_id( a_binder_transaction_data->current_transaction_message_id );
}

void binder_transaction_message::parse_transaction_context( binder_transaction_data* a_binder_transaction_data )
{
    char* ping_buffer = nullptr;
    uint32_t raw_buffer_size = get_raw_buffer_size();
    ping_buffer = binder_internal_control_block_mgr::get_instance().get_buffer(
        raw_buffer_size + 1 );
    std::string raw_buffer = extract_raw_buffer();
    memcpy( ping_buffer, raw_buffer.data(), raw_buffer_size );

    a_binder_transaction_data->data.ptr.buffer = (binder_uintptr_t)( ping_buffer );
    a_binder_transaction_data->data_size = raw_buffer_size;
    a_binder_transaction_data->code = m_tr_code;
    a_binder_transaction_data->offsets_size = m_tr_offsets_size;
    a_binder_transaction_data->data.ptr.offsets = m_tr_offsets_size;
    if( m_tr_service_name.size() < MAX_SERVICE_NAME_SIZE )
    {
        strcpy_s( a_binder_transaction_data->service_name, m_tr_service_name.c_str() );
        a_binder_transaction_data->target.binder_handle = 0;
    }

    std::string connection_name = get_source_connection_id();
    if( connection_name.size() < MAX_CONNECTION_NAME_SIZE )
    {
        strcpy_s( a_binder_transaction_data->source_connection_name, connection_name.c_str() );
    }

    a_binder_transaction_data->current_transaction_message_id = get_id();
}

std::shared_ptr<binder_ipc_message> create( binder_message_type a_msg_type, bool a_auto_incread_id )
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
    case binder_message_type::binder_transaction:
        ret = std::make_shared<binder_transaction_message>( a_auto_incread_id );
        break;
    default:
        break;
    }
    return ret;
}


}


