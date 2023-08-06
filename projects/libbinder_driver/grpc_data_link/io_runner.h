#pragma once

#include <grpcpp/server_builder.h>
#include <grpcpp/server.h>
#include <grpcpp/create_channel.h>

#include <chrono>
#include <functional>

namespace data_link
{

class abstract_io_runner
{

public:

    virtual ~abstract_io_runner();

    virtual grpc::CompletionQueue* get_detail_queue() = 0;

    void run( bool a_occupy_current_thread = true );

    void post_task( std::function<void()> );

    void post_delay_task
        (
        std::function<void()>,
        std::chrono::milliseconds
        );

protected:

    void running_detail();

private:

    std::thread m_running_thread;
};

class io_runner : public abstract_io_runner
{

public:

    io_runner();

    static io_runner& get_default_instance();

    grpc::CompletionQueue* get_detail_queue() override
    {
        return &m_running_queue;
    }

private:

    grpc::CompletionQueue m_running_queue;
};

class server_io_runner : public abstract_io_runner
{

public:

    server_io_runner();

    static server_io_runner& get_default_instance();

    grpc::CompletionQueue* get_detail_queue() override
    {
        return m_server_task_queue.get();
    }

    grpc::ServerCompletionQueue* get_server_detail_queue()
    {
        return m_server_task_queue.get();
    }

    grpc::ServerBuilder& get_server_builder()
    {
        return m_service_builder;
    }

private:

    std::unique_ptr<grpc::ServerCompletionQueue> m_server_task_queue;
    grpc::ServerBuilder m_service_builder;
};

}
