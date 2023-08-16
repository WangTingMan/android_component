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

    void new_client_connected( new_client_callback a_new_client_callback ) override
    {
        std::lock_guard<std::shared_mutex> locker( m_mutex );
        m_new_client_callback = a_new_client_callback;
    }

    void start();

private:

    void start_internal( std::string a_address );

    void accept_new();

    void handle_client_porxy_status_changed( std::shared_ptr<binder_client_proxy>, connection_status );

    void remove_client_proxy( std::shared_ptr<binder_client_proxy> a_proxy );

    std::unique_ptr<grpc::Server> m_rpc_server;
    BinderDriverDataLink::BinderDriverService::AsyncService m_detail_service;
    std::vector<std::shared_ptr<binder_client_proxy>> m_client_proxes;
    bool m_listening = false;

    std::shared_mutex m_mutex;
    new_client_callback m_new_client_callback;
};

}
