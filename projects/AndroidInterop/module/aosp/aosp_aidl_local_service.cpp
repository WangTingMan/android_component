#include "aosp_aidl_local_service.h"

#include <android/binder_manager.h>
#include <linux/MessageLooper.h>

#include <Zhen/logging.h>

aosp_aidl_local_service::aosp_aidl_local_service()
{
    set_module_name( s_module_name );
}

int aosp_aidl_local_service::init()
{
    auto thiz = std::dynamic_pointer_cast<aosp_aidl_local_service>
        ( shared_from_this() );
    MessageLooper::GetDefault().PostTask(
        std::bind( &aosp_aidl_local_service::init_detail, thiz ) );
    set_init_status(bluetooth_module::init_status::initialized);
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

void aosp_aidl_local_service::handle_audio_stream_started( bluetooth_module::a2dp_stream_status a_status )
{

}

void aosp_aidl_local_service::handle_audio_stream_suspended( bluetooth_module::a2dp_stream_status a_status )
{

}

void aosp_aidl_local_service::init_detail()
{

}
