#pragma once
#include <aaudio/AAudio.h>
#include <system/audio-hal-enums.h>
#include <utils/Log.h>

#define AUDIO_CHANNEL_COUNT_MAX 30

enum
{
    /**
     * Audio channel index mask, only used internally.
     */
    AAUDIO_CHANNEL_BIT_INDEX = 0x80000000,
    AAUDIO_CHANNEL_INDEX_MASK_1 = AAUDIO_CHANNEL_BIT_INDEX | ( 1 << 1 ) - 1,
    AAUDIO_CHANNEL_INDEX_MASK_2 = AAUDIO_CHANNEL_BIT_INDEX | ( 1 << 2 ) - 1,
    AAUDIO_CHANNEL_INDEX_MASK_3 = AAUDIO_CHANNEL_BIT_INDEX | ( 1 << 3 ) - 1,
    AAUDIO_CHANNEL_INDEX_MASK_4 = AAUDIO_CHANNEL_BIT_INDEX | ( 1 << 4 ) - 1,
    AAUDIO_CHANNEL_INDEX_MASK_5 = AAUDIO_CHANNEL_BIT_INDEX | ( 1 << 5 ) - 1,
    AAUDIO_CHANNEL_INDEX_MASK_6 = AAUDIO_CHANNEL_BIT_INDEX | ( 1 << 6 ) - 1,
    AAUDIO_CHANNEL_INDEX_MASK_7 = AAUDIO_CHANNEL_BIT_INDEX | ( 1 << 7 ) - 1,
    AAUDIO_CHANNEL_INDEX_MASK_8 = AAUDIO_CHANNEL_BIT_INDEX | ( 1 << 8 ) - 1,
    AAUDIO_CHANNEL_INDEX_MASK_9 = AAUDIO_CHANNEL_BIT_INDEX | ( 1 << 9 ) - 1,
    AAUDIO_CHANNEL_INDEX_MASK_10 = AAUDIO_CHANNEL_BIT_INDEX | ( 1 << 10 ) - 1,
    AAUDIO_CHANNEL_INDEX_MASK_11 = AAUDIO_CHANNEL_BIT_INDEX | ( 1 << 11 ) - 1,
    AAUDIO_CHANNEL_INDEX_MASK_12 = AAUDIO_CHANNEL_BIT_INDEX | ( 1 << 12 ) - 1,
    AAUDIO_CHANNEL_INDEX_MASK_13 = AAUDIO_CHANNEL_BIT_INDEX | ( 1 << 13 ) - 1,
    AAUDIO_CHANNEL_INDEX_MASK_14 = AAUDIO_CHANNEL_BIT_INDEX | ( 1 << 14 ) - 1,
    AAUDIO_CHANNEL_INDEX_MASK_15 = AAUDIO_CHANNEL_BIT_INDEX | ( 1 << 15 ) - 1,
    AAUDIO_CHANNEL_INDEX_MASK_16 = AAUDIO_CHANNEL_BIT_INDEX | ( 1 << 16 ) - 1,
    AAUDIO_CHANNEL_INDEX_MASK_17 = AAUDIO_CHANNEL_BIT_INDEX | ( 1 << 17 ) - 1,
    AAUDIO_CHANNEL_INDEX_MASK_18 = AAUDIO_CHANNEL_BIT_INDEX | ( 1 << 18 ) - 1,
    AAUDIO_CHANNEL_INDEX_MASK_19 = AAUDIO_CHANNEL_BIT_INDEX | ( 1 << 19 ) - 1,
    AAUDIO_CHANNEL_INDEX_MASK_20 = AAUDIO_CHANNEL_BIT_INDEX | ( 1 << 20 ) - 1,
    AAUDIO_CHANNEL_INDEX_MASK_21 = AAUDIO_CHANNEL_BIT_INDEX | ( 1 << 21 ) - 1,
    AAUDIO_CHANNEL_INDEX_MASK_22 = AAUDIO_CHANNEL_BIT_INDEX | ( 1 << 22 ) - 1,
    AAUDIO_CHANNEL_INDEX_MASK_23 = AAUDIO_CHANNEL_BIT_INDEX | ( 1 << 23 ) - 1,
    AAUDIO_CHANNEL_INDEX_MASK_24 = AAUDIO_CHANNEL_BIT_INDEX | ( 1 << 24 ) - 1,
};


