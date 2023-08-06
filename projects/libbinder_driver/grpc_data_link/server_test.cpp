#include "server_test.h"
#include "io_runner.h"

#include <log/log.h>

#include "server/binder_server.h"
#include "client/binder_client.h"

#include <thread>
#include <iostream>
#include <chrono>
#include <vector>

std::shared_ptr<data_link::binder_client> client;
uint64_t id = 1;

struct client_cb
{
    std::string peer_str;
    uint64_t id = 1;
};

std::shared_ptr<data_link::binder_server> server;
std::vector<client_cb> client_cbs;

void send_message_to_client( std::string a_client_peer, std::string a_message )
{
    std::shared_ptr<data_link::message_from_server> msg;
    msg = std::make_shared<data_link::message_from_server>();
    msg->id = 1;
    msg->message = a_message;
    server->send_message( a_client_peer, msg );
}

void client_connection_status_changed_server( std::string a_client_peer, data_link::connection_status a_status )
{
    auto it = client_cbs.begin();
    for( ; it != client_cbs.end(); ++it )
    {
        if( it->peer_str == a_client_peer )
        {
            break;
        }
    }

    if( a_status == data_link::connection_status::disconnected )
    {
        client_cbs.erase( it );
        return;
    }

    if( it == client_cbs.end() )
    {
        client_cb cb;
        cb.peer_str = a_client_peer;
        client_cbs.push_back( cb );
        it = client_cbs.end();
        it--;
    }

    if( a_status == data_link::connection_status::connected )
    {
        std::string msg_str( "Message from server. id: " );
        msg_str.append( std::to_string( it->id++ ) );
        send_message_to_client( a_client_peer, msg_str );
    }
}

void message_from_client( std::string a_client_peer, data_link::message_from_client a_message )
{
    ALOGD( "Received message from %s, message: %s",
           a_client_peer.c_str(), a_message.message.c_str() );

    auto it = client_cbs.begin();
    for( ; it != client_cbs.end(); ++it )
    {
        if( it->peer_str == a_client_peer )
        {
            break;
        }
    }

    if( it != client_cbs.end() )
    {
        std::string msg_str( "Message from server. id: " );
        msg_str.append( std::to_string( it->id++ ) );
        send_message_to_client( a_client_peer, msg_str );
    }
}

static void server_test_()
{
    server = std::make_shared<data_link::binder_server>();
    server->start();

    data_link::binder_servcer_callbacks cbs;
    cbs.client_status_changed = std::bind( &client_connection_status_changed_server, std::placeholders::_1, std::placeholders::_2 );
    cbs.new_message_from_client = std::bind( &message_from_client, std::placeholders::_1, std::placeholders::_2 );
    server->set_callbacks( cbs );
    data_link::server_io_runner::get_default_instance().run( true );
}

void client_connection_status_changed( data_link::connection_status a_status )
{
    if( a_status == data_link::connection_status::connected )
    {
        data_link::io_runner::get_default_instance().post_delay_task(
            []()
            {
                std::shared_ptr<data_link::message_from_client> msg;
                msg = std::make_shared<data_link::message_from_client>();
                msg->id = id++;
                std::string msg_str( "Message from client. id: " );
                msg_str.append( std::to_string( msg->id ) );
                msg->message = msg_str;
                if( client )
                {
                    client->send_message( msg );
                }
            },
            std::chrono::seconds(1)
        );
    }
}

void client_receive_message_from_server( std::shared_ptr<data_link::message_from_server> a_message )
{
    data_link::io_runner::get_default_instance().post_delay_task(
        []()
        {
            std::shared_ptr<data_link::message_from_client> msg;
            msg = std::make_shared<data_link::message_from_client>();
            msg->id = id++;
            std::string msg_str( "Message from client. id: " );
            msg_str.append( std::to_string( msg->id ) );
            msg->message = msg_str;
            if( client )
            {
                client->send_message( msg );
            }
        },
        std::chrono::seconds( 1 )
        );

    ALOGD( "Message from server: %s", a_message->message.c_str() );
}

static void client_test_()
{
    client = std::make_shared<data_link::binder_client>();
    data_link::binder_client_callbacks cbs;
    cbs.connection_status_changed = std::bind( &client_connection_status_changed, std::placeholders::_1 );
    cbs.new_message_from_server = std::bind( &client_receive_message_from_server, std::placeholders::_1 );
    client->set_callbacks( cbs );

    client->connect();

    data_link::io_runner::get_default_instance().run( false );

    std::this_thread::sleep_for( std::chrono::seconds( 10 ) );
    client.reset();
}

#ifdef __cplusplus
extern "C" {
#endif

void server_start_test()
{
    server_test_();
}

void client_start_test()
{
    client_test_();
}

#ifdef __cplusplus
} // extern "C"
#endif
