#include "ipc_manager.h"
#include <android/binder_process.h>

#include <Zhen/logging.h>
#include "mtk/mtk_aidl_local_service.h"
#include "module_manager.h"

ipc_manager::ipc_manager()
{
    set_module_name(s_module_name);
}

int ipc_manager::init()
{
    trigger_run();
    auto mtk_service = std::make_shared<mtk_aidl_local_service>();
    module_manager::get_instance()->add_new_module(mtk_service);
    return 0;
}

void ipc_manager::stop()
{

}

void ipc_manager::release()
{

}

void ipc_manager::trigger_run()
{
    std::shared_ptr<std::promise<void>> promise;
    promise = std::make_shared<std::promise<void>>();
    std::future<void> future = promise->get_future();
    m_running_thread = std::thread( &ipc_manager::run_detail, this, promise );
    future.wait_for( std::chrono::seconds( 1 ) );
}

void ipc_manager::run_detail( std::shared_ptr<std::promise<void>> a_promise )
{
    a_promise->set_value();
    a_promise.reset();

    LogDebug() << "Start to run ipc manager.";
    ABinderProcess_joinThreadPool();
}
