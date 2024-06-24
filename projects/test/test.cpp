
#include <atomic>
#include <base/logging.h>
#include <fstream>
#include <iostream>
#include <thread>
#include <vector>

#include <fmq/MessageQueue.h>
#include <fmq/system_porting.h>
#include <log/log.h>
#include <openssl/digest.h>
#include <utils/RefBase.h>
#include <utils/StrongPointer.h>

#include <aidl\android\hardware\common\NativeHandle.h>
#include <android\binder_auto_utils.h>
#include <android-base\logging.h>
#include <base\strings\stringprintf.h>
#include <base\files\file_util.h>
#include <base\callback.h>
#include <base\callback_forward.h>
#include <base\bind.h>
#include <base\bind_helpers.h>

#include <audio\aidl\default\ANDROIDHARDWAREBLUETOOTHAUDIOIMPL_EXPORTS.h>

#include <windows.h>
#include <DbgHelp.h>
#include <tchar.h>
#include <type_traits>

using DataMQ = ::android::hardware::MessageQueue<
    uint8_t, ::android::hardware::kSynchronizedReadWrite>;

int main()
{

    ANDROIDHARDWAREBLUETOOTHAUDIOIMPL_TEST_NOT_USE_DIRECTLY();

    ::ndk::ScopedFileDescriptor des;
    ::ndk::ScopedFileDescriptor aa = des;
    aidl::android::hardware::common::NativeHandle handle;

    DataMQ mq( 76800, "A2dpSoftwareAudioProviderMemoryZone", true );
    auto desc = mq.getDesc();
    std::string name = desc->toString();

    std::vector<uint8_t> p_buf;
    p_buf.resize( 100 );

    std::string msg{ "hello, this is " };
    std::vector<std::string> msgs;
    for( int i = 0; i < 10000; ++i )
    {
        std::string send_msg;
        send_msg = msg;
        send_msg.append( std::to_string( i ) );
        send_msg.append( " message\n" );
        send_msg.push_back( 0x00 );
        memcpy( p_buf.data(), send_msg.c_str(), send_msg.size() );
        mq.write( p_buf.data(), 100 );
        msgs.push_back( send_msg );
        //std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
    }

    std::cout << "Hello World!\n";
}

