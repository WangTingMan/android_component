#include <android/binder_manager.h>
#include <android/binder_process.h>
#include <hidl/HidlSupport.h>
#include <hidl/HidlTransportSupport.h>

#include "AospAidlBluetoothAudioProviderFactory.h"

using ::android::hardware::configureRpcThreadpool;
using ::android::hardware::joinRpcThreadpool;

int main( int /* argc */, char** /* argv */ )
{
#ifdef __set_default_log_file_name_defined
    __set_default_log_file_name( nullptr, true );
#endif

    ALOGI( "Bluetooth HAL starting" );
    if( !ABinderProcess_setThreadPoolMaxThreadCount( 0 ) )
    {
        ALOGI( "failed to set thread pool max thread count" );
        return 1;
    }

    using namespace aidl::android::hardware::bluetooth::audio;
    std::shared_ptr<AospAidlBluetoothAudioProviderFactory> service =
        ndk::SharedRefBase::make<AospAidlBluetoothAudioProviderFactory>();
    std::string instance = std::string() + AospAidlBluetoothAudioProviderFactory::descriptor + "/default_test";
    auto result =
        AServiceManager_addService( service->asBinder().get(), instance.c_str() );
    if( result == STATUS_OK )
    {
        ABinderProcess_joinThreadPool();
    }
    else
    {
        ALOGE( "Could not register as a service!" );
    }
    return 0;
}
