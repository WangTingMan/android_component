#include "mtk_hidl_local_service.h"

#include <linux/MessageLooper.h>

#include <Zhen/ExecutbleEvent.h>
#include <Zhen/logging.h>
#include <Zhen/PageManager.h>

#include <cutils/properties.h>
#include <hidl/LegacySupport.h>
#include <vendor/mediatek/hardware/bluetooth/audio/2.2/IBluetoothAudioProvidersFactory.h>

#include "HidlBluetoothAudioProviderFactory_2_2.h"
#include "HidlBluetoothAudioProvider.h"

#define MTK_HIDL_AUDIO_LOCAL_SERVICE_ENABLED "persist.bluetooth.mtk_hidl_audio_local_service_enabled"

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
    if( !m_bluetooth_audio_port )
    {
        return;
    }

    m_bluetooth_audio_port->startStream();
}

void mtk_hidl_local_service::stop_stream()
{
    if( !m_bluetooth_audio_port )
    {
        return;
    }

    m_bluetooth_audio_port->stopStream();
}

void mtk_hidl_local_service::suspend_stream()
{
    if( !m_bluetooth_audio_port )
    {
        return;
    }

    m_bluetooth_audio_port->suspendStream();
}

void mtk_hidl_local_service::update_bluetooth_port_interface( ::android::sp<IBluetoothAudioPort> a_bluetooth_audio_port )
{
    m_bluetooth_audio_port = a_bluetooth_audio_port;
}

void mtk_hidl_local_service::get_presentation()
{
    if( !m_bluetooth_audio_port )
    {
        return;
    }

    using namespace ::vendor::mediatek::hardware::bluetooth::audio::V2_1;
    std::function<void( Status, uint64_t, uint64_t, const TimeSpec& )> presentation_cb;
    auto thiz = shared_from_this();
    presentation_cb = std::bind( &mtk_hidl_local_service::presentation_updated,
                                 std::dynamic_pointer_cast<mtk_hidl_local_service>( thiz ),
                                 std::placeholders::_1,
                                 std::placeholders::_2,
                                 std::placeholders::_3,
                                 std::placeholders::_4
                                );
    m_bluetooth_audio_port->getPresentationPosition( presentation_cb );

}

void mtk_hidl_local_service::init_detail()
{
    ::android::sp<IBluetoothAudioProvider> bluetooth_audio_provider;
    int8_t enabled = property_get_bool( MTK_HIDL_AUDIO_LOCAL_SERVICE_ENABLED, 0 );
    if( 1 == enabled )
    {
        bluetooth_audio_provider = ::android::sp<vendor::mediatek::hardware::bluetooth::audio::V2_1::HidlBluetoothAudioProvider>::make();
        vendor::mediatek::hardware::bluetooth::audio::V2_2::register_generator();
        using vendor::mediatek::hardware::bluetooth::audio::V2_2::IBluetoothAudioProvidersFactory;
        using android::hardware::registerPassthroughServiceImplementation;
        android::status_t status;
        status = registerPassthroughServiceImplementation<IBluetoothAudioProvidersFactory>();
        LogDebug() << "vendor::mediatek::hardware::bluetooth::audio::V2_2::IBluetoothAudioProvidersFactory"
            " registered with status: " << status;
    }

    auto thiz = std::dynamic_pointer_cast<mtk_hidl_local_service>(shared_from_this());
    std::function<void()> fun;
    fun = std::bind(&mtk_hidl_local_service::handle_initialization_completed, thiz, bluetooth_audio_provider );
    PageManager::GetInstance().PostEvent(std::make_shared<ExecutbleEvent>(fun));
}

void mtk_hidl_local_service::presentation_updated
    (
    ::vendor::mediatek::hardware::bluetooth::audio::V2_1::Status status,
    uint64_t remoteDeviceAudioDelayNanos,
    uint64_t transmittedOctets,
    const ::vendor::mediatek::hardware::bluetooth::audio::V2_1::TimeSpec& transmittedOctetsTimeStamp
    )
{
    int x = 0;
    x = 90;
}

void mtk_hidl_local_service::handle_initialization_completed( ::android::sp<IBluetoothAudioProvider> a_provider )
{
    set_init_status( bluetooth_module::init_status::initialized );
    std::lock_guard locker( m_mutex );
    m_bluetooth_audio_provider = a_provider;
}
