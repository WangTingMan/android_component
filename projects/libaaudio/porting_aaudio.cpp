#include "aaudio/AAudio.h"
#include "src/core/AudioGlobal.h"

#include <log/log.h>

#include <chrono>
#include <memory>
#include <mutex>
#include <new>
#include <optional>
#include <string>
#include <vector>

#include <PcmPlayer.h>

#ifndef DONOT_USE_PORTING_AAUDIO

struct AAudioStreamBuidlerParameters
{
    int                             m_sampleRate = 0;
    aaudio_format_t                 m_format = AAUDIO_FORMAT_PCM_FLOAT;
    int                             m_channelCount = 0;
    int                             m_sessionId = 0;
    int                             m_performanceMode = 0;
    int32_t                         m_samplesPerFrame = 0;
    int32_t                         m_deviceId = 0;
    aaudio_sharing_mode_t           mSharingMode = 0;
    aaudio_direction_t              mDirection = AAUDIO_DIRECTION_OUTPUT;
    int32_t                         mBufferCapacity = AAUDIO_UNSPECIFIED;
    aaudio_usage_t                  mUsage = AAUDIO_UNSPECIFIED;
    aaudio_content_type_t           mContentType = AAUDIO_UNSPECIFIED;
    aaudio_spatialization_behavior_t mSpatializationBehavior
        = AAUDIO_UNSPECIFIED;
    bool                            mIsContentSpatialized = false;
    aaudio_input_preset_t           mInputPreset = AAUDIO_UNSPECIFIED;
    aaudio_allowed_capture_policy_t mAllowedCapturePolicy = AAUDIO_UNSPECIFIED;
    bool                            mIsPrivacySensitive = false;
    std::optional<std::string>      mOpPackageName;
    std::optional<std::string>      mAttributionTag;
    int32_t                         mFramesPerDataCallback = AAUDIO_UNSPECIFIED; // frames
    aaudio_channel_mask_t           mChannelMask = AAUDIO_UNSPECIFIED;

    AAudioStream_dataCallback       mDataCallbackProc = nullptr;  // external callback functions
    void*                           mDataCallbackUserData = nullptr;

    AAudioStream_errorCallback      mErrorCallbackProc = nullptr;
    void*                           mErrorCallbackUserData = nullptr;

    AAudioStream_presentationEndCallback mPresentationEndCallbackProc = nullptr;
    void*                                mPresentationEndCallbackUserData = nullptr;
};

struct PcmBuffer
{
    void clear()
    {
        m_validSize = 0;
        if (m_buffer)
        {
            m_buffer.reset();
        }
    }

    std::size_t m_validSize = 0;
    std::shared_ptr<std::vector<char>> m_buffer;
    std::chrono::steady_clock::time_point m_lastUsedTime;
};

struct AAudioStreamStruct
{
    AAudioStreamBuidlerParameters m_parameters;

    std::recursive_timed_mutex m_mutex;
    std::vector<PcmBuffer> m_buffersToPlay; // The PCM data waiting to pass to driver to render
    std::vector<PcmBuffer> m_buffersFree;   // The free buffers can be used for incoming pcm data
};

struct AAudioStreamBuilderStruct
{
    AAudioStreamBuidlerParameters m_parameters;
};

