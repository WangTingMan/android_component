#define LOG_TAG "TestBinserService"

#include <utils/Log.h> 
#include <cutils/threads.h>
#include <binder/IServiceManager.h>
#include "../Interface/ITestBinderService.h"
#include "../TestBinderServer/TestBinderService.h"
#include <base/logging.h>

#include <thread>
using namespace android;

bool libchrome_logging_handler( int levelIn, const char* file, int line,
    size_t message_start, const std::string& str );

int main( int argc, char** argv )
{
    logging::SetLogMessageHandler( libchrome_logging_handler );
    __set_default_log_file_name(nullptr, false );

    ALOGI( "binderclient" );
    printf( "binderclient --\n" );
    int sum = 0;
    sp<ITestBinderService> mTestBinserService;
    if( mTestBinserService.get() == 0 )
    {
        sp<IServiceManager> sm = defaultServiceManager();
        sp<IBinder> binder;
        do
        {
            binder = sm->getService( String16( "my.test.binder" ) );
            if( binder != 0 )
                break;
            ALOGI( "getService fail" );
            usleep( 500000 ); // 0.5 s
        } while( true );
        mTestBinserService = interface_cast<ITestBinderService> ( binder );
        ALOGE_IF( mTestBinserService == 0, "no ITestBinserService!?" );
    }
    sp<IAddTest> test = mTestBinserService->BeginAddTest();
    for( int i = 0; i < 100; ++i )
    {
        sum = test->Add( 2, 4 + i );
        ALOGI( "sum = %d", sum );
    }
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
    __log_format( level, "", file, "", line, logStr.c_str() );

    return true;
}
