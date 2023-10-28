#include <binderwrapper/common_binder_server.h>
#include <binderwrapper/common_binder_client.h>
#include <log/log.h>
#include <base/logging.h>
#include <base/rand_util.h>
#include <linux/MessageLooper.h>

std::string message_handler( std::string const& para )
{
    auto tsk = []()
        {
            common_binder_client client;
            client.set_service_name( "test_service2" );
            std::string str{ "bbb" };
            str.append( std::to_string( base::RandInt( 10, 1000 ) ) );
            auto ret = client.invoke_message( str );
        };

    MessageLooper::GetDefault().PostDelayTask( 5, tsk );

    return para;
}

bool libchrome_logging_handler( int levelIn, const char* file, int line,
                                size_t message_start, const std::string& str );

int main()
{
    logging::SetLogMessageHandler( libchrome_logging_handler );
    __set_default_log_file_name( nullptr, false );

    common_binder_server::get_instance()
        .register_handler( std::bind( &message_handler, std::placeholders::_1 ) );
    common_binder_server::get_instance().init( "test_service" );
    common_binder_server::get_instance().run( true );
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