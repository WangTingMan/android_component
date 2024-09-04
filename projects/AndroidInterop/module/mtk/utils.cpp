#include "utils.h"

bluetooth_module::a2dp_stream_status convert
    (
    aidl::vendor::mediatek::hardware::bluetooth::audio::BluetoothAudioStatus a_status
    )
{
    bluetooth_module::a2dp_stream_status upward_status;
    switch (a_status)
    {
    case aidl::vendor::mediatek::hardware::bluetooth::audio::BluetoothAudioStatus::FAILURE:
        upward_status = bluetooth_module::a2dp_stream_status::failure;
        break;
    case aidl::vendor::mediatek::hardware::bluetooth::audio::BluetoothAudioStatus::UNKNOWN:
        upward_status = bluetooth_module::a2dp_stream_status::unknown;
        break;
    case aidl::vendor::mediatek::hardware::bluetooth::audio::BluetoothAudioStatus::SUCCESS:
        upward_status = bluetooth_module::a2dp_stream_status::success;
        break;
    case aidl::vendor::mediatek::hardware::bluetooth::audio::BluetoothAudioStatus::UNSUPPORTED_CODEC_CONFIGURATION:
        upward_status = bluetooth_module::a2dp_stream_status::unsupported_codec_configuration;
        break;
    case aidl::vendor::mediatek::hardware::bluetooth::audio::BluetoothAudioStatus::RECONFIGURATION:
        upward_status = bluetooth_module::a2dp_stream_status::reconfiguration;
        break;
    default:
        upward_status = bluetooth_module::a2dp_stream_status::unknown;
        break;
    }
    return upward_status;
}

