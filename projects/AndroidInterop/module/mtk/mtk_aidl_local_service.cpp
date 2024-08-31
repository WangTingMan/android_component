#include "mtk_aidl_local_service.h"

#include <android/binder_manager.h>
#include <linux/MessageLooper.h>

#include <Zhen/logging.h>

mtk_aidl_local_service::mtk_aidl_local_service()
{
    set_module_name(s_module_name);
}

int mtk_aidl_local_service::init()
{
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
    if (m_service)
    {
        LogError() << "Already registered";
        return;
    }

    m_service = ndk::SharedRefBase::make<BluetoothAudioProviderFactory>();
    std::string instance = BluetoothAudioProviderFactory::descriptor;
    instance += "/default";
    auto result =
        AServiceManager_addService(m_service->asBinder().get(), instance.c_str());
    LogDebug() << instance << " registered";
}

void mtk_aidl_local_service::update_bluetooth_audio_port(std::shared_ptr<IBluetoothAudioPort> a_bluetoothAudioPort)
{
    std::lock_guard locker(m_mutex);
    m_bluetooth_audio_port = a_bluetoothAudioPort;
}

