#pragma once
#include <atomic>
#include <memory>

#include "protobuf/binder_driver_data_link.pb.h"
#include "protobuf/binder_driver_data_link.grpc.pb.h"
#include "grpc_data_link/message_define.h"
#include "data_link/message_types.h"

#include <grpcpp/server_builder.h>
#include <grpcpp/server.h>

namespace data_link {

class binder_client_proxy;

struct client_proxy_callbacks
{
    std::function<void(std::shared_ptr<binder_client_proxy>, connection_status )> connection_status_changed;
    std::function<void(std::shared_ptr<binder_client_proxy>, BinderDriverDataLink::MessageFromClient&)> new_message_come;
};

class binder_client_proxy : public std::enable_shared_from_this<binder_client_proxy>
{

public:

    binder_client_proxy
        (
        BinderDriverDataLink::BinderDriverService::AsyncService& a_detail_service
        );

    ~binder_client_proxy();

    void start();

    void terminate();

    void async_send_biddirection_message( BinderDriverDataLink::MessageFromServer a_msg );

    void register_callbacks( client_proxy_callbacks a_callbacks )
    {
        m_callbacks = a_callbacks;
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
    connection_status m_connection_status = connection_status::disconnected;
    uint64_t m_read_come_id = 0;
    uint64_t m_done_id = 0;
    uint64_t m_start_id = 0;
    uint64_t m_write_done_id = 0;
    std::string m_peer;
    bool m_message_sending = false;
    std::vector<BinderDriverDataLink::MessageFromServer> m_msg_to_send;
    client_proxy_callbacks m_callbacks;
};

}

