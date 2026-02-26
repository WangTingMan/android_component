#include "PcmPlayer.h"
#include "soundio/soundio.h"
#include "PcmDataSaver.h"
#include "PcmInternal.h"

#include <string>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <list>
#include <chrono>
#include <algorithm>
#include <iostream>

#if __has_include(<utils/direct.h>)
#include <utils/direct.h>
#include <base/files/file_util.h>
#pragma comment(lib,"libutils.lib")
#pragma comment(lib,"libChromeBase.lib")
#define HAS_COMPONENT_LIB
#endif

#include <windows.h>

#define BUFFER_SIZE 4096
constexpr std::size_t s_maxFreeMemoryBlockCount = 20;
constexpr std::size_t s_minimalMemoryBlockSize = 1024 * 400;

extern "C"
{
    static void audio_pcm_write_callback( struct SoundIoOutStream* outstream, int frame_count_min, int frame_count_max );

    static void underflow_callback( struct SoundIoOutStream* outstream )
    {
    }

    static void out_error_callback( struct SoundIoOutStream* stream, int err )
    {
#ifdef HAS_COMPONENT_LIB
        LOG( ERROR ) << "libsoundio received a error. error code: " << err
            << ", error message: " << soundio_strerror( err );
#endif
    }
}

int GetSampleSizeFromSampleFormat( SoundIoFormat format )
{
    int ret = 0;
    switch( format )
    {
    case SoundIoFormatInvalid:
        break;
    case SoundIoFormatS8:
    case SoundIoFormatU8:
        ret = 1;
        break;
    case SoundIoFormatS16LE:
    case SoundIoFormatS16BE:
    case SoundIoFormatU16LE:
    case SoundIoFormatU16BE:
        ret = 2;
        break;
    case SoundIoFormatS24LE:
    case SoundIoFormatS24BE:
    case SoundIoFormatU24LE:
    case SoundIoFormatU24BE:
        ret = 3;
        break;
    case SoundIoFormatS32LE:
    case SoundIoFormatS32BE:
    case SoundIoFormatU32LE:
    case SoundIoFormatU32BE:
    case SoundIoFormatFloat32LE:
    case SoundIoFormatFloat32BE:
        ret = 4;
        break;
    case SoundIoFormatFloat64LE:
    case SoundIoFormatFloat64BE:
        ret = 8;
        break;
    default:
        break;
    }
    return ret;
}

struct PcmBuffer
{
    void clear()
    {
        m_validSize = 0;
        if( m_buffer )
        {
            m_buffer.reset();
        }
    }

    std::size_t m_validSize = 0;
    std::shared_ptr<std::vector<char>> m_buffer;
    std::chrono::steady_clock::time_point m_lastUsedTime;
};

struct PcmPlayerImpl
{

    void PlayPcmBuffer
        (
        unsigned char* a_pcm,
        unsigned int a_len
        );

    int selected_device_index = 0;
    struct SoundIoOutStream* outstream = nullptr;
    struct SoundIoDevice* device = nullptr;

    SoundIoFormat format;
    uint32_t sampleFrequency;
    uint8_t channelCount;

    PCMRecorder incomingSaver;

    std::recursive_timed_mutex m_mutex;
    std::vector<PcmBuffer> m_buffersToPlay; // The PCM data waiting to pass to driver to render
    std::vector<PcmBuffer> m_buffersFree;   // The free buffers can be used for incoming pcm data
};

void PcmPlayerImpl::PlayPcmBuffer
    (
    unsigned char* a_pcm,
    unsigned int a_len
    )
{
    soundio_flush_events( PcmInternalControlBlock::GetInstance().soundio );

    PcmBuffer buffer;
    buffer.m_buffer = std::make_shared<std::vector<char>>();
    buffer.m_buffer->resize( a_len );
    buffer.m_validSize = a_len;
    buffer.m_lastUsedTime = std::chrono::steady_clock::now();

    void* pBuffer = buffer.m_buffer->data();

    memcpy( pBuffer, a_pcm, a_len );
    incomingSaver.handle_pcm_data( a_pcm, a_len );

    std::unique_lock<std::recursive_timed_mutex> locker( m_mutex );
    m_buffersToPlay.push_back( buffer );
}

PcmPlayer::~PcmPlayer()
{
    if( m_impl->outstream )
    {
        soundio_outstream_destroy( m_impl->outstream );
        m_impl->outstream = nullptr;
    }

    if( m_impl->device )
    {
        soundio_device_unref( m_impl->device );
        m_impl->device = nullptr;
    }

}

std::string get_pcm_path()
{
    std::string dir("D:/bluetooth/");
#ifdef HAS_COMPONENT_LIB
    dir = GetCurrentDir();
    dir.append( "log\\" );

    base::FilePath path( dir );
    if( !base::DirectoryExists( path ) )
    {
        base::CreateDirectory( path );
    }
#endif
    dir.append( "IncomingPcmData.raw" );
    return dir;
}

PcmPlayer::PcmPlayer()
{
    m_impl = std::make_shared<PcmPlayerImpl>();
    soundio_flush_events( PcmInternalControlBlock::GetInstance().soundio );

    m_impl->selected_device_index = soundio_default_output_device_index( PcmInternalControlBlock::GetInstance().soundio );
    m_impl->device = soundio_get_output_device( PcmInternalControlBlock::GetInstance().soundio, m_impl->selected_device_index );

    m_impl->incomingSaver.update_pcm_record_setting( get_pcm_path(), true );
}

