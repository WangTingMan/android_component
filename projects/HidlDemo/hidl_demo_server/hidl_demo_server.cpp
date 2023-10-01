#include <iostream>
#include <android/hardware/bluetooth/1.0/IBluetoothHci.h>
#include <hidl/LegacySupport.h>
#include <hwbinder/ProcessState.h> 
#include <base/logging.h>

#include <cutils/properties.h>

bool libchrome_logging_handler( int levelIn, const char* file, int line,
                                size_t message_start, const std::string& str );

int main()
{
    property_set( "persist.message.id.start", "100" );

    logging::SetLogMessageHandler( libchrome_logging_handler );
    __set_default_log_file_name( nullptr, false );

    using android::hardware::bluetooth::V1_0::IBluetoothHci;
    using android::hardware::registerPassthroughServiceImplementation;
    using android::hardware::configureRpcThreadpool;
    using android::hardware::joinRpcThreadpool;
    using android::OK;

    //Initialize Mmap size the moment the process starts
    android::hardware::ProcessState::initWithMmapSize( (size_t)( 256144 ) );
    configureRpcThreadpool( 1, true /*callerWillJoin*/ );

    android::status_t status;
    ALOGI( "Registering BT Service" );
    status = registerPassthroughServiceImplementation<IBluetoothHci>();
    if( status != OK )
        ALOGI( "Error while registering BT service: %d", status );

    joinRpcThreadpool();

    std::cout << "Hello World!\n";
    return 0;
}


bool libchrome_logging_handler( int levelIn, const char* file, int line,
                                size_t message_start, const std::string& str )
{
    android_LogPriority level = android_LogPriority::ANDROID_LOG_DEFAULT;

    switch( levelIn )
    {

    case logging::LOG_VERBOSE:
        level = android_LogPriority::ANDROID_LOG_VERBOSE;
        break;
    case logging::LOG_INFO:
        level = android_LogPriority::ANDROID_LOG_INFO;
        break;
    case logging::LOG_WARNING:
        level = android_LogPriority::ANDROID_LOG_WARN;
        break;
    case logging::LOG_ERROR:
        level = android_LogPriority::ANDROID_LOG_ERROR;
        break;
    case logging::LOG_FATAL:
        level = android_LogPriority::ANDROID_LOG_FATAL;
        break;
    case logging::LOG_NUM_SEVERITIES:
        level = android_LogPriority::ANDROID_LOG_VERBOSE;
        break;
    default:
        break;
    }

    std::string logStr;
    if( str.size() > message_start )
    {
        logStr = str.substr( message_start );
    }
    __log_format( level, "", file, "", line, logStr.c_str() );

    return true;
}