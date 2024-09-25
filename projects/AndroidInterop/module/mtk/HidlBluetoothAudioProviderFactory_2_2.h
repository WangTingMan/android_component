#pragma once
#include <vendor/mediatek/hardware/bluetooth/audio/2.2/IBluetoothAudioProvidersFactory.h>

using ::android::hardware::Return;
using ::android::hardware::Void;
using ::android::hardware::hidl_vec;
using ::android::hardware::hidl_handle;
using ::android::hardware::hidl_string;

namespace vendor::mediatek::hardware::bluetooth::audio::V2_2 {

void register_generator();

class BluetoothAudioProvidersFactory : public IBluetoothAudioProvidersFactory
{

public:

    ::android::hardware::Return<void> openProvider
        (
        ::vendor::mediatek::hardware::bluetooth::audio::V2_1::SessionType sessionType,
        openProvider_cb _hidl_cb
        )override;

    /**
     * 获取音频服务的音频能力。
     * 获取sessionType所指定的类型所代表的音频能力，通过调用回调_hidl_cb，就可以将音频能力回传给
     * 蓝牙服务。
     */
    ::android::hardware::Return<void> getProviderCapabilities
        (
        ::vendor::mediatek::hardware::bluetooth::audio::V2_1::SessionType sessionType,
        getProviderCapabilities_cb _hidl_cb
        )override;

    ::android::hardware::Return<void> openProvider_2_1
        (
        ::vendor::mediatek::hardware::bluetooth::audio::V2_2::SessionType sessionType,
        openProvider_2_1_cb _hidl_cb
        )override;

    ::android::hardware::Return<void> getProviderCapabilities_2_1
        (
        ::vendor::mediatek::hardware::bluetooth::audio::V2_2::SessionType sessionType,
        getProviderCapabilities_2_1_cb _hidl_cb
        );
};

}
