#pragma once

#include <aidl/vendor/mediatek/hardware/bluetooth/audio/BnBluetoothAudioProviderFactory.h>

namespace aidl::vendor::mediatek::hardware::bluetooth::audio {

 /*
 * Local audio service
 */
class BluetoothAudioProviderFactory : public BnBluetoothAudioProviderFactory
{

public:

    BluetoothAudioProviderFactory();

    /*
    * Get local audio service's audio capabilities.
    * [in] in_sessionType Which audio session type to get
    * [out] _aidl_return The capablities of in_sessionType
    */
    ::ndk::ScopedAStatus getProviderCapabilities
        (
        ::aidl::vendor::mediatek::hardware::bluetooth::audio::SessionType in_sessionType,
        std::vector<::aidl::vendor::mediatek::hardware::bluetooth::audio::AudioCapabilities>* _aidl_return
        )override;

    /*
    * Open a audio provider for specific session type.
    * [in] in_sessionType Which audio session type to open
    * [out] _aidl_return The bluetooth audio interfaces offered by local side.
    *      Remote side can use this interfaces to notify some audio status changed to
    *      local process.
    */
    ::ndk::ScopedAStatus openProvider
        (
        ::aidl::vendor::mediatek::hardware::bluetooth::audio::SessionType in_sessionType,
        std::shared_ptr<::aidl::vendor::mediatek::hardware::bluetooth::audio::IBluetoothAudioProvider>* _aidl_return
        )override;

private:

    void init();

    std::vector<::aidl::vendor::mediatek::hardware::bluetooth::audio::AudioCapabilities> audioCapabilities_;
};

}
