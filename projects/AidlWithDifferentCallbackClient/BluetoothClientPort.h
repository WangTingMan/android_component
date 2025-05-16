#pragma once
#include <aidl\android\hardware\bluetooth\audio\IBluetoothAudioPort.h>

class BluetoothPort : public aidl::android::hardware::bluetooth::audio::IBluetoothAudioPort
{

public:

    ::ndk::ScopedAStatus getPresentationPosition(::aidl::android::hardware::bluetooth::audio::PresentationPosition* _aidl_return);
    ::ndk::ScopedAStatus startStream(bool in_isLowLatency);
    ::ndk::ScopedAStatus stopStream();
    ::ndk::ScopedAStatus suspendStream();
    ::ndk::ScopedAStatus updateSourceMetadata(const ::aidl::android::hardware::audio::common::SourceMetadata& in_sourceMetadata);
    ::ndk::ScopedAStatus updateSinkMetadata(const ::aidl::android::hardware::audio::common::SinkMetadata& in_sinkMetadata);
    ::ndk::ScopedAStatus setLatencyMode(::aidl::android::hardware::bluetooth::audio::LatencyMode in_latencyMode);
    ::ndk::ScopedAStatus getInterfaceVersion(int32_t* _aidl_return);
    ::ndk::ScopedAStatus getInterfaceHash(std::string* _aidl_return);
};

