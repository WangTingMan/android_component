#pragma once
#include <aidl/vendor/mediatek/hardware/bluetooth/audio/BnBluetoothAudioProvider.h>
#include <aidl/vendor/mediatek/hardware/bluetooth/audio/LatencyMode.h>
#include <aidl/vendor/mediatek/hardware/bluetooth/audio/SessionType.h>
#include <fmq/AidlMessageQueue.h>
#include <mutex>

namespace aidl::vendor::mediatek::hardware::bluetooth::audio {

class AidlBluetoothAudioProvider : public BnBluetoothAudioProvider
{

public:

    AidlBluetoothAudioProvider();

    ::ndk::ScopedAStatus endSession()override;

    ::ndk::ScopedAStatus startSession
        (
        const std::shared_ptr<IBluetoothAudioPort>& in_hostIf,
        const AudioConfiguration& in_audioConfig,
        const std::vector<LatencyMode>& in_supportedLatencyModes,
        ::aidl::android::hardware::common::fmq::MQDescriptor<int8_t, ::aidl::android::hardware::common::fmq::SynchronizedReadWrite>* _aidl_return
        )override;

    ::ndk::ScopedAStatus streamStarted( BluetoothAudioStatus in_status )override;

    ::ndk::ScopedAStatus streamSuspended( BluetoothAudioStatus in_status )override;

    ::ndk::ScopedAStatus updateAudioConfiguration( const AudioConfiguration& in_audioConfig )override;

    ::ndk::ScopedAStatus setLowLatencyModeAllowed( bool in_allowed )override;

    ::ndk::ScopedAStatus enterGameMode( int8_t in_enter )override;

    ::ndk::ScopedAStatus updataConnParam( const ConnParam& in_connPrameter )override;

private:

};

}
