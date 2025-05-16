#pragma once

#include <aidl/android/hardware/bluetooth/audio/BnBluetoothAudioProvider.h>
#include <aidl\android\hardware\bluetooth\audio\SessionType.h>

class AospBluetoothAudioProvider : public aidl::android::hardware::bluetooth::audio::BnBluetoothAudioProvider
{

public:

    AospBluetoothAudioProvider();

    ::ndk::ScopedAStatus endSession() override;

    ::ndk::ScopedAStatus startSession
        (
        const std::shared_ptr<::aidl::android::hardware::bluetooth::audio::IBluetoothAudioPort>& in_hostIf,
        const ::aidl::android::hardware::bluetooth::audio::AudioConfiguration& in_audioConfig,
        const std::vector<::aidl::android::hardware::bluetooth::audio::LatencyMode>& in_supportedLatencyModes,
        ::aidl::android::hardware::common::fmq::MQDescriptor<int8_t, ::aidl::android::hardware::common::fmq::SynchronizedReadWrite>* _aidl_return
        ) override;

    ::ndk::ScopedAStatus streamStarted(::aidl::android::hardware::bluetooth::audio::BluetoothAudioStatus in_status) override;

    ::ndk::ScopedAStatus streamSuspended(::aidl::android::hardware::bluetooth::audio::BluetoothAudioStatus in_status) override;

    ::ndk::ScopedAStatus updateAudioConfiguration(const ::aidl::android::hardware::bluetooth::audio::AudioConfiguration& in_audioConfig) override;

    ::ndk::ScopedAStatus setLowLatencyModeAllowed(bool in_allowed) override;

    ::ndk::ScopedAStatus parseA2dpConfiguration
        (
        const ::aidl::android::hardware::bluetooth::audio::CodecId& in_codecId,
        const std::vector<uint8_t>& in_configuration,
        ::aidl::android::hardware::bluetooth::audio::CodecParameters* out_codecParameters,
        ::aidl::android::hardware::bluetooth::audio::A2dpStatus* _aidl_return
        ) override;

    ::ndk::ScopedAStatus getA2dpConfiguration
        (
        const std::vector<::aidl::android::hardware::bluetooth::audio::A2dpRemoteCapabilities>& in_remoteA2dpCapabilities,
        const ::aidl::android::hardware::bluetooth::audio::A2dpConfigurationHint& in_hint,
        std::optional<::aidl::android::hardware::bluetooth::audio::A2dpConfiguration>* _aidl_return
        ) override;

    ::ndk::ScopedAStatus setCodecPriority
        (
        const ::aidl::android::hardware::bluetooth::audio::CodecId& in_codecId,
        int32_t in_priority
        ) override;

    ::ndk::ScopedAStatus getLeAudioAseConfiguration
        (
        const std::optional<std::vector<std::optional<::aidl::android::hardware::bluetooth::audio::IBluetoothAudioProvider::LeAudioDeviceCapabilities>>>& in_remoteSinkAudioCapabilities,
        const std::optional<std::vector<std::optional<::aidl::android::hardware::bluetooth::audio::IBluetoothAudioProvider::LeAudioDeviceCapabilities>>>& in_remoteSourceAudioCapabilities,
        const std::vector<::aidl::android::hardware::bluetooth::audio::IBluetoothAudioProvider::LeAudioConfigurationRequirement>& in_requirements,
        std::vector<::aidl::android::hardware::bluetooth::audio::IBluetoothAudioProvider::LeAudioAseConfigurationSetting>* _aidl_return
        ) override;

    ::ndk::ScopedAStatus getLeAudioAseQosConfiguration
        (
        const ::aidl::android::hardware::bluetooth::audio::IBluetoothAudioProvider::LeAudioAseQosConfigurationRequirement& in_qosRequirement,
        ::aidl::android::hardware::bluetooth::audio::IBluetoothAudioProvider::LeAudioAseQosConfigurationPair* _aidl_return
        ) override;

    ::ndk::ScopedAStatus getLeAudioAseDatapathConfiguration
        (
        const std::optional<::aidl::android::hardware::bluetooth::audio::IBluetoothAudioProvider::StreamConfig>& in_sinkConfig,
        const std::optional<::aidl::android::hardware::bluetooth::audio::IBluetoothAudioProvider::StreamConfig>& in_sourceConfig,
        ::aidl::android::hardware::bluetooth::audio::IBluetoothAudioProvider::LeAudioDataPathConfigurationPair* _aidl_return
        ) override;

    ::ndk::ScopedAStatus onSinkAseMetadataChanged
        (
        ::aidl::android::hardware::bluetooth::audio::IBluetoothAudioProvider::AseState in_state,
        int32_t in_cigId,
        int32_t in_cisId,
        const std::optional<std::vector<std::optional<::aidl::android::hardware::bluetooth::audio::MetadataLtv>>>& in_metadata
        ) override;

    ::ndk::ScopedAStatus onSourceAseMetadataChanged
        (
        ::aidl::android::hardware::bluetooth::audio::IBluetoothAudioProvider::AseState in_state,
        int32_t in_cigId,
        int32_t in_cisId,
        const std::optional<std::vector<std::optional<::aidl::android::hardware::bluetooth::audio::MetadataLtv>>>& in_metadata
        ) override;

    ::ndk::ScopedAStatus getLeAudioBroadcastConfiguration
        (
        const std::optional<std::vector<std::optional<::aidl::android::hardware::bluetooth::audio::IBluetoothAudioProvider::LeAudioDeviceCapabilities>>>& in_remoteSinkAudioCapabilities,
        const ::aidl::android::hardware::bluetooth::audio::IBluetoothAudioProvider::LeAudioBroadcastConfigurationRequirement& in_requirement,
        ::aidl::android::hardware::bluetooth::audio::IBluetoothAudioProvider::LeAudioBroadcastConfigurationSetting* _aidl_return
        ) override;

    ::ndk::ScopedAStatus getLeAudioBroadcastDatapathConfiguration
        (
        const ::aidl::android::hardware::bluetooth::audio::AudioContext& in_audioContext,
        const std::vector<::aidl::android::hardware::bluetooth::audio::LeAudioBroadcastConfiguration::BroadcastStreamMap>& in_streamMap,
        ::aidl::android::hardware::bluetooth::audio::IBluetoothAudioProvider::LeAudioDataPathConfiguration* _aidl_return
        ) override;

    void setSessionType(aidl::android::hardware::bluetooth::audio::SessionType a_session_type)
    {
        m_session_type = a_session_type;
    }

private:

    aidl::android::hardware::bluetooth::audio::SessionType m_session_type;
    void DebugChecker();
};

