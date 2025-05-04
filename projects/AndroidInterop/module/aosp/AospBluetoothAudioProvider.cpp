#include "AospBluetoothAudioProvider.h"
#include "aosp_aidl_local_service.h"
#include "module/ipc_manager.h"
#include "../module_manager.h"

#include <Zhen/ExecutbleEvent.h>
#include <Zhen/PageManager.h>

#include <base/logging.h>

#include <fmq/system_porting.h>

AospBluetoothAudioProvider::AospBluetoothAudioProvider()
{
    using namespace std::placeholders;
    m_endSession = std::bind(&AospBluetoothAudioProvider::endSession, this);
    m_startSession = std::bind(&AospBluetoothAudioProvider::startSession, this, _1, _2, _3, _4);
    m_streamStarted = std::bind(&AospBluetoothAudioProvider::streamStarted, this, _1);
    m_streamSuspended = std::bind(&AospBluetoothAudioProvider::streamSuspended, this, _1);
    m_updateAudioConfiguration = std::bind(&AospBluetoothAudioProvider::updateAudioConfiguration, this, _1);
    m_setLowLatencyModeAllowed = std::bind(&AospBluetoothAudioProvider::setLowLatencyModeAllowed, this, _1);
    m_parseA2dpConfiguration = std::bind(&AospBluetoothAudioProvider::parseA2dpConfiguration, this, _1, _2, _3, _4);
    m_getA2dpConfiguration = std::bind(&AospBluetoothAudioProvider::getA2dpConfiguration, this, _1, _2, _3);
    m_setCodecPriority = std::bind(&AospBluetoothAudioProvider::setCodecPriority, this, _1, _2);
    m_getLeAudioAseConfiguration = std::bind(&AospBluetoothAudioProvider::getLeAudioAseConfiguration, this, _1, _2, _3, _4);
    m_getLeAudioAseQosConfiguration = std::bind(&AospBluetoothAudioProvider::getLeAudioAseQosConfiguration, this, _1, _2);
    m_getLeAudioAseDatapathConfiguration = std::bind(&AospBluetoothAudioProvider::getLeAudioAseDatapathConfiguration, this, _1, _2, _3);
    m_onSinkAseMetadataChanged = std::bind(&AospBluetoothAudioProvider::onSinkAseMetadataChanged, this, _1, _2, _3, _4);
    m_onSourceAseMetadataChanged = std::bind(&AospBluetoothAudioProvider::onSourceAseMetadataChanged, this, _1, _2, _3, _4);
    m_getLeAudioBroadcastConfiguration = std::bind(&AospBluetoothAudioProvider::getLeAudioBroadcastConfiguration, this, _1, _2, _3);
    m_getLeAudioBroadcastDatapathConfiguration = std::bind(&AospBluetoothAudioProvider::getLeAudioBroadcastDatapathConfiguration, this, _1, _2, _3);
}

::ndk::ScopedAStatus AospBluetoothAudioProvider::endSession()
{
    DebugChecker();
    return ::ndk::ScopedAStatus(AStatus_newOk());
}

::ndk::ScopedAStatus AospBluetoothAudioProvider::startSession
    (
    const std::shared_ptr<::aidl::android::hardware::bluetooth::audio::IBluetoothAudioPort>& in_hostIf,
    const ::aidl::android::hardware::bluetooth::audio::AudioConfiguration& in_audioConfig,
    const std::vector<::aidl::android::hardware::bluetooth::audio::LatencyMode>& in_supportedLatencyModes,
    ::aidl::android::hardware::common::fmq::MQDescriptor<int8_t, ::aidl::android::hardware::common::fmq::SynchronizedReadWrite>* _aidl_return
    )
{
    DebugChecker();
    auto aosp_module = module_manager::get_instance()
        ->get_module<aosp_aidl_local_service>(aosp_aidl_local_service::s_module_name);
    std::function<void()> fun;
    fun = std::bind(&aosp_aidl_local_service::handle_update_bluetooth_port_interface, aosp_module,
        in_hostIf);
    PageManager::GetInstance().PostEvent(std::make_shared<ExecutbleEvent>(fun));

    auto ipc_manager_ = module_manager::get_instance()
        ->get_module<ipc_manager>(ipc_manager::s_module_name);
    std::string json_fmq = ipc_manager_->get_fmq_json_descriptor();
    _aidl_return->json_decriptor = json_fmq;
    std::vector<::android::hardware::GrantorDescriptor> grantors;
    native_handle_t handle;
    native_handle_t* handles = &handle;
    uint32_t quantum;
    uint32_t flags;
    std::string name;
    system_porting::from_string(json_fmq, grantors, handles, quantum, flags, name);
    for (auto& ele : grantors)
    {
        ::aidl::android::hardware::common::fmq::GrantorDescriptor grantor;
        grantor.extent = ele.extent;
        grantor.fdIndex = ele.fdIndex;
        grantor.offset = ele.offset;
        _aidl_return->grantors.push_back(grantor);
    }
    _aidl_return->quantum = quantum;
    _aidl_return->flags = flags;

    _aidl_return->from_json_descriptor(json_fmq);

    return ::ndk::ScopedAStatus(AStatus_newOk());
}

::ndk::ScopedAStatus AospBluetoothAudioProvider::streamStarted(::aidl::android::hardware::bluetooth::audio::BluetoothAudioStatus in_status)
{
    DebugChecker();
    return ::ndk::ScopedAStatus(AStatus_newOk());
}

::ndk::ScopedAStatus AospBluetoothAudioProvider::streamSuspended(::aidl::android::hardware::bluetooth::audio::BluetoothAudioStatus in_status)
{
    DebugChecker();
    return ::ndk::ScopedAStatus(AStatus_newOk());
}

::ndk::ScopedAStatus AospBluetoothAudioProvider::updateAudioConfiguration(const ::aidl::android::hardware::bluetooth::audio::AudioConfiguration& in_audioConfig)
{
    DebugChecker();
    return ::ndk::ScopedAStatus(AStatus_newOk());
}

::ndk::ScopedAStatus AospBluetoothAudioProvider::setLowLatencyModeAllowed(bool in_allowed)
{
    DebugChecker();
    return ::ndk::ScopedAStatus(AStatus_newOk());
}

::ndk::ScopedAStatus AospBluetoothAudioProvider::parseA2dpConfiguration
    (
    const ::aidl::android::hardware::bluetooth::audio::CodecId& in_codecId,
    const std::vector<uint8_t>& in_configuration,
    ::aidl::android::hardware::bluetooth::audio::CodecParameters* out_codecParameters,
    ::aidl::android::hardware::bluetooth::audio::A2dpStatus* _aidl_return
    )
{
    DebugChecker();
    return ::ndk::ScopedAStatus(AStatus_newOk());
}

::ndk::ScopedAStatus AospBluetoothAudioProvider::getA2dpConfiguration
    (
    const std::vector<::aidl::android::hardware::bluetooth::audio::A2dpRemoteCapabilities>& in_remoteA2dpCapabilities,
    const ::aidl::android::hardware::bluetooth::audio::A2dpConfigurationHint& in_hint,
    std::optional<::aidl::android::hardware::bluetooth::audio::A2dpConfiguration>* _aidl_return
    )
{
    DebugChecker();
    return ::ndk::ScopedAStatus(AStatus_newOk());
}

::ndk::ScopedAStatus AospBluetoothAudioProvider::setCodecPriority
    (
    const ::aidl::android::hardware::bluetooth::audio::CodecId& in_codecId,
    int32_t in_priority
    )
{
    DebugChecker();
    return ::ndk::ScopedAStatus(AStatus_newOk());
}

::ndk::ScopedAStatus AospBluetoothAudioProvider::getLeAudioAseConfiguration
    (
    const std::optional<std::vector<std::optional<::aidl::android::hardware::bluetooth::audio::IBluetoothAudioProvider::LeAudioDeviceCapabilities>>>& in_remoteSinkAudioCapabilities,
    const std::optional<std::vector<std::optional<::aidl::android::hardware::bluetooth::audio::IBluetoothAudioProvider::LeAudioDeviceCapabilities>>>& in_remoteSourceAudioCapabilities,
    const std::vector<::aidl::android::hardware::bluetooth::audio::IBluetoothAudioProvider::LeAudioConfigurationRequirement>& in_requirements,
    std::vector<::aidl::android::hardware::bluetooth::audio::IBluetoothAudioProvider::LeAudioAseConfigurationSetting>* _aidl_return
    )
{
    DebugChecker();
    return ::ndk::ScopedAStatus(AStatus_newOk());
}

