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
    proxy->register_connection_callback( std::bind( &binder_server::handle_client_porxy_status_changed,
        this, std::placeholders::_1, std::placeholders::_2 ) );

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
        {
            std::shared_lock<std::shared_mutex> locker( m_mutex );
            if( m_new_client_callback )
            {
                m_new_client_callback( a_proxy );
            }
        }
        break;
    case data_link::connection_status::disconnecting:
        break;
    default:
        break;
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

