#pragma once
#include <cstdint>
#include <optional>
#include <string>
#include <variant>
#include <vector>

namespace bluetooth_module {

struct presentation_position
{
    int64_t remote_device_audio_delay = 0;
    int64_t transmitteed_bytes = 0;

    int64_t seconds = 0;
    int64_t nanoseconds_part = 0;
};

enum class audio_usage
{
    invalid = -1,
    unknown = 0,
    media,
    voice_communication,
    voice_communication_siganlling,
    alarm,
    notification,
    notification_telephony_ringtone,
};

enum class audio_content_type
{
    unknown = 0,
    speech = 1,
    music = 2,
    movie = 3,
    snification = 4
};

using audio_channel_layout = uint32_t;

enum class audio_device_type
{
    in_headset = 7,
    out_headset = 137
};

enum class latency_mode
{
    unknown = 0,
    low_latency = 1,
    free = 2,
    dynamic_spatial_audio_software = 3,
    dynamic_spatial_audio_hardware = 4
};

struct playback_track_metadata
{
    audio_usage usage;
    audio_content_type content_type;
    float gain;
    audio_channel_layout channel_mask;
    std::optional<audio_device_type> source_device;
    std::vector<std::string> tags;
};

enum class audio_source
{
    default_source = 0,
    mic = 1,
};

struct audio_device_description
{
    audio_device_type type;
    std::string connection;
};

struct audio_device_address
{
    std::variant<std::string, std::vector<uint8_t>, std::vector<uint8_t>, std::vector<int32_t>, std::vector<int32_t>> _value;
};

struct audio_device
{
    audio_device_description type;
    audio_device_address address;
};

struct record_track_metadata
{
    audio_source usage;
    float gain;
    std::optional<audio_device> destination_device;
    audio_channel_layout channel_mask;
    std::vector<std::string> tags;
};

}
