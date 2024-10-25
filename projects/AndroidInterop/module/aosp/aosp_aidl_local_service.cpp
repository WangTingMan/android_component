#include "aosp_aidl_local_service.h"
#include "AospAidlBluetoothAudioProviderFactory.h"

#include <android/binder_manager.h>
#include <linux/MessageLooper.h>

#include <Zhen/ExecutbleEvent.h>
#include <Zhen/logging.h>
#include <Zhen/PageManager.h>

#include <cutils/properties.h>

#define AOSP_AIDL_AUDIO_LOCAL_SERVICE_ENABLED "persist.bluetooth.aospaidl_audio_local_service_enabled"

aosp_aidl_local_service::aosp_aidl_local_service()
{
    set_module_name( s_module_name );
}

int aosp_aidl_local_service::init()
{
    if( get_init_status() != bluetooth_module::init_status::deinitialized )
    {
        LogDebug() << "init status is not deinitialized.";
        return 0;
    }

    auto thiz = std::dynamic_pointer_cast<aosp_aidl_local_service>
        ( shared_from_this() );
    MessageLooper::GetDefault().PostTask(
        std::bind( &aosp_aidl_local_service::init_detail, thiz ) );
    return 0;
}

void aosp_aidl_local_service::stop()
{

}

void aosp_aidl_local_service::release()
{

}

void aosp_aidl_local_service::start_stream()
{

}

void aosp_aidl_local_service::stop_stream()
{

}

void aosp_aidl_local_service::suspend_stream()
{

}

void aosp_aidl_local_service::request_presentaion_delay()
{

}

void aosp_aidl_local_service::handle_audio_stream_started( bluetooth_module::a2dp_stream_status a_status )
{

}

void aosp_aidl_local_service::handle_audio_stream_suspended( bluetooth_module::a2dp_stream_status a_status )
{

}

void aosp_aidl_local_service::init_detail()
{
    using namespace aidl::android::hardware::bluetooth::audio;
    std::shared_ptr<AospAidlBluetoothAudioProviderFactory> service;
    int8_t enabled = property_get_bool( AOSP_AIDL_AUDIO_LOCAL_SERVICE_ENABLED, 0 );
    if( 1 == enabled )
    {
        service = ndk::SharedRefBase::make<AospAidlBluetoothAudioProviderFactory>();
        std::string instance = AospAidlBluetoothAudioProviderFactory::descriptor;
        instance += "/default";
        auto result =
            AServiceManager_addService( service->asBinder().get(), instance.c_str() );
        LogDebug() << instance << " registered";
    }

    auto thiz = std::dynamic_pointer_cast<aosp_aidl_local_service>( shared_from_this() );
    std::function<void()> fun;
    fun = std::bind(&aosp_aidl_local_service::handle_initialization_completed, thiz);
    PageManager::GetInstance().PostEvent( std::make_shared<ExecutbleEvent>( fun ) );
}

void aosp_aidl_local_service::handle_initialization_completed()
{
    set_init_status( bluetooth_module::init_status::initialized );
}
