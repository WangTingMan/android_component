#pragma once

#include "binder_client_proxy.h"
#include "grpc_data_link/message_define.h"
#include "data_link/server.h"

#include "protobuf/binder_driver_data_link.pb.h"
#include "protobuf/binder_driver_data_link.grpc.pb.h"

#include <grpcpp/server_builder.h>
#include <grpcpp/server.h>

#include <functional>
#include <memory>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <thread>
#include <vector>

namespace data_link
{

struct binder_servcer_callbacks
{
    std::function<void( std::string, connection_status )> client_status_changed;
    std::function<void( std::string, message_from_client )> new_message_from_client;
};

class binder_server : public server
{

public:

    binder_server();

    void listen_on
        (
        std::string a_address,
        bool a_accupy_current_thread
        ) override;

    void send_message( std::shared_ptr<binder_ipc_message> a_message ) override;

    void register_message_incoming_callback( message_callback a_callback ) override;

    void set_callbacks( binder_servcer_callbacks a_callback )
    {
        std::lock_guard<std::shared_mutex> locker( m_mutex );
        m_callbacks = a_callback;
    }

    void send_message( std::string, std::shared_ptr<message_from_server> );

    void start();

private:

    void start_internal( std::string a_address );

    void send_message_internal( std::string, std::shared_ptr <message_from_server> );

    void accept_new();

    void handle_client_porxy_status_changed( std::shared_ptr<binder_client_proxy>, connection_status );

    void handle_client_new_message( std::shared_ptr<binder_client_proxy>, BinderDriverDataLink::MessageFromClient& );

    void remove_client_proxy( std::shared_ptr<binder_client_proxy> a_proxy );

    std::unique_ptr<grpc::Server> m_rpc_server;
    BinderDriverDataLink::BinderDriverService::AsyncService m_detail_service;
    std::vector<std::shared_ptr<binder_client_proxy>> m_client_proxes;
    bool m_listening = false;

    std::shared_mutex m_mutex;
    binder_servcer_callbacks m_callbacks;
};

}
