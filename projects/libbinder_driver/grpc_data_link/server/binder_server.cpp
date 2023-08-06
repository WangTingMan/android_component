#include "binder_server.h"
#include "grpc_data_link/tag_handler_manager.h"  
#include "grpc_data_link/io_runner.h"

#include <log/log.h>

namespace data_link
{

std::shared_ptr<server> server::make_one()
{
    return std::make_shared<binder_server>();
}

binder_server::binder_server()
{
}

void binder_server::listen_on
    (
    std::string a_address,
    bool a_accupy_current_thread
    )
{
    server_io_runner::get_default_instance().post_task
        (
        std::bind( &binder_server::start_internal, this, a_address )
        );

    data_link::server_io_runner::get_default_instance().run( a_accupy_current_thread );
}

void binder_server::send_message( std::shared_ptr<binder_ipc_message> a_message )
{
    if( !a_message )
    {
        ALOGE( "empty message!" );
        return;
    }

    std::shared_ptr<message_from_server> msg;
    msg = std::make_shared<message_from_server>();
    msg->id = a_message->get_id();
    msg->message = a_message->to_string();
    msg->type = static_cast< uint32_t >( a_message->get_type() );
    msg->raw_buffer = a_message->extract_raw_buffer();

    send_message( a_message->get_endpoint(), msg );
}

void binder_server::register_message_incoming_callback( message_callback a_callback )
{
    std::function<void(std::string, message_from_client)> fun;
    fun = [ a_callback ]( std::string a_client, message_from_client a_msg )
    {
        std::shared_ptr<binder_ipc_message> msg;
        binder_message_type msg_type = static_cast<binder_message_type>( a_msg.type );
        msg = create( msg_type );
        if( !msg )
        {
            ALOGE( "Unknown message type: %d", a_msg.type );
            return;
        }
        msg->set_from_client( false );
        msg->set_endpoint( a_client );
        msg->set_id( a_msg.id );
        msg->set_raw_buffer( std::move( a_msg.raw_buffer ) );
        msg->parse_from_message( a_msg.message );
        a_callback( msg );
    };

    std::lock_guard<std::shared_mutex> locker( m_mutex );
    m_callbacks.new_message_from_client = fun;
}

void binder_server::send_message( std::string a_peer, std::shared_ptr<message_from_server> a_msg )
{
    if( a_msg )
    {
        server_io_runner::get_default_instance().post_task
            (
            std::bind( &binder_server::send_message_internal,
                       this, a_peer, a_msg )
            );
    }
}

void binder_server::start()
{
    server_io_runner::get_default_instance().post_task
        (
        std::bind( &binder_server::start_internal, this, std::string() )
        );
}

void binder_server::start_internal( std::string a_address )
{
    if( !a_address.empty() )
    {
        ALOGD( "binder server listen on: %s", a_address.c_str() );
        server_io_runner::get_default_instance().get_server_builder()
            .AddListeningPort( a_address, grpc::InsecureServerCredentials() );
    }

    server_io_runner::get_default_instance().get_server_builder().RegisterService( &m_detail_service );
    m_rpc_server = server_io_runner::get_default_instance().get_server_builder().BuildAndStart();
    if( !m_rpc_server )
    {
        // Build and start failed.
        ALOGF( "Cannot build server!" );
        return;
    }

    accept_new();
    ALOGD( "grpc server started." );

}

void binder_server::send_message_internal
    (
    std::string a_client,
    std::shared_ptr<message_from_server> a_message
    )
{
    for( auto& ele : m_client_proxes )
    {
        if( ele->peer() == a_client )
        {
            BinderDriverDataLink::MessageFromServer msg;
            msg.set_id( a_message->id );
            msg.set_buffer( std::move( a_message->raw_buffer ) );
            msg.set_type( a_message->type );
            msg.set_msg( std::move( a_message->message ) );

            ele->async_send_biddirection_message( msg );
        }
    }
}

void binder_server::accept_new()
{
    if( m_listening )
    {
        ALOGD( "Already listen new one client." );
        return;
    }

    std::shared_ptr<binder_client_proxy> proxy;
    proxy = std::make_shared<binder_client_proxy>( m_detail_service );
    m_client_proxes.push_back( proxy );
    client_proxy_callbacks callbacks;
    callbacks.connection_status_changed = std::bind( &binder_server::handle_client_porxy_status_changed,
                                       this, std::placeholders::_1, std::placeholders::_2 );
    callbacks.new_message_come = std::bind( &binder_server::handle_client_new_message,
                                            this, std::placeholders::_1, std::placeholders::_2 );
    proxy->register_callbacks( callbacks );

    proxy->start();
    m_listening = true;
}

void binder_server::handle_client_porxy_status_changed
    (
    std::shared_ptr<binder_client_proxy> a_proxy,
    connection_status a_status
    )
{
    std::string peer = a_proxy->peer();
    switch( a_status )
    {
    case data_link::connection_status::disconnected:
        server_io_runner::get_default_instance().post_task
            (
            std::bind( &binder_server::remove_client_proxy, this, a_proxy )
            );
        accept_new();
        break;
    case data_link::connection_status::connecting:
        break;
    case data_link::connection_status::connected:
        m_listening = false;
        accept_new();
        break;
    case data_link::connection_status::disconnecting:
        break;
    default:
        break;
    }

    std::shared_lock<std::shared_mutex> locker( m_mutex );
    if( m_callbacks.client_status_changed )
    {
        m_callbacks.client_status_changed( peer, a_status );
    }

}

void binder_server::handle_client_new_message
    (
    std::shared_ptr<binder_client_proxy> a_proxy,
    BinderDriverDataLink::MessageFromClient& a_message
    )
{
    message_from_client client_message;
    client_message.id = a_message.id();
    client_message.message = a_message.msg();
    client_message.type = a_message.type();
    client_message.raw_buffer = a_message.buffer();

    std::shared_lock<std::shared_mutex> locker( m_mutex );
    if( m_callbacks.new_message_from_client )
    {
        m_callbacks.new_message_from_client( a_proxy->peer(), client_message );
    }
    else
    {
        ALOGE( "No message callback registered!" );
    }
}

void binder_server::remove_client_proxy( std::shared_ptr<binder_client_proxy> a_proxy )
{
    for( auto it = m_client_proxes.begin(); it != m_client_proxes.end(); ++it )
    {
        if( *it == a_proxy )
        {
            m_client_proxes.erase( it );
        }
        break;
    }
}

}