inline aaudio_channel_mask_t AAudioConvert_channelCountToMask( int32_t channelCount )
{
    if( channelCount < 0 || channelCount > AUDIO_CHANNEL_COUNT_MAX )
    {
        return AAUDIO_CHANNEL_INVALID;
    }

    if( channelCount == 0 )
    {
        return AAUDIO_UNSPECIFIED;
    }

    // Return index mask if the channel count is greater than 2.
    return AAUDIO_CHANNEL_BIT_INDEX | ( ( 1 << channelCount ) - 1 );
}

inline audio_format_t AAudioConvert_aaudioToAndroidDataFormat( aaudio_format_t aaudioFormat )
{
    audio_format_t androidFormat;
    switch( aaudioFormat )
    {
    case AAUDIO_FORMAT_UNSPECIFIED:
        androidFormat = AUDIO_FORMAT_DEFAULT;
    break;
    case AAUDIO_FORMAT_PCM_I16:
        androidFormat = AUDIO_FORMAT_PCM_16_BIT;
    break;
    case AAUDIO_FORMAT_PCM_FLOAT:
        androidFormat = AUDIO_FORMAT_PCM_FLOAT;
    break;
    case AAUDIO_FORMAT_PCM_I24_PACKED:
        androidFormat = AUDIO_FORMAT_PCM_24_BIT_PACKED;
    break;
    case AAUDIO_FORMAT_PCM_I32:
        androidFormat = AUDIO_FORMAT_PCM_32_BIT;
    break;
    case AAUDIO_FORMAT_IEC61937:
        androidFormat = AUDIO_FORMAT_IEC61937;
    break;
    default:
        androidFormat = AUDIO_FORMAT_INVALID;
        ALOGE( "%s() 0x%08X unrecognized", __func__, aaudioFormat );
    break;
    }
    return androidFormat;
}

inline aaudio_format_t AAudioConvert_androidToAAudioDataFormat( audio_format_t androidFormat )
{
    aaudio_format_t aaudioFormat;
    switch( androidFormat )
    {
    case AUDIO_FORMAT_DEFAULT:
        aaudioFormat = AAUDIO_FORMAT_UNSPECIFIED;
    break;
    case AUDIO_FORMAT_PCM_16_BIT:
        aaudioFormat = AAUDIO_FORMAT_PCM_I16;
    break;
    case AUDIO_FORMAT_PCM_FLOAT:
        aaudioFormat = AAUDIO_FORMAT_PCM_FLOAT;
    break;
    case AUDIO_FORMAT_PCM_24_BIT_PACKED:
        aaudioFormat = AAUDIO_FORMAT_PCM_I24_PACKED;
    break;
    case AUDIO_FORMAT_PCM_32_BIT:
        aaudioFormat = AAUDIO_FORMAT_PCM_I32;
    break;
    case AUDIO_FORMAT_IEC61937:
        aaudioFormat = AAUDIO_FORMAT_IEC61937;
    break;
    default:
        aaudioFormat = AAUDIO_FORMAT_INVALID;
        ALOGE( "%s() 0x%08X unrecognized", __func__, androidFormat );
    break;
    }
    return aaudioFormat;
}

inline aaudio_format_t AAudioConvert_androidToNearestAAudioDataFormat( audio_format_t androidFormat )
{
    // Special case AUDIO_FORMAT_PCM_8_24_BIT because this function should be used to find the
    // resolution of the data format. Setting AUDIO_FORMAT_PCM_8_24_BIT directly is not available
    // from AAudio but hardware may use AUDIO_FORMAT_PCM_8_24_BIT under the hood.
    if( androidFormat == AUDIO_FORMAT_PCM_8_24_BIT )
    {
        ALOGD( "%s() converting 8.24 to 24 bit packed", __func__ );
        return AAUDIO_FORMAT_PCM_I24_PACKED;
    }
    return AAudioConvert_androidToAAudioDataFormat( androidFormat );
}

inline bool AAudio_isChannelIndexMask( aaudio_channel_mask_t channelMask )
{
    return ( channelMask & AAUDIO_CHANNEL_BIT_INDEX ) == AAUDIO_CHANNEL_BIT_INDEX;
}
