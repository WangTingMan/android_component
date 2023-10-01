#pragma once
#include <atomic>
#include <memory>
#include <mutex>
#include <vector>

#include "protobuf/binder_driver_data_link.pb.h"
#include "protobuf/binder_driver_data_link.grpc.pb.h"
#include "grpc_data_link/message_define.h"
#include "data_link/message_types.h"

#include <grpcpp/server_builder.h>
#include <grpcpp/server.h>
#include <data_link/client.h>

namespace data_link {

class binder_client_proxy;

using connection_status_callback = std::function<void( std::shared_ptr<binder_client_proxy>, connection_status )>;

struct connection_status_callback_control_block
{
    connection_status_callback_control_block( connection_status_callback a_cb );

    connection_status_callback m_callback;
    uint32_t m_id = 0;
    static uint32_t s_next_id;
};

class binder_client_proxy : public client, public std::enable_shared_from_this<binder_client_proxy>
{

public:

    using new_message_callback = std::function<void( std::shared_ptr<binder_client_proxy>, BinderDriverDataLink::MessageFromClient& )>;

    binder_client_proxy
        (
        BinderDriverDataLink::BinderDriverService::AsyncService& a_detail_service
        );

    ~binder_client_proxy();

    void start();

    void connect( std::string a_address ) override;

    void send_message( std::shared_ptr<binder_ipc_message> a_message ) override;

    connection_status get_connection_status()override;

    void register_connection_status_callback( std::function<void( connection_status )> a_callback )override
    {
        auto fun = [a_callback]( std::shared_ptr<binder_client_proxy>, connection_status a_status )
        {
            a_callback( a_status );
        };

        return register_connection_callback( fun );
    }

    void register_message_incoming_callback( message_callback a_callback )override
    {
        std::lock_guard<std::mutex> locker( m_mutex );
        m_message_callback = a_callback;
    }

    void terminate();

    void async_send_biddirection_message( std::shared_ptr<binder_ipc_message> a_msg );

    void register_connection_callback( connection_status_callback a_callback )
    {
        connection_status_callback_control_block cb( a_callback );
        std::lock_guard<std::mutex> locker( m_mutex );
        m_connection_cbs.push_back( connection_status_callback_control_block( a_callback ) );
    }

    std::string peer()
    {
        return m_server_context.peer();
    }

private:

    void create_tag_handler();

    void handle_request_done( bool ok );

    void handle_request_start( bool ok );

    void handle_request_message_read_come( bool ok );

    void handle_message_write_done( bool ok );

    void unregister_all_tag_handlers();

    void change_to_new_status( connection_status a_status );

    using bid_stream = grpc::ServerAsyncReaderWriter<BinderDriverDataLink::MessageFromServer,
                            BinderDriverDataLink::MessageFromClient>;

    BinderDriverDataLink::BinderDriverService::AsyncService& m_detail_service;
    grpc::ServerContext m_server_context;
    bid_stream m_biddiraction_stream;

    BinderDriverDataLink::MessageFromClient m_read_msg;
    uint64_t m_read_come_id = 0;
    uint64_t m_done_id = 0;
    uint64_t m_start_id = 0;
    uint64_t m_write_done_id = 0;
    std::string m_peer;
    bool m_message_sending = false;
    std::vector<std::shared_ptr<binder_ipc_message>> m_msgs_to_send;

    std::mutex m_mutex;
    connection_status m_connection_status = connection_status::disconnected;
    std::vector<connection_status_callback_control_block> m_connection_cbs;
    message_callback m_message_callback;
};

}

