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

    DataMQ::Descriptor desc_;
    std::string desc_str = R"(
        {
         "GrantorDescriptor_key" : 
         [
          {
           "GrantorDescriptor_extent_key" : 8,
           "GrantorDescriptor_fdIndex_key" : 0,
           "GrantorDescriptor_flags_key" : 0,
           "GrantorDescriptor_offset_key" : 0
          },
          {
           "GrantorDescriptor_extent_key" : 8,
           "GrantorDescriptor_fdIndex_key" : 0,
           "GrantorDescriptor_flags_key" : 0,
           "GrantorDescriptor_offset_key" : 8
          },
          {
           "GrantorDescriptor_extent_key" : 76800,
           "GrantorDescriptor_fdIndex_key" : 0,
           "GrantorDescriptor_flags_key" : 0,
           "GrantorDescriptor_offset_key" : 16
          },
          {
           "GrantorDescriptor_extent_key" : 4,
           "GrantorDescriptor_fdIndex_key" : 0,
           "GrantorDescriptor_flags_key" : 0,
           "GrantorDescriptor_offset_key" : 7696
          }
         ],
         "GrantorDescriptor_size_key" : 4,
         "flags_key" : 1,
         "name_key" : "A2dpSoftwareAudioProviderMemoryZone",
         "numFds_key" : 1,
         "numInts_key" : 0,
         "quantum_key" : 1
        }
    )";

    desc_.fromString( desc_str );
    std::shared_ptr<DataMQ> mDataMQ;
    mDataMQ.reset( new DataMQ( desc_ ) );

    std::vector<char> msg;
    msg.resize( 100 );
    size_t read_size = 0;
    std::vector<std::string> msgs;
    while( true )
    {
        read_size = read_msg( mDataMQ, msg );
        if( read_size == 100 )
        {
            //std::cout << msg.data();
            msgs.push_back( msg.data() );
            continue;
        }

        if( read_size < 1 )
        {
            continue;
        }

        if( read_size < 100 )
        {
            std::cout << "wrong\n";
        }
    }



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