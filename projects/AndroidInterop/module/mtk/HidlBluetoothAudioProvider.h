#pragma once

#include <vendor/mediatek/hardware/bluetooth/audio/2.1/IBluetoothAudioProvider.h>

namespace vendor::mediatek::hardware::bluetooth::audio::V2_1
{
class HidlBluetoothAudioProvider : public ::vendor::mediatek::hardware::bluetooth::audio::V2_1::IBluetoothAudioProvider
{

public:

    HidlBluetoothAudioProvider();

    ~HidlBluetoothAudioProvider() = default;

    // Methods from ::vendor::mediatek::hardware::bluetooth::audio::V2_1::IBluetoothAudioProvider follow.
    ::android::hardware::Return<void> startSession
        (
        const ::android::sp<IBluetoothAudioPort>& hostIf,
        const AudioConfiguration& audioConfig,
        startSession_cb _hidl_cb
        ) override;

    ::android::hardware::Return<void> streamStarted( Status status ) override;

    ::android::hardware::Return<void> streamSuspended( Status status ) override;

    ::android::hardware::Return<void> endSession() override;

    ::android::hardware::Return<void> enterGameMode( uint8_t enter ) override;

private:


};

}