::ndk::ScopedAStatus AospBluetoothAudioProvider::getLeAudioAseQosConfiguration
    (
    const ::aidl::android::hardware::bluetooth::audio::IBluetoothAudioProvider::LeAudioAseQosConfigurationRequirement& in_qosRequirement,
    ::aidl::android::hardware::bluetooth::audio::IBluetoothAudioProvider::LeAudioAseQosConfigurationPair* _aidl_return
    )
{
    DebugChecker();
    return ::ndk::ScopedAStatus(AStatus_newOk());
}

::ndk::ScopedAStatus AospBluetoothAudioProvider::getLeAudioAseDatapathConfiguration
    (
    const std::optional<::aidl::android::hardware::bluetooth::audio::IBluetoothAudioProvider::StreamConfig>& in_sinkConfig,
    const std::optional<::aidl::android::hardware::bluetooth::audio::IBluetoothAudioProvider::StreamConfig>& in_sourceConfig,
    ::aidl::android::hardware::bluetooth::audio::IBluetoothAudioProvider::LeAudioDataPathConfigurationPair* _aidl_return
    )
{
    DebugChecker();
    return ::ndk::ScopedAStatus(AStatus_newOk());
}

::ndk::ScopedAStatus AospBluetoothAudioProvider::onSinkAseMetadataChanged
    (
    ::aidl::android::hardware::bluetooth::audio::IBluetoothAudioProvider::AseState in_state,
    int32_t in_cigId,
    int32_t in_cisId,
    const std::optional<std::vector<std::optional<::aidl::android::hardware::bluetooth::audio::MetadataLtv>>>& in_metadata
    )
{
    DebugChecker();
    return ::ndk::ScopedAStatus(AStatus_newOk());
}

::ndk::ScopedAStatus AospBluetoothAudioProvider::onSourceAseMetadataChanged
    (
    ::aidl::android::hardware::bluetooth::audio::IBluetoothAudioProvider::AseState in_state,
    int32_t in_cigId,
    int32_t in_cisId,
    const std::optional<std::vector<std::optional<::aidl::android::hardware::bluetooth::audio::MetadataLtv>>>& in_metadata
    )
{
    DebugChecker();
    return ::ndk::ScopedAStatus(AStatus_newOk());
}

::ndk::ScopedAStatus AospBluetoothAudioProvider::getLeAudioBroadcastConfiguration
    (
    const std::optional<std::vector<std::optional<::aidl::android::hardware::bluetooth::audio::IBluetoothAudioProvider::LeAudioDeviceCapabilities>>>& in_remoteSinkAudioCapabilities,
    const ::aidl::android::hardware::bluetooth::audio::IBluetoothAudioProvider::LeAudioBroadcastConfigurationRequirement& in_requirement,
    ::aidl::android::hardware::bluetooth::audio::IBluetoothAudioProvider::LeAudioBroadcastConfigurationSetting* _aidl_return
    )
{
    DebugChecker();
    return ::ndk::ScopedAStatus(AStatus_newOk());
}

::ndk::ScopedAStatus AospBluetoothAudioProvider::getLeAudioBroadcastDatapathConfiguration
    (
    const ::aidl::android::hardware::bluetooth::audio::AudioContext& in_audioContext,
    const std::vector<::aidl::android::hardware::bluetooth::audio::LeAudioBroadcastConfiguration::BroadcastStreamMap>& in_streamMap,
    ::aidl::android::hardware::bluetooth::audio::IBluetoothAudioProvider::LeAudioDataPathConfiguration* _aidl_return
    )
{
    DebugChecker();
    return ::ndk::ScopedAStatus(AStatus_newOk());
}

void AospBluetoothAudioProvider::DebugChecker()
{
    LOG(INFO) << "DebugChecker";
}
