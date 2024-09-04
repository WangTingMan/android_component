#pragma once
#include "module/audio_types.h"
#include <aidl/vendor/mediatek/hardware/bluetooth/audio/BluetoothAudioStatus.h>

namespace aidl::vendor::mediatek::hardware::bluetooth::audio {
    class AidlBluetoothAudioProvider;
}

bluetooth_module::a2dp_stream_status convert
    (
    aidl::vendor::mediatek::hardware::bluetooth::audio::BluetoothAudioStatus a_statis
    );

