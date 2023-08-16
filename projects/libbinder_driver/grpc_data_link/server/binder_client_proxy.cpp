#include "binder_client_proxy.h"
#include "grpc_data_link/tag_handler_manager.h"
#include "grpc_data_link/io_runner.h"

#include <log/log.h>

namespace data_link {

uint32_t connection_status_callback_control_block::s_next_id = 0;

connection_status_callback_control_block::connection_status_callback_control_block
    ( connection_status_callback a_cb )
    : m_callback( a_cb )
{
    m_id = s_next_id++;
}

binder_client_proxy::binder_client_proxy
    (
    BinderDriverDataLink::BinderDriverService::AsyncService& a_detail_service
    )
    : m_biddiraction_stream( &m_server_context )
    , m_detail_service( a_detail_service )
{

}

binder_client_proxy::~binder_client_proxy()
{
    unregister_all_tag_handlers();
}

void binder_client_proxy::start()
{
    if( m_connection_status != connection_status::disconnected )
    {
        ALOGW( "connection status is not disconnected. Reject start" );
        return;
    }

    create_tag_handler();

    m_server_context.AsyncNotifyWhenDone( (void*)( m_done_id ) );

    auto tq_ = server_io_runner::get_default_instance().get_server_detail_queue();
    m_detail_service.RequestBidirectionalStreamMessages
            ( &m_server_context, &m_biddiraction_stream,
              tq_, tq_, (void*)( m_start_id ) );

    m_connection_status = connection_status::connecting;
    ALOGI( "Start listen new remote client rpc calling" );
}

void binder_client_proxy::connect( std::string a_address )
{
    ALOGE( "client proxy not support connect action" );
}

void binder_client_proxy::send_message( std::shared_ptr<binder_ipc_message> a_message )
{
    server_io_runner::get_default_instance()
        .post_task( std::bind( &binder_client_proxy::async_send_biddirection_message, this, a_message ) );
}

connection_status binder_client_proxy::get_connection_status()
{
    std::lock_guard<std::mutex> loker( m_mutex );
    return m_connection_status;
}

void binder_client_proxy::terminate()
{
    unregister_all_tag_handlers();
}

void binder_client_proxy::async_send_biddirection_message( std::shared_ptr<binder_ipc_message> a_msg )
{
    if( m_connection_status != connection_status::connected )
    {
        ALOGE( "no connected, cannot send message." );
        return;
    }

    if( !m_message_sending )
    {
        BinderDriverDataLink::MessageFromServer msg;
        msg.set_msg( a_msg->to_string() );
        msg.set_id( a_msg->get_id() );
        // after invoke extract_raw_buffer, the raw data size member of binder_ipc_message
        // will change to zero. So we need generate the string first!!
        msg.set_buffer( std::move( a_msg->extract_raw_buffer() ) );
        msg.set_type( uint32_t( a_msg->get_type() ) );
        m_biddiraction_stream.Write( std::move( msg ), (void*)( m_write_done_id ) );
        m_message_sending = true;
    }
    else
    {
        m_msgs_to_send.push_back( std::move( a_msg ) );
    }
}

void binder_client_proxy::create_tag_handler()
{
    std::function<void( bool )> fun;
    uint64_t id = 0;

    if( m_write_done_id == 0 )
    {
        fun = std::bind( &binder_client_proxy::handle_message_write_done,
                         shared_from_this(), std::placeholders::_1 );
        id = tag_handler_manager::get_instance().register_tag_handler( fun );
        m_write_done_id = id;
    }

    if( m_done_id == 0 )
    {
        fun = std::bind( &binder_client_proxy::handle_request_done,
                         shared_from_this(), std::placeholders::_1 );
        id = tag_handler_manager::get_instance().register_tag_handler( fun );
        m_done_id = id;
    }

    if( m_start_id == 0 )
    {
        fun = std::bind( &binder_client_proxy::handle_request_start,
                         shared_from_this(), std::placeholders::_1 );
        id = tag_handler_manager::get_instance().register_tag_handler( fun );
        m_start_id = id;
    }

    if( m_read_come_id == 0 )
    {
        fun = std::bind( &binder_client_proxy::handle_request_message_read_come,
                         shared_from_this(), std::placeholders::_1 );
        id = tag_handler_manager::get_instance().register_tag_handler( fun );
        m_read_come_id = id;
    }
}

void binder_client_proxy::handle_request_done( bool ok )
{
    if( !ok )
    {
        ALOGD( "remote client called done with failed." );
        return;
    }

    ALOGI( "remote client called done." );
    change_to_new_status( connection_status::disconnected );
    unregister_all_tag_handlers();
}

void binder_client_proxy::handle_request_start( bool ok )
{
    if( !ok )
    {
        ALOGD( "streaming request started with false. not connected." );
        change_to_new_status( connection_status::disconnected );
        return;
    }

    m_peer = m_server_context.peer();
    ALOGI( "remote client from peer: %s", m_peer.c_str() );

    change_to_new_status( connection_status::connected );
    m_biddiraction_stream.Read( &m_read_msg, (void*)( m_read_come_id ) );
}

void binder_client_proxy::handle_request_message_read_come( bool ok )
{
    if( !ok )
    {
        ALOGD( "client disconnected when read streaming message." );
        change_to_new_status( connection_status::disconnected );
        return;
    }

    std::lock_guard<std::mutex> locker( m_mutex );

    if( m_message_callback )
    {
        std::shared_ptr<binder_ipc_message> msg;
        binder_message_type msg_type = static_cast< binder_message_type >( m_read_msg.type() );
        msg = create( msg_type );
        if( !msg )
        {
            ALOGE( "Unknown message type: %d", m_read_msg.type() );
            return;
        }
        msg->set_from_client( false );
        msg->set_endpoint( peer() );
        msg->set_id( m_read_msg.id() );
        msg->set_raw_buffer( std::move( m_read_msg.buffer() ) );
        msg->parse_from_message( m_read_msg.msg() );
        m_message_callback( msg );
    }

    m_biddiraction_stream.Read( &m_read_msg, (void*)( m_read_come_id ) );
}

void binder_client_proxy::handle_message_write_done( bool ok )
{
    m_message_sending = false;

    if( !ok )
    {
        ALOGD( "client disconnected when write streaming message." );
        change_to_new_status( connection_status::disconnected );
        return;
    }

    if( m_msg_to_send.empty() )
    {
        return;
    }

    async_send_biddirection_message( m_msgs_to_send.front() );
    m_msg_to_send.erase( m_msg_to_send.begin() );
}

void binder_client_proxy::unregister_all_tag_handlers()
{
    tag_handler_manager::get_instance().delete_tag_handler( m_read_come_id );
    tag_handler_manager::get_instance().delete_tag_handler( m_done_id );
    tag_handler_manager::get_instance().delete_tag_handler( m_start_id );
    tag_handler_manager::get_instance().delete_tag_handler( m_write_done_id );
    m_read_come_id = 0;
    m_done_id = 0;
    m_start_id = 0;
    m_write_done_id = 0;
}

void binder_client_proxy::change_to_new_status( connection_status a_status )
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
        m_server_context.TryCancel();
        ALOGD( "cancel server context." );
        break;
    case connection_status::disconnecting:
        break;
    }

    m_msg_to_send.clear();

    std::unique_lock<std::mutex> locker( m_mutex );
    auto cbs = m_connection_cbs;
    locker.unlock();

    for( auto& ele : cbs )
    {
        if( ele.m_callback )
        {
            ele.m_callback( shared_from_this(), m_connection_status );
        }
    }
}

}
