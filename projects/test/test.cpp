
#include <iostream>
#include <atomic>
#include <base/logging.h>

#include <fmq/MessageQueue.h>
#include <log/log.h>

using DataMQ = ::android::hardware::MessageQueue<
    uint8_t, ::android::hardware::kSynchronizedReadWrite>;

int main()
{
    native_handle_t na_handle;
    na_handle.version = sizeof( native_handle_t );
    na_handle.numInts = 2;
    na_handle.numFds = 1;
    memset( na_handle.data, 0x00, NATIVE_HANDLE_DATA_SIZE );
    size_t bufferSize = 1024;
    native_handle_t* nHandle = &na_handle;
    size_t messageSize = sizeof( uint8_t );
    bool configureEventFlag = true;

    DataMQ::Descriptor desciptor( bufferSize, nHandle, messageSize, configureEventFlag );

    DataMQ mq( desciptor, true );

    size_t size = mq.availableToRead();
    std::vector<uint8_t> p_buf( size );

    if( !mq.read( p_buf.data(), size ) )
        LOG( WARNING ) << __func__ << ", failed to flush data queue!";

    uint8_t buffer[10];
    for( int i = 0; i < 10; ++i )
    {
        buffer[i] = 'A' + i;
    }
    mq.write( buffer, 10 );

    size = mq.availableToRead();
    p_buf.resize( size );

    if( !mq.read( p_buf.data(), size ) )
        LOG( WARNING ) << __func__ << ", failed to flush data queue!";
    std::cout << "Hello World!\n";
}

