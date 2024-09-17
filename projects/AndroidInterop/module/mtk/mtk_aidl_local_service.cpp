#include "mtk_aidl_local_service.h"

#include <android/binder_manager.h>
#include <linux/MessageLooper.h>

#include <Zhen/ExecutbleEvent.h>
#include <Zhen/logging.h>
#include <Zhen/PageManager.h>

mtk_aidl_local_service::mtk_aidl_local_service()
{
    set_module_name(s_module_name);
}

int mtk_aidl_local_service::init()
{
    if (get_init_status() != bluetooth_module::init_status::deinitialized)
    {
        LogDebug() << "init status is not deinitialized.";
        return 0;
    }

    set_init_status(bluetooth_module::init_status::initializing);
    auto thiz = std::dynamic_pointer_cast<mtk_aidl_local_service>
        (shared_from_this());
    MessageLooper::GetDefault().PostTask(
        std::bind(&mtk_aidl_local_service::init_detail, thiz));
    return 0;
}

void mtk_aidl_local_service::stop()
{

}

void mtk_aidl_local_service::release()
{

}

void mtk_aidl_local_service::init_detail()
{
    std::shared_ptr<BluetoothAudioProviderFactory> service;
    service = ndk::SharedRefBase::make<BluetoothAudioProviderFactory>();
    std::string instance = BluetoothAudioProviderFactory::descriptor;
    instance += "/default";
    auto result =
        AServiceManager_addService(service->asBinder().get(), instance.c_str());
    LogDebug() << instance << " registered";
    auto thiz = std::dynamic_pointer_cast<mtk_aidl_local_service>(shared_from_this());
    std::function<void()> fun;
    fun = std::bind(&mtk_aidl_local_service::handle_initialization_completed, thiz,
        service);
    PageManager::GetInstance().PostEvent(std::make_shared<ExecutbleEvent>(fun));
}

void mtk_aidl_local_service::handle_initialization_completed(std::shared_ptr<BluetoothAudioProviderFactory> a_service)
{
    m_service = std::move(a_service);
    set_init_status(bluetooth_module::init_status::initialized);
}

void mtk_aidl_local_service::update_bluetooth_audio_port(std::shared_ptr<IBluetoothAudioPort> a_bluetoothAudioPort)
{
    m_bluetooth_audio_port = a_bluetoothAudioPort;
}

void mtk_aidl_local_service::start_stream()
{
    if (m_bluetooth_audio_port)
    {
        m_bluetooth_audio_port->startStreamDetail(false);
    }
}

void mtk_aidl_local_service::stop_stream()
{
    if (m_bluetooth_audio_port)
    {
        m_bluetooth_audio_port->stopStreamDetail();
    }
}

void mtk_aidl_local_service::suspend_stream()
{
    if (m_bluetooth_audio_port)
    {
        m_bluetooth_audio_port->suspendStreamDetail();
    }
}

void mtk_aidl_local_service::handle_audio_stream_started(bluetooth_module::a2dp_stream_status a_status)
{
    LogDebug() << "handle_audio_stream_started: " << to_string(a_status);
}

void mtk_aidl_local_service::handle_audio_stream_suspended(bluetooth_module::a2dp_stream_status a_status)
{
    LogDebug() << "handle_audio_stream_suspended: " << to_string(a_status);
}

