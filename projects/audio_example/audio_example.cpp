#include <iostream>
#include <vector>
#include <windows.h>
#define WINSOCK_API_LINKAGE
#include <log/log.h>
#include <base/logging.h>

#include "audio_component_config.h"
#include <linux/MessageLooper.h>
#include <binder/IPCThreadState.h>

bool libchrome_logging_handler( int levelIn, const char* file, int line,
                                size_t message_start, const std::string& str );

int main()
{
    logging::SetLogMessageHandler( libchrome_logging_handler );
    __set_default_log_file_name( nullptr, false );

    SetDllDirectory(L"E:\\VCLAB\\NewAndroidInWindows\\AndroidBTInWindows\\x64\\Debug\\");

    MessageLooper& looper = MessageLooper::GetDefault();
    audio_component_config::get_instance();

    std::function<void()> tsk;
    tsk = []()
        {
            audio_component_config& condig = audio_component_config::get_instance();
            audio_component component;
            component.name = "qcom_audio";
            component.component = "E:\\VCLAB\\NewAndroidInWindows\\AndroidBTInWindows\\x64\\Debug\\audio.bluetooth_qti.default.so";
            condig.add_component( component );
            condig.load_all_component();
        };

    looper.PostTask( std::bind(&android::IPCThreadState::joinThreadPool, android::IPCThreadState::self(), true ) );
    looper.PostTask( tsk );

    if( !looper.IsRunning() )
    {
        looper.Run();
    }

    system( "pause" );
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
    __android_log_print_ext( level, "", file, line, logStr.c_str() );

    return true;
}

