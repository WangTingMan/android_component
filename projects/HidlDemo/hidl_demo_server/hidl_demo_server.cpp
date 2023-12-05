#include <iostream>
#include <android/hardware/bluetooth/1.0/IBluetoothHci.h>
#include <hidl/LegacySupport.h>
#include <hwbinder/ProcessState.h> 
#include <base/logging.h>

#include <cutils/properties.h>

#include <fmq/MessageQueue.h>

using DataMQ = ::android::hardware::MessageQueue<
    uint8_t, ::android::hardware::kSynchronizedReadWrite>;

bool libchrome_logging_handler( int levelIn, const char* file, int line,
                                size_t message_start, const std::string& str );

size_t read_msg
    (
    std::shared_ptr<DataMQ> aDataMQ,
    std::vector<char>& msg
    )
{
    size_t total_read = 0;
    static constexpr int kDefaultDataReadTimeoutMs = 10;
    static constexpr int kDefaultDataReadPollIntervalMs = 1;
    int timeout_ms = kDefaultDataReadTimeoutMs;
    uint8_t* p_buf = reinterpret_cast<uint8_t*>( msg.data() );
    uint32_t len = msg.size();
    do
    {
        if( aDataMQ == nullptr || !aDataMQ->isValid() ) break;

        size_t avail_to_read = aDataMQ->availableToRead();
        if( avail_to_read )
        {
            if( avail_to_read > len - total_read )
            {
                avail_to_read = len - total_read;
            }
            if( aDataMQ->read( p_buf + total_read, avail_to_read ) == 0 )
            {
                LOG( WARNING ) << __func__ << ": len=" << len
                    << " total_read=" << total_read << " failed";
                break;
            }
            total_read += avail_to_read;
        }
        else if( timeout_ms >= kDefaultDataReadPollIntervalMs )
        {
            std::this_thread::sleep_for(
                std::chrono::milliseconds( kDefaultDataReadPollIntervalMs ) );
            timeout_ms -= kDefaultDataReadPollIntervalMs;
            continue;
        }
        else
        {
            LOG( WARNING ) << __func__ << ": " << ( len - total_read ) << "/" << len
                << " no data " << ( kDefaultDataReadTimeoutMs - timeout_ms )
                << " ms";
            break;
        }
    } while( total_read < len );

    return total_read;
}

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
    __android_log_print_ext( level, "", file, line, logStr.c_str() );

    return true;
}