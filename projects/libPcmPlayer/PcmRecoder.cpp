#include "PcmRecoder.h"
#include "PcmInternal.h"
#include "PcmDataSaver.h"
#include "soundio/soundio.h"

#include <iostream>
#include <vector>

#if __has_include(<utils/direct.h>)
#include <utils/direct.h>
#include <base/files/file_util.h>
#pragma comment(lib,"libutils.lib")
#pragma comment(lib,"libChromeBase.lib")
#define HAS_COMPONENT_LIB
#endif

struct PcmRecoderImpl
{
    PCMRecorder recorder;

    std::vector<SampleFormat> formatsSupported;
    uint32_t maxSampleRateSupported = 0;
    uint32_t minSampleRateSupported = 0;
    std::vector<SampleRateRange> sampleRatesSupported;

    struct SoundIoInStream* instream = nullptr;
    struct SoundIoDevice* in_device = nullptr;
    double microphone_latency = 0.1;
    SoundIoFormat sampleFormat = SoundIoFormatS16LE;
    SoundIoChannelLayout layout;
    std::function<void( void*, uint32_t )> data_callback;
};

static void read_callback( SoundIoInStream* instream, int frame_count_min, int frame_count_max )
{
    SoundIoChannelArea* areas;
    int err = 0;
    int flexSamles = instream->sample_rate / 10 + 300;
    int frames_left = frame_count_max;
    int framesCountUsed = 0;
    for(;;)
    {
        int frame_count = frames_left;
        err = soundio_instream_begin_read( instream, &areas, &frame_count );
        if( err != 0 )
        {
            soundio_strerror( err );
        }

        if( !frame_count )
            break;

        if( areas )
        {
            if( framesCountUsed <= flexSamles )
            {
                uint32_t size = frame_count * instream->layout.channel_count * instream->bytes_per_sample;
                auto& callback = PcmRecoder::GetInstance().m_impl->data_callback;
                if( callback )
                {
                    callback( areas->ptr, size );
                }
                PcmRecoder::GetInstance().m_impl->recorder.handle_pcm_data( areas->ptr, size );
                framesCountUsed += frame_count;
            }
        }

        err = soundio_instream_end_read( instream );
        if( err != 0 )
        {
            soundio_strerror( err );
        }

        frames_left -= frame_count;
        if( frames_left <= 0 )
            break;
    }
}

PcmRecoder& PcmRecoder::GetInstance()
{
    static PcmRecoder instance;
    return instance;
}

PcmRecoder::PcmRecoder()
{
    m_impl = std::make_shared<PcmRecoderImpl>();
    int default_in_device_index = soundio_default_input_device_index( PcmInternalControlBlock::GetInstance().soundio );
    if( default_in_device_index < 0 )
    {
        //"no input device found";
        m_impl->in_device = nullptr;
        return;
    }

    int in_device_index = default_in_device_index;
    m_impl->in_device = soundio_get_input_device( PcmInternalControlBlock::GetInstance().soundio, in_device_index );
    if( !( m_impl->in_device ) )
    {
        //"could not get input device: out of memory";
        return;
    }

    std::vector<SampleFormat> formats;
    for( int i = 0; i < m_impl->in_device->format_count; ++i )
    {
        formats.push_back( SoundIoForMatToExternalFormat( m_impl->in_device->formats[i] ) );
    }
    m_impl->formatsSupported = std::move( formats );

    std::vector<SampleRateRange> sampleRanges;
    for( int i = 0; i < m_impl->in_device->sample_rate_count; i += 1 )
    {
        SampleRateRange range;
        auto& sampleRange = m_impl->in_device->sample_rates[i];
        range.max = sampleRange.max;
        range.min = sampleRange.min;
        sampleRanges.push_back( range );
    }
    m_impl->sampleRatesSupported = std::move( sampleRanges );

    std::string dir( "D:/bluetooth/" );
#ifdef HAS_COMPONENT_LIB
    dir = GetCurrentDir();
    dir.append( "log\\" );

    base::FilePath path( dir );
    if( !base::DirectoryExists( path ) )
    {
        base::CreateDirectory( path );
    }
#endif
    dir.append( "record_mic.pcm" );

    m_impl->recorder.update_pcm_record_setting( dir, true );
}


bool PcmRecoder::open
    (
    SampleFormat a_format,
    uint32_t a_sampleRate,
    std::function<void( void*, uint32_t )> a_dataCallback
    )
{
    int err = 0;
    if( m_impl->instream )
    {
        close();
    }

    bool formatSupported = false;
    for( auto& ele : m_impl->formatsSupported )
    {
        if( ele == a_format )
        {
            formatSupported = true;
            break;
        }
    }

    if( !formatSupported )
    {
        return false;
    }

    bool sampleRateSupported = false;
    for( auto& ele : m_impl->sampleRatesSupported )
    {
        if( a_sampleRate <= ele.max && a_sampleRate >= ele.min )
        {
            sampleRateSupported = true;
            break;
        }
    }

    if( !sampleRateSupported )
    {
        return false;
    }

    m_impl->instream = soundio_instream_create( m_impl->in_device );
    m_impl->instream->format = ExternalFormatToSoundIoFormat( a_format );
    m_impl->instream->sample_rate = a_sampleRate;
    m_impl->instream->layout = m_impl->in_device->layouts[0];
    m_impl->layout = m_impl->instream->layout;
    m_impl->instream->software_latency = m_impl->microphone_latency;
    m_impl->instream->read_callback = read_callback;
    m_impl->data_callback = a_dataCallback;

    err = soundio_instream_open( m_impl->instream );
    err = soundio_instream_start( m_impl->instream );
    return true;
}

void PcmRecoder::close()
{
    if( m_impl->instream )
    {
        soundio_instream_destroy( m_impl->instream );
        m_impl->instream = nullptr;
    }
}

std::vector<SampleFormat> PcmRecoder::GetSupportedFormats()
{
    return m_impl->formatsSupported;
}

std::vector<SampleRateRange> PcmRecoder::GetSampleRates()
{
    return m_impl->sampleRatesSupported;
}

SampleFormat PcmRecoder::GetCurrentSampleFormat()
{
    SampleFormat format = SampleFormat::FormatInvalid;
    if( m_impl->instream )
    {
        format = SoundIoForMatToExternalFormat( m_impl->instream->format );
    }
    return format;
}

uint32_t PcmRecoder::GetCurrentSampleRate()
{
    uint32_t frequency = 0;
    if( m_impl->instream )
    {
        frequency = m_impl->instream->sample_rate;
    }
    return frequency;
}

uint8_t PcmRecoder::GetChannelCount()
{
    uint8_t channel = 0;
    channel = m_impl->layout.channel_count;
    return channel;
}

void PcmRecoder::SetPcmDataCallback( std::function<void( void*, uint32_t )> a_callback )
{
    m_impl->data_callback = a_callback;
}