#ifdef __cplusplus
extern "C" {
#endif

const char* AAudio_convertResultToText( aaudio_result_t returnCode )
{
    return aaudio::AudioGlobal_convertResultToText( returnCode );
}

const char* AAudio_convertStreamStateToText( aaudio_stream_state_t state ) {
    return aaudio::AudioGlobal_convertStreamStateToText( state );
}

void TestFunctionForDebuger()
{

}

aaudio_result_t AAudio_createStreamBuilder( AAudioStreamBuilder** a_out )
{
    *a_out = new (std::nothrow) AAudioStreamBuilder;
    return AAUDIO_OK;
}

void AAudioStreamBuilder_setDeviceId( AAudioStreamBuilder* builder,
    int32_t deviceId )
{
    AAudioStreamBuilderStruct* streamBuilder = ( builder );
    streamBuilder->m_parameters.m_deviceId = ( deviceId );
}

void AAudioStreamBuilder_setPackageName
    (
    AAudioStreamBuilder* builder,
    const char* packageName
    )
{
    std::optional<std::string> optionalPackageName;
    if (packageName != nullptr) {
        optionalPackageName = std::string( packageName );
    }
    builder->m_parameters.mOpPackageName = (optionalPackageName);
}

void AAudioStreamBuilder_setAttributionTag
    (
    AAudioStreamBuilder* builder,
    const char* attributionTag
    )
{
    std::optional<std::string> optionalAttrTag;
    if (attributionTag != nullptr) {
        optionalAttrTag = std::string( attributionTag );
    }
    builder->m_parameters.mAttributionTag = (optionalAttrTag);
}

void AAudioStreamBuilder_setSampleRate( AAudioStreamBuilder* a_out, int a_sampleRate )
{
    a_out->m_parameters.m_sampleRate = a_sampleRate;
}

void AAudioStreamBuilder_setFormat( AAudioStreamBuilder* a_out, aaudio_format_t a_format )
{
    a_out->m_parameters.m_format = a_format;
}

void AAudioStreamBuilder_setSharingMode
    (
    AAudioStreamBuilder* builder,
    aaudio_sharing_mode_t sharingMode
    )
{
    builder->m_parameters.mSharingMode = sharingMode;
}

void AAudioStreamBuilder_setDirection
    (
    AAudioStreamBuilder* builder,
    aaudio_direction_t direction
    )
{
    builder->m_parameters.mDirection = direction;
}

void AAudioStreamBuilder_setBufferCapacityInFrames
    (
    AAudioStreamBuilder* builder,
    int32_t numFrames
    )
{
    builder->m_parameters.mBufferCapacity = numFrames;
}

void AAudioStreamBuilder_setChannelCount( AAudioStreamBuilder* a_out, int a_channelCount )
{
    a_out->m_parameters.m_channelCount = a_channelCount;
}

void AAudioStreamBuilder_setSamplesPerFrame
    (
    AAudioStreamBuilder* builder,
    int32_t samplesPerFrame
    )
{
    builder->m_parameters.m_samplesPerFrame = samplesPerFrame;
}

void AAudioStreamBuilder_setUsage
    (
    AAudioStreamBuilder* builder,
    aaudio_usage_t usage
    )
{
    builder->m_parameters.mUsage = usage;
}

void AAudioStreamBuilder_setContentType
    (
    AAudioStreamBuilder* builder,
    aaudio_content_type_t contentType
    )
{
    builder->m_parameters.mContentType = contentType;
}

void AAudioStreamBuilder_setSpatializationBehavior(
    AAudioStreamBuilder* builder,
    aaudio_spatialization_behavior_t spatializationBehavior )
{
    builder->m_parameters.mSpatializationBehavior = spatializationBehavior;
}

void AAudioStreamBuilder_setIsContentSpatialized( AAudioStreamBuilder* builder,
    bool isSpatialized )
{
    builder->m_parameters.mIsContentSpatialized = isSpatialized;
}

void AAudioStreamBuilder_setInputPreset( AAudioStreamBuilder* _Nonnull builder,
    aaudio_input_preset_t inputPreset )
{
    builder->m_parameters.mInputPreset = inputPreset;
}

void AAudioStreamBuilder_setAllowedCapturePolicy( AAudioStreamBuilder* _Nonnull builder,
    aaudio_allowed_capture_policy_t capturePolicy )
{
    builder->m_parameters.mAllowedCapturePolicy = capturePolicy;
}

void AAudioStreamBuilder_setSessionId( AAudioStreamBuilder* a_out, int a_id )
{
    a_out->m_parameters.m_sessionId = a_id;
}

void AAudioStreamBuilder_setPrivacySensitive( AAudioStreamBuilder* _Nonnull builder,
    bool privacySensitive )
{
    builder->m_parameters.mIsPrivacySensitive = privacySensitive;
}

void AAudioStreamBuilder_setPerformanceMode( AAudioStreamBuilder* a_out, int a_mode )
{
    a_out->m_parameters.m_performanceMode = a_mode;
}

void AAudioStreamBuilder_setDataCallback( AAudioStreamBuilder* _Nonnull builder,
    AAudioStream_dataCallback _Nullable callback, void* _Nullable userData )
{
    builder->m_parameters.mDataCallbackProc = callback;
    builder->m_parameters.mDataCallbackUserData = userData;
}

void AAudioStreamBuilder_setFramesPerDataCallback( AAudioStreamBuilder* _Nonnull builder,
    int32_t numFrames )
{
    builder->m_parameters.mFramesPerDataCallback = numFrames;
}

void AAudioStreamBuilder_setErrorCallback( AAudioStreamBuilder* _Nonnull builder,
    AAudioStream_errorCallback _Nullable callback, void* _Nullable userData )
{
    builder->m_parameters.mErrorCallbackProc = callback;
    builder->m_parameters.mErrorCallbackUserData = userData;
}

void AAudioStreamBuilder_setPresentationEndCallback(
    AAudioStreamBuilder* _Nonnull builder,
    AAudioStream_presentationEndCallback _Nonnull callback,
    void* _Nullable userData )
{
    builder->m_parameters.mPresentationEndCallbackProc = callback;
    builder->m_parameters.mPresentationEndCallbackUserData = userData;
}

aaudio_result_t AAudioStreamBuilder_openStream( AAudioStreamBuilder* a_out, AAudioStream** a_stream )
{
    *a_stream = new AAudioStream;
    ALOGI( "open new audio stream" );

    AAudioStream* p_audio_stream = *a_stream;
    p_audio_stream->m_parameters = a_out->m_parameters;

    SampleFormat sampleFormat = SampleFormat::FormatS16LE;
    switch (p_audio_stream->m_parameters.m_format)
    {
    case AAUDIO_FORMAT_PCM_I16:
        sampleFormat = SampleFormat::FormatS16LE;
        break;
    case AAUDIO_FORMAT_PCM_FLOAT:
        sampleFormat = SampleFormat::FormatFloat32LE;
        break;
    case AAUDIO_FORMAT_PCM_I32:
        sampleFormat = SampleFormat::FormatS32LE;
        break;
    default:
        break;
    }

    PcmPlayer::GetInstance().SetPcmParameters( p_audio_stream->m_parameters.m_sampleRate,
        p_audio_stream->m_parameters.m_channelCount, sampleFormat );

    return AAUDIO_OK;
}

aaudio_result_t AAudioStreamBuilder_delete( AAudioStreamBuilder* a_out )
{
    delete a_out;
    return 0;
}

void AAudioStreamBuilder_setChannelMask( AAudioStreamBuilder* _Nonnull builder,
    aaudio_channel_mask_t channelMask )
{
    builder->m_parameters.mChannelMask = channelMask;
}

int AAudioStream_getBufferSizeInFrames( AAudioStream* a_out )
{
    int ret = 4096;
    return ret;
}

aaudio_result_t AAudioStream_requestStart( AAudioStream* a_out )
{
    return 0;
}

aaudio_result_t AAudioStream_requestStop( AAudioStream* a_out )
{
    return 0;
}

aaudio_result_t AAudioStream_close( AAudioStream* a_out )
{
    return 0;
}

aaudio_result_t AAudioStream_requestPause( AAudioStream* )
{
    return 0;
}

aaudio_result_t AAudioStream_requestFlush( AAudioStream* a_out )
{
    std::unique_lock<std::recursive_timed_mutex> locker( a_out->m_mutex );
    a_out->m_buffersToPlay.clear();
    return 0;
}

aaudio_result_t AAudioStream_write
    (
    AAudioStream*   a_stream,
    const void*     a_buffer,
    int32_t         a_numFrames,
    int64_t         a_timeoutNanoseconds
    )
{
    unsigned char* p = nullptr;
    p = const_cast<uint8_t*>(reinterpret_cast<const uint8_t*>(a_buffer));
    uint16_t sample_size = 0;
    uint16_t channel_count = 0;
    std::unique_lock<std::recursive_timed_mutex> locker( a_stream->m_mutex );
    switch (a_stream->m_parameters.m_format)
    {
    case AAUDIO_FORMAT_PCM_I16:
        sample_size = sizeof( int16_t );
        break;
    case AAUDIO_FORMAT_PCM_FLOAT:
        sample_size = sizeof( float );
        break;
    case AAUDIO_FORMAT_PCM_I32:
        sample_size = sizeof( int32_t );
        break;
    default:
        break;
    }
    channel_count = a_stream->m_parameters.m_channelCount;
    locker.unlock();

    uint32_t total_size = sample_size * channel_count * a_numFrames;
    PcmPlayer::GetInstance().PlayPcmData( p, total_size );

    return AAUDIO_OK;
}

aaudio_session_id_t AAudioStream_getSessionId( AAudioStream* stream )
{
    return AAUDIO_SESSION_ID_ALLOCATE;
}

#ifdef __cplusplus
}
#endif

#endif
