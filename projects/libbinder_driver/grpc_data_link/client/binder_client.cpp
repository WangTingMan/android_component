#include "binder_client.h"
#include "grpc_data_link/tag_handler_manager.h"
#include "grpc_data_link/io_runner.h"

#include <log/log.h>

namespace data_link
{

std::shared_ptr<client> client::make_one()
{
    return std::make_shared<binder_client>();
}

binder_client::binder_client()
{
    create_tag_handler();
    data_link::io_runner::get_default_instance().run( false );
}

binder_client::~binder_client()
{
    unregister_all_tag_handler();
}

void binder_client::connect( std::string a_address )
{
    auto fun = [this, a_address ]()mutable
    {
        if( m_connection_status != connection_status::disconnected )
        {
            ALOGE( "connection status is not disconnected, is %d", m_connection_status );
            return;
        }

        set_server_address( a_address );
        connect_internal();
    };
    io_runner::get_default_instance().post_task( fun );
}

void binder_client::send_message( std::shared_ptr<binder_ipc_message> a_message )
{
    std::string detail_message = a_message->to_string();
    std::shared_ptr<message_from_client> client_msg;
    client_msg = std::make_shared<message_from_client>();
    client_msg->id = a_message->get_id();
    client_msg->message = std::move( detail_message );
    client_msg->type = static_cast<uint32_t>( a_message->get_type() );
    if( a_message->get_raw_buffer_size() > 0 )
    {
        client_msg->raw_buffer = a_message->extract_raw_buffer();
    }

    send_message( client_msg );
}

void binder_client::register_message_incoming_callback( message_callback a_callback )
{
    std::function<void( std::shared_ptr<message_from_server> )> fun;
    fun = [a_callback]( std::shared_ptr<message_from_server> a_msg )
    {
        data_link::binder_message_type a_msg_type;
        a_msg_type = static_cast<data_link::binder_message_type>( a_msg->type );
        auto ipc_msg = data_link::create( a_msg_type, false );
        if( !ipc_msg )
        {
            return;
        }

        ipc_msg->set_id( a_msg->id );
        ipc_msg->set_from_client( false );
        ipc_msg->set_raw_buffer( std::move( a_msg->raw_buffer ) );
        bool ret = ipc_msg->parse_from_message( a_msg->message );
        if( !ret )
        {
            return;
        }

        a_callback( ipc_msg );
    };

    std::lock_guard<std::shared_mutex> lcker( m_mutex );
    m_callbacks.new_message_from_server = fun;
}

connection_status binder_client::get_connection_status()
{
    return m_connection_status;
}

void binder_client::send_message( std::shared_ptr<message_from_client> a_message )
{
    io_runner::get_default_instance().post_task(
        std::bind( &binder_client::send_message_internal, shared_from_this(), a_message ) );
}

void binder_client::connect()
{
    io_runner::get_default_instance().post_task(
        std::bind( &binder_client::connect_internal, shared_from_this() ) );
}

void binder_client::disconnect()
{
    m_client_context.TryCancel();
}

void binder_client::create_tag_handler()
{
    std::function<void( bool )> fun;
    if( m_connect_done_id == 0 )
    {
        fun = std::bind( &binder_client::handle_connected, this, std::placeholders::_1 );
        m_connect_done_id = tag_handler_manager::get_instance().register_tag_handler( fun );
    }

    if( m_disconnect_done_id == 0 )
    {
        fun = std::bind( &binder_client::handle_disconnected, this, std::placeholders::_1 );
        m_disconnect_done_id = tag_handler_manager::get_instance().register_tag_handler( fun );
    }

    if( m_read_done_id == 0 )
    {
        fun = std::bind( &binder_client::handle_message_read_done, this, std::placeholders::_1 );
        m_read_done_id = tag_handler_manager::get_instance().register_tag_handler( fun );
    }

    if( m_write_done_id == 0 )
    {
        fun = std::bind( &binder_client::handle_message_write_done, this, std::placeholders::_1 );
        m_write_done_id = tag_handler_manager::get_instance().register_tag_handler( fun );
    }
}

void binder_client::unregister_all_tag_handler()
{
    tag_handler_manager::get_instance().delete_tag_handler( m_write_done_id );
    tag_handler_manager::get_instance().delete_tag_handler( m_read_done_id );
    tag_handler_manager::get_instance().delete_tag_handler( m_disconnect_done_id );
    tag_handler_manager::get_instance().delete_tag_handler( m_connect_done_id );
    m_connect_done_id = 0;
    m_disconnect_done_id = 0;
    m_read_done_id = 0;
    m_write_done_id = 0;
}

void binder_client::connect_internal()
{
    if( connection_status::disconnected == m_connection_status )
    {
        if( !m_channel )
        {
            m_channel = grpc::CreateChannel( m_server_address, grpc::InsecureChannelCredentials() );
        }

        if( !m_stub )
        {
            m_stub = BinderDriverDataLink::BinderDriverService::NewStub( m_channel );
        }

        auto cq = io_runner::get_default_instance().get_detail_queue();
        if( !m_stream )
        {
            m_stream = m_stub->AsyncBidirectionalStreamMessages( &m_client_context,
                cq, ( void* )( m_connect_done_id ) );
        }
        change_to_new_status( connection_status::connecting );
    }
    else
    {
        ALOGE( "not disconnected status. reject connect." );
    }
}

void binder_client::send_message_internal( std::shared_ptr<message_from_client> a_message )
{
    if( m_connection_status != connection_status::connected )
    {
        ALOGE( "Not connected. Reject send message. dispatched message id: %d", a_message->id );
        return;
    }

    m_message_to_send.push_back( a_message );
    if( m_message_sending )
    {
        return;
    }

    send_next_message();
}

void binder_client::send_next_message()
{
    if( m_message_to_send.empty() )
    {
        return;
    }

    if( m_connection_status != connection_status::connected )
    {
        ALOGE( "Not connected. Reject send message." );
        return;
    }

    BinderDriverDataLink::MessageFromClient msg;
    auto msg_to_send = m_message_to_send.front();
    msg.set_id( msg_to_send->id );
    msg.set_buffer( msg_to_send->raw_buffer );
    msg.set_type( msg_to_send->type );
    msg.set_msg( msg_to_send->message );

    ALOGI( "send message with ID: %d", msg_to_send->id );
    m_message_sending = true;
    m_stream->Write( std::move(msg), (void*)( m_write_done_id ) );
    m_message_to_send.erase( m_message_to_send.begin() );
}

void binder_client::handle_connected( bool ok )
{
    if( ok )
    {
        ALOGD( "Connect server success." );
        change_to_new_status( connection_status::connected );
        m_stream->Finish( &m_status, (void*)( m_disconnect_done_id ) );
        m_stream->Read( &m_message_from_server, (void*)( m_read_done_id ) );
    }
    else
    {
        ALOGD( "Connect server failed." );
        // since grpc will start connect after connect failed automatically,
        // so we cannot change the connection status to disconnected here.
    }
}

void binder_client::handle_disconnected( bool ok )
{
    std::string error_str = m_status.error_message();
    ALOGW( "Connection broken. reason: %s", error_str.c_str() );
    change_to_new_status( connection_status::disconnected );
}

void binder_client::handle_message_read_done( bool ok )
{
    if( !ok )
    {
        ALOGE( "read callback with not ok." );
        change_to_new_status( connection_status::disconnected );
        return;
    }

    ALOGI( "Received message id = %d", m_message_from_server.id() );

    std::shared_lock<std::shared_mutex> locker( m_mutex );
    if( m_callbacks.new_message_from_server )
    {
        std::shared_ptr<message_from_server> msg_from_server;
        msg_from_server = std::make_shared<message_from_server>();
        msg_from_server->id = m_message_from_server.id();

        std::string* take_str = m_message_from_server.release_msg();
        if( take_str )
        {
            take_str->swap( msg_from_server->message );
        }

        std::string* take_buffer = m_message_from_server.release_buffer();
        if( take_buffer )
        {
            take_buffer->swap( msg_from_server->raw_buffer );
        }

        msg_from_server->type = m_message_from_server.type();

        m_callbacks.new_message_from_server( msg_from_server );
    }

    m_stream->Read( &m_message_from_server, (void*)( m_read_done_id ) );
}

void binder_client::handle_message_write_done( bool ok )
{
    if( !ok )
    {
        ALOGE( "write callback with not ok." );
        change_to_new_status( connection_status::disconnected );
        return;
    }

    m_message_sending = false;
    send_next_message();
}

void binder_client::change_to_new_status( connection_status a_status )
{
    if( m_connection_status == a_status )
    {
        return;
    }

    m_connection_status = a_status;

    switch( a_status )
    {
    case connection_status::connected:
        break;
    case connection_status::connecting:
        break;
    case connection_status::disconnected:
        m_client_context.TryCancel();
        ALOGD( "cancel server context." );
        break;
    case connection_status::disconnecting:
        break;
    }

    for( auto& ele : m_message_to_send )
    {
        ALOGI( "message dispatched with id: %d", ele->id );
    }

    m_message_to_send.clear();

    std::shared_lock<std::shared_mutex> locker( m_mutex );
    if( m_callbacks.connection_status_changed )
    {
        m_callbacks.connection_status_changed( m_connection_status );
    }
}

}

