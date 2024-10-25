#pragma once

#include <vendor/qti/hardware/bluetooth_audio/2.1/IBluetoothAudioProvider.h>

namespace vendor::qti::hardware::bluetooth_audio::V2_1 {

class HidlBluetoothAudioProvider : public IBluetoothAudioProvider
{

public:

    ::android::hardware::Return<void> startSession
        (
        const ::android::sp<::vendor::qti::hardware::bluetooth_audio::V2_0::IBluetoothAudioPort>& hostIf,
        const ::vendor::qti::hardware::bluetooth_audio::V2_0::AudioConfiguration& audioConfig,
        startSession_cb _hidl_cb
        ) override;

    ::android::hardware::Return<void> streamStarted
        (
        ::vendor::qti::hardware::bluetooth_audio::V2_0::Status status
        ) override;

    ::android::hardware::Return<void> streamSuspended
        (
        ::vendor::qti::hardware::bluetooth_audio::V2_0::Status status 
        ) override;

    ::android::hardware::Return<void> updateSessionParams
        (
        const ::vendor::qti::hardware::bluetooth_audio::V2_0::SessionParams& sessionParams
        ) override;

    ::android::hardware::Return<void> endSession() override;

    ::android::hardware::Return<void> startSession_2_1
        (
        const ::android::sp<::vendor::qti::hardware::bluetooth_audio::V2_1::IBluetoothAudioPort>& hostIf,
        const ::vendor::qti::hardware::bluetooth_audio::V2_1::AudioConfiguration& audioConfig,
        startSession_2_1_cb _hidl_cb
        ) override;

};

}


