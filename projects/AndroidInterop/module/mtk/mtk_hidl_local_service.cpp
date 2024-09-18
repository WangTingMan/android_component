#include "mtk_hidl_local_service.h"

#include <linux/MessageLooper.h>

#include <Zhen/ExecutbleEvent.h>
#include <Zhen/logging.h>
#include <Zhen/PageManager.h>

#include <hidl/LegacySupport.h>
#include <vendor/mediatek/hardware/bluetooth/audio/2.2/IBluetoothAudioProvidersFactory.h>

mtk_hidl_local_service::mtk_hidl_local_service()
{
    set_module_name(s_module_name);
}

int mtk_hidl_local_service::init()
{
    if (get_init_status() != bluetooth_module::init_status::deinitialized)
    {
        LogDebug() << "init status is not deinitialized.";
        return 0;
    }

    set_init_status(bluetooth_module::init_status::initializing);
    auto thiz = std::dynamic_pointer_cast<mtk_hidl_local_service>
        (shared_from_this());
    MessageLooper::GetDefault().PostTask(
        std::bind(&mtk_hidl_local_service::init_detail, thiz));

    return 0;
}

void mtk_hidl_local_service::stop()
{

}

void mtk_hidl_local_service::release()
{

}

void mtk_hidl_local_service::start_stream()
{

}

void mtk_hidl_local_service::stop_stream()
{

}

void mtk_hidl_local_service::suspend_stream()
{

}

void mtk_hidl_local_service::init_detail()
{
    using vendor::mediatek::hardware::bluetooth::audio::V2_2::IBluetoothAudioProvidersFactory;
    using android::hardware::registerPassthroughServiceImplementation;
    android::status_t status;
    status = registerPassthroughServiceImplementation<IBluetoothAudioProvidersFactory>();

    auto thiz = std::dynamic_pointer_cast<mtk_hidl_local_service>(shared_from_this());
    std::function<void()> fun;
    fun = std::bind(&mtk_hidl_local_service::handle_initialization_completed, thiz);
    PageManager::GetInstance().PostEvent(std::make_shared<ExecutbleEvent>(fun));
}

void mtk_hidl_local_service::handle_initialization_completed()
{
    set_init_status(bluetooth_module::init_status::initialized);
}
