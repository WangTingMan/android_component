
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <utils/Log.h>

#include <base/logging.h>
#include <iostream>

#include "TestBinderService.h"

using namespace android;

bool libchrome_logging_handler( int levelIn, const char* file, int line,
                                size_t message_start, const std::string& str );

int main(int argc, char** argv)
{
    logging::SetLogMessageHandler( libchrome_logging_handler );
    __set_default_log_file_name( nullptr, false );

    std::cout << "HelloBinerService start to run--\n";
	sp<ProcessState> proc(ProcessState::self());
    sp<IServiceManager> sm = defaultServiceManager();
    std::cout << "Success to communicate to service manager--\n";
	ALOGI("TestBinderService before");
	TestBinderService::instantiate();
	ALOGI("TestBinderService End");
	ProcessState::self()->startThreadPool();
	IPCThreadState::self()->joinThreadPool();
	ALOGI("TestBinderService End");
    system( "pause" );
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
    __android_log_print_ext( level, "", file, line,"%s", logStr.c_str() );

    return true;
}