PcmPlayer& PcmPlayer::GetInstance()
{
    static PcmPlayer instance;
    return instance;
}

void PcmPlayer::SetPcmParameters
(
    uint32_t a_sampleFrequency,
    uint8_t a_channelCount,
    SampleFormat a_bitSize
)
{
    int err = 0;
    bool needCreate = !( m_impl->outstream );
    while( !needCreate )
    {
        if( m_impl->format != ExternalFormatToSoundIoFormat( a_bitSize ) )
        {
            needCreate = true;
            break;
        }

        if( m_impl->channelCount != a_channelCount )
        {
            needCreate = true;
            break;
        }

        if( m_impl->sampleFrequency != a_sampleFrequency )
        {
            needCreate = true;
            break;
        }

        break;
    }

    if( needCreate )
    {
        if( m_impl->outstream )
        {
            soundio_outstream_pause( m_impl->outstream, true );
            soundio_outstream_destroy( m_impl->outstream );
            m_impl->outstream = nullptr;
        }

        m_impl->sampleFrequency = a_sampleFrequency;
        m_impl->channelCount = a_channelCount;
        m_impl->format = ExternalFormatToSoundIoFormat( a_bitSize );

        if( nullptr == PcmInternalControlBlock::GetInstance().soundio )
        {
            PcmInternalControlBlock::GetInstance().soundio = soundio_create();
        }

        struct SoundIoOutStream* outstream = soundio_outstream_create( m_impl->device );
        outstream->write_callback = audio_pcm_write_callback;
        outstream->underflow_callback = underflow_callback;
        outstream->name = "PCM Player";
        outstream->software_latency = 0;
        outstream->error_callback = out_error_callback;

        outstream->sample_rate = a_sampleFrequency;
        if( soundio_device_supports_format( outstream->device, m_impl->format ) )
        {
            outstream->format = m_impl->format;
        }
        else
        {
#ifdef HAS_COMPONENT_LIB
            LOG( ERROR ) << "libsoundio does not support format: " << m_impl->format;
#endif
        }

        err = soundio_outstream_open( outstream );
        std::string errString( soundio_strerror( err ) );
        soundio_outstream_start( outstream );
        soundio_flush_events( PcmInternalControlBlock::GetInstance().soundio );

        m_impl->outstream = outstream;
    }
}

void PcmPlayer::PlayPcmData
(
    unsigned char* a_pcm,
    unsigned int a_len
)
{
    m_impl->PlayPcmBuffer( a_pcm, a_len );
}

void PcmPlayer::PlayPcmFrames
    (
    unsigned char* a_data,
    unsigned int a_frameCount
    )
{
    uint32_t size = a_frameCount * m_impl->channelCount * GetSampleSizeFromSampleFormat( m_impl->format );
    PlayPcmData( a_data, size );
}

extern "C"
{
    void audio_pcm_write_callback( struct SoundIoOutStream* outstream, int frame_count_min, int frame_count_max )
    {
        std::shared_ptr<PcmPlayerImpl> impl;
        impl = PcmPlayer::GetInstance().GetInternalImpl();
        std::vector<PcmBuffer> buffersToPlay;

        std::unique_lock<std::recursive_timed_mutex> locker( impl->m_mutex );
        std::swap( buffersToPlay, impl->m_buffersToPlay );
        locker.unlock();

        if( buffersToPlay.empty() )
        {
            // We cannot got PCM to play just has a rest!
            std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );
            return;
        }

        int frames_left = frame_count_max;
        int err = 0;
        int oneSampleSize = GetSampleSizeFromSampleFormat( outstream->format );
        struct SoundIoChannelArea* areas = nullptr;

        uint32_t sizeWrote = 0;
        for( auto it = buffersToPlay.begin(); it != buffersToPlay.end(); ++it )
        {
            const struct SoundIoChannelLayout* layout = &outstream->layout;
            int frame_count_to_write = ( it->m_validSize ) / ( layout->channel_count * oneSampleSize );
            int frame_count = ( frames_left >= frame_count_to_write ) ? frame_count_to_write : frames_left;

            if( ( err = soundio_outstream_begin_write( outstream, &areas, &frame_count ) ) )
            {
#ifdef HAS_COMPONENT_LIB
                LOG( ERROR ) << "unrecoverable stream error: " << soundio_strerror( err );
#endif
                return;
            }

            if( !frame_count )
                break;

            sizeWrote = frame_count * layout->channel_count * oneSampleSize;
            memcpy( areas->ptr, it->m_buffer->data(), sizeWrote );

            if( ( err = soundio_outstream_end_write( outstream ) ) )
            {
                if( err == SoundIoErrorUnderflow )
                    return;
#ifdef HAS_COMPONENT_LIB
                LOG( FATAL ) << "unrecoverable stream error :" << soundio_strerror( err );
#endif
                exit( 1 );
            }

            frames_left -= frame_count;

            if( frames_left <= 0 )
            {
                break;
            }
        }
    }
}