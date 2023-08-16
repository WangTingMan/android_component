#pragma once
#include "grpc_data_link/message_define.h"
#include "protobuf/binder_driver_data_link.pb.h"
#include "protobuf/binder_driver_data_link.grpc.pb.h"
#include "data_link/message_types.h"
#include "data_link/client.h"

#include <grpcpp/server_builder.h>
#include <grpcpp/server.h>
#include <grpcpp/create_channel.h>

#include <functional>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>
#include <shared_mutex>

namespace data_link
{

struct binder_client_callbacks
{
    std::function<void(connection_status)> connection_status_changed;
    std::function<void( std::shared_ptr<message_from_server> )> new_message_from_server;
};

class binder_client : public client, public std::enable_shared_from_this<binder_client>
{

public:

    binder_client();

    ~binder_client();

    void connect( std::string a_address ) override;

    void send_message( std::shared_ptr<binder_ipc_message> a_message ) override;

    void register_message_incoming_callback( message_callback a_callback ) override;

    connection_status get_connection_status() override;

    void register_connection_status_callback( std::function<void( connection_status )> a_callback ) override
    {
        std::lock_guard<std::shared_mutex> lcker( m_mutex );
        m_callbacks.connection_status_changed = a_callback;
    }

    void send_message( std::shared_ptr<message_from_client> );

    void connect();

    void disconnect();

    void set_server_address( std::string a_address )
    {
        std::lock_guard<std::shared_mutex> lcker( m_mutex );
        m_server_address = a_address;
    }

    void set_callbacks( binder_client_callbacks a_callbacks )
    {
        std::lock_guard<std::shared_mutex> lcker( m_mutex );
        m_callbacks = a_callbacks;
    }

private:

    void unregister_all_tag_handler();

    void connect_internal();

    void send_message_internal( std::shared_ptr<message_from_client> );

    void create_tag_handler();

    void send_next_message();

    void handle_connected( bool ok );

    void handle_disconnected( bool ok );

    void handle_message_read_done( bool ok );

    void handle_message_write_done( bool ok );

    void change_to_new_status( connection_status a_status );

    grpc::ClientContext m_client_context;
    std::shared_ptr<grpc::Channel> m_channel;
    std::unique_ptr<BinderDriverDataLink::BinderDriverService::Stub> m_stub;
    std::unique_ptr<grpc::ClientAsyncReaderWriter
        <BinderDriverDataLink::MessageFromClient,
        BinderDriverDataLink::MessageFromServer>> m_stream;
    grpc::Status m_status;
    BinderDriverDataLink::MessageFromServer m_message_from_server;
    uint64_t m_connect_done_id = 0;
    uint64_t m_disconnect_done_id = 0;
    uint64_t m_read_done_id = 0;
    uint64_t m_write_done_id = 0;
    bool m_message_sending = false;
    connection_status m_connection_status = connection_status::disconnected;
    std::vector<std::shared_ptr<message_from_client>> m_message_to_send;

    std::shared_mutex m_mutex;
    binder_client_callbacks m_callbacks;
    std::string m_server_address;
};

}
