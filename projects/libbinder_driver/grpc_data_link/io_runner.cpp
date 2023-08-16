#include "io_runner.h"
#include "tag_handler_manager.h"

#include <chrono>

#include <log/log.h>
#include <base/threading/platform_thread.h>

#include <grpcpp/alarm.h>
#include <grpc/impl/codegen/log.h>

namespace
{

void gpr_log_func_( gpr_log_func_args* args )
{
    android_LogPriority severity = ANDROID_LOG_VERBOSE;
    switch( args->severity )
    {
    case GPR_LOG_SEVERITY_ERROR:
        severity = ANDROID_LOG_FATAL;
        break;
    case GPR_LOG_SEVERITY_INFO:
        severity = ANDROID_LOG_INFO;
        break;
    case GPR_LOG_SEVERITY_DEBUG:
        severity = ANDROID_LOG_DEBUG;
        break;
    default:
        return;
    }

    __log_format( severity, "", args->file, "", args->line, args->message );
}

struct runner_task_wrapper_control_block
{
    std::function<void()> detail_task;
    uint64_t tag_id = 0;
    std::shared_ptr<grpc::Alarm> alarm;
};

void io_runner_task_wrapper
    (
    std::shared_ptr<runner_task_wrapper_control_block> a_cb,
    bool ok
    )
{
    if( a_cb->alarm )
    {
        a_cb->alarm->Cancel();
    }

    if( !a_cb )
    {
        return;
    }

    if( a_cb->detail_task )
    {
        a_cb->detail_task();
    }

    tag_handler_manager::get_instance().delete_tag_handler( a_cb->tag_id );
}

}

namespace data_link
{

abstract_io_runner::~abstract_io_runner()
{
    if( m_running_thread.joinable() )
    {
        m_running_thread.join();
    }
}

void abstract_io_runner::run( bool a_occupy_current_thread )
{
    if( a_occupy_current_thread )
    {
        running_detail();
        return;
    }

    if( m_running_thread.joinable() )
    {
        return;
    }

    m_running_thread = std::thread( &abstract_io_runner::running_detail, this );
}

void abstract_io_runner::post_task( std::function<void()> a_tsk )
{
    post_delay_task( a_tsk, std::chrono::milliseconds( 5 ) );
}

void abstract_io_runner::post_delay_task
    (
    std::function<void()> a_tsk,
    std::chrono::milliseconds a_delay
    )
{
    std::function<void( bool )> fun;
    auto cb = std::make_shared<runner_task_wrapper_control_block>();
    fun = std::bind( &io_runner_task_wrapper, cb, std::placeholders::_1 );
    auto id = tag_handler_manager::get_instance().register_tag_handler( fun );
    cb->tag_id = id;

    std::shared_ptr<grpc::Alarm> alarm = std::make_shared<grpc::Alarm>();
    cb->alarm = alarm;

    cb->detail_task = a_tsk;
    // go!
    alarm->Set( get_detail_queue(),
                std::chrono::system_clock::now() + a_delay,
                (void*)( id ) );
}

void abstract_io_runner::running_detail()
{
    base::PlatformThread::SetName( m_running_thread_name );

    gpr_set_log_function( &gpr_log_func_ );
    gpr_set_log_verbosity( GPR_LOG_SEVERITY_INFO );

    grpc::CompletionQueue* cq_ = get_detail_queue();

    while(true)
    {
        void* tag = nullptr;
        bool ok = false;
        bool ret = cq_->Next( &tag, &ok );
        if( ret )
        {
            uint64_t id = uint64_t( tag );
            auto fun = tag_handler_manager::get_instance().find_tag_handler( id );
            if( fun )
            {
                fun( ok );
            }
            else
            {
                ALOGE( "No such Tag handler! tag id = %d", id );
            }
        }
    }
}

io_runner& io_runner::get_default_instance()
{
    static io_runner instance;
    return instance;
}

io_runner::io_runner()
{
    set_running_thread_name( "io_runner" );
}

server_io_runner& server_io_runner::get_default_instance()
{
    static server_io_runner instance;
    return instance;
}

server_io_runner::server_io_runner()
{
    set_running_thread_name( "server_io_runner" );
    m_server_task_queue = m_service_builder.AddCompletionQueue();
}

}
