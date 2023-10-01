
#include <iostream>
#include <thread>
#include <log/log.h>
#include <base/logging.h>

#include "../hidl_client.h"

#include <cutils/properties.h>

bool libchrome_logging_handler( int levelIn, const char* file, int line,
                                size_t message_start, const std::string& str );

int main()
{
    property_set( "persist.message.id.start", "200" );
    logging::SetLogMessageHandler( libchrome_logging_handler );
    __set_default_log_file_name( nullptr, false );

    hci_initialize();
    std::this_thread::sleep_for( std::chrono::hours( 1 ) );
    std::cout << "Hello World!\n";
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
