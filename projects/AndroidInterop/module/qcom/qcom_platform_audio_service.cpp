#include "qcom_platform_audio_service.h"
#include "qcom_hidl_local_service.h"
#include "../module_manager.h"
#include "../ipc_manager.h"

#include <cutils/native_handle.h>

#include <Zhen/ExecutbleEvent.h>
#include <Zhen/logging.h>
#include <Zhen/PageManager.h>

#define qcom_bluetooth_audio_lib_name "libbluetooth_audio_qti.dll"

typedef void* (*get_platform_bluetooth_audio_interface_type)(const char* name);

qcom_platform_audio_service::qcom_platform_audio_service()
{
    set_module_name(s_module_name);
}

int qcom_platform_audio_service::init()
{
    if (get_init_status() != bluetooth_module::init_status::deinitialized)
    {
        LogDebug() << "init status is not deinitialized.";
        return 0;
    }

    set_init_status(bluetooth_module::init_status::initializing);
    if (m_platform_lib == nullptr) {
        LogDebug("Requesting for BT lib handle");
        m_platform_lib = dlopen(qcom_bluetooth_audio_lib_name, RTLD_NOW);
        if (m_platform_lib == nullptr) {
            LogDebug("dlopen failed for %s", qcom_bluetooth_audio_lib_name);
            set_init_status(bluetooth_module::init_status::deinitialized);
            create_qcom_local_service();
            return 0;
        }
    }

    get_platform_bluetooth_audio_interface_type api = (get_platform_bluetooth_audio_interface_type)
        dlsym(m_platform_lib, "get_platform_bluetooth_audio_interface");
    if (api)
    {
        m_low_level_interface = (bluetooth_audio_interface*)api(nullptr);
    }

    if (m_low_level_interface)
    {
        m_low_level_interface->register_async_task_scheduler(
            std::bind(&qcom_platform_audio_service::async_schedule_task,
                this, std::placeholders::_1, std::placeholders::_2));
        m_low_level_interface->init();
        set_init_status(bluetooth_module::init_status::initialized);
    }
    else
    {
        set_init_status(bluetooth_module::init_status::deinitialized);
        create_qcom_local_service();
    }
    return 0;
}

void qcom_platform_audio_service::stop()
{
    if (m_low_level_interface)
    {
        m_low_level_interface->stop();
    }
}

void qcom_platform_audio_service::release()
{
    if (m_low_level_interface)
    {
        m_low_level_interface->stop();
    }
}

void qcom_platform_audio_service::start_stream()
{
    if (m_low_level_interface)
    {
        m_low_level_interface->start_stream();
    }
}

void qcom_platform_audio_service::stop_stream()
{
    if (m_low_level_interface)
    {
        m_low_level_interface->stop_stream();
    }
}

void qcom_platform_audio_service::suspend_stream()
{
    if (m_low_level_interface)
    {
        m_low_level_interface->suspend_stream();
    }
}

void qcom_platform_audio_service::request_presentaion_delay()
{
    if (m_low_level_interface)
    {
        m_low_level_interface->request_presentaion_delay();
    }
}

bool qcom_platform_audio_service::is_enabled()
{
    return m_low_level_interface;
}

void qcom_platform_audio_service::create_qcom_local_service()
{
    auto qcom_hidl_service = std::make_shared<qcom_hidl_local_service>();
    module_manager::get_instance()->add_new_module(qcom_hidl_service);

    module_manager::get_instance()->get_module<ipc_manager>(ipc_manager::s_module_name)
        ->register_audio_service(std::move(qcom_hidl_service));
}

void qcom_platform_audio_service::async_schedule_task(bluetooth_audio_interface::async_task_type a_tsk, int a_execute_time)
{
    if (!a_tsk)
    {
        return;
    }

    if (a_execute_time > 0)
    {
        PageManager::GetInstance().connectOneShotTimerTo(a_tsk, a_execute_time, true);
    }
    else
    {
        PageManager::GetInstance().PostEvent(std::make_shared<ExecutbleEvent>(a_tsk));
    }
}


