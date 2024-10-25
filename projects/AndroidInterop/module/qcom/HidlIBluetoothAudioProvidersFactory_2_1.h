#pragma once
#include <vendor/qti/hardware/bluetooth_audio/2.1/IBluetoothAudioProvidersFactory.h>

namespace vendor::qti::hardware::bluetooth_audio::V2_1 {

void register_generator();

class BluetoothAudioProvidersFactory : public IBluetoothAudioProvidersFactory
{

public:

    ::android::hardware::Return<void> openProvider
        (
        ::vendor::qti::hardware::bluetooth_audio::V2_0::SessionType sessionType,
        openProvider_cb _hidl_cb
        ) override;

    ::android::hardware::Return<void> getProviderCapabilities
        (
        ::vendor::qti::hardware::bluetooth_audio::V2_0::SessionType sessionType,
        getProviderCapabilities_cb _hidl_cb
        ) override;

    ::android::hardware::Return<void> openProvider_2_1
        (
        ::vendor::qti::hardware::bluetooth_audio::V2_0::SessionType sessionType,
        openProvider_2_1_cb _hidl_cb
        ) override;

    ::android::hardware::Return<void> getProviderCapabilities_2_1
        (
        ::vendor::qti::hardware::bluetooth_audio::V2_0::SessionType sessionType,
        getProviderCapabilities_2_1_cb _hidl_cb
        ) override;


};

}

