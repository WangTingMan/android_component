#include "AidlBluetoothAudioProvider.h"
#include "../module_manager.h"
#include "mtk_aidl_local_service.h"
#include "module/ipc_manager.h"
#include "utils.h"

#include <Zhen/PageManager.h>
#include <Zhen/ExecutbleEvent.h>

#include <fmq/system_porting.h>

namespace aidl::vendor::mediatek::hardware::bluetooth::audio {

AidlBluetoothAudioProvider::AidlBluetoothAudioProvider()
{
    m_endSessionFun = [this]()mutable->::ndk::ScopedAStatus
        {
            return this->AidlBluetoothAudioProvider::endSession();
        };

    m_startSessionFun = [this](
        const std::shared_ptr<IBluetoothAudioPort>& in_hostIf,
        const AudioConfiguration& in_audioConfig,
        const std::vector<LatencyMode>& in_supportedLatencyModes,
        ::aidl::android::hardware::common::fmq::MQDescriptor<int8_t, ::aidl::android::hardware::common::fmq::SynchronizedReadWrite>* _aidl_return
        )mutable->::ndk::ScopedAStatus
        {
            return this->AidlBluetoothAudioProvider::startSession( in_hostIf, in_audioConfig, in_supportedLatencyModes, _aidl_return );
        };

    m_streamStartedFun = [ this ]( BluetoothAudioStatus in_status )mutable->::ndk::ScopedAStatus
        {
            return this->AidlBluetoothAudioProvider::streamStarted( in_status );
        };

    m_streamSuspendedFun = [ this ]( BluetoothAudioStatus in_status )mutable->::ndk::ScopedAStatus
        {
            return this->AidlBluetoothAudioProvider::streamSuspended( in_status );
        };

    m_updateAudioConfigurationFun = [ this ]( const AudioConfiguration& in_audioConfig )mutable->::ndk::ScopedAStatus
        {
            return this->AidlBluetoothAudioProvider::updateAudioConfiguration( in_audioConfig );
        };

    m_setLowLatencyModeAllowedFun = [ this ]( bool in_allowed )mutable->::ndk::ScopedAStatus
        {
            return this->AidlBluetoothAudioProvider::setLowLatencyModeAllowed( in_allowed );
        };

    m_enterGameModeFun = [ this ]( int8_t in_enter )mutable->::ndk::ScopedAStatus
        {
            return this->AidlBluetoothAudioProvider::enterGameMode( in_enter );
        };

    m_updataConnParamFun = [ this ]( const ConnParam& in_connPrameter )mutable->::ndk::ScopedAStatus
        {
            return this->AidlBluetoothAudioProvider::updataConnParam( in_connPrameter );
        };
}

::ndk::ScopedAStatus AidlBluetoothAudioProvider::endSession()
{
    LOG(INFO) << "request end audio session";
    return ndk::ScopedAStatus::ok();
}

::ndk::ScopedAStatus AidlBluetoothAudioProvider::startSession
    (
    const std::shared_ptr<IBluetoothAudioPort>& in_hostIf,
    const AudioConfiguration& in_audioConfig,
    const std::vector<LatencyMode>& in_supportedLatencyModes,
    ::aidl::android::hardware::common::fmq::MQDescriptor<int8_t, ::aidl::android::hardware::common::fmq::SynchronizedReadWrite>* _aidl_return
    )
{
    std::string latency_mode;
    for (auto& ele : in_supportedLatencyModes)
    {
        latency_mode.append(toString(ele));
    }
    LOG( INFO ) << __func__ << " bluetooth service request start session. "
        << "latency_mode: " << latency_mode;

    auto mtk_module = module_manager::get_instance()
        ->get_module<mtk_aidl_local_service>(mtk_aidl_local_service::s_module_name);
    std::function<void()> fun;
    fun = std::bind(&mtk_aidl_local_service::update_bluetooth_audio_port, mtk_module,
        in_hostIf);
    PageManager::GetInstance().PostEvent(std::make_shared<ExecutbleEvent>(fun));

    auto icp_manager = module_manager::get_instance()
        ->get_module<ipc_manager>( ipc_manager::s_module_name );
    std::string json_fmq = icp_manager->get_fmq_json_descriptor();
    _aidl_return->json_decriptor = json_fmq;
    std::vector<::android::hardware::GrantorDescriptor> grantors;
    native_handle_t handle;
    native_handle_t* handles = &handle;
    uint32_t quantum;
    uint32_t flags;
    std::string name;
    system_porting::from_string( json_fmq, grantors, handles, quantum, flags, name );
    for( auto& ele : grantors )
    {
        ::aidl::android::hardware::common::fmq::GrantorDescriptor grantor;
        grantor.extent = ele.extent;
        grantor.fdIndex = ele.fdIndex;
        grantor.offset = ele.offset;
        _aidl_return->grantors.push_back( grantor );
    }
    _aidl_return->quantum = quantum;
    _aidl_return->flags = flags;

    handleAudioSessionChanged( in_audioConfig );

    return ndk::ScopedAStatus::ok();
}

::ndk::ScopedAStatus AidlBluetoothAudioProvider::streamStarted( BluetoothAudioStatus in_status )
{
    LOG( INFO ) << __func__ << " with " << toString(in_status);
    auto mtk_module = module_manager::get_instance()
        ->get_module<mtk_aidl_local_service>(mtk_aidl_local_service::s_module_name);
    std::function<void()> fun;
    bluetooth_module::a2dp_stream_status status = convert(in_status);
    fun = std::bind(&mtk_aidl_local_service::handle_audio_stream_started, mtk_module, status);
    PageManager::GetInstance().PostEvent(std::make_shared<ExecutbleEvent>(fun));
    return ndk::ScopedAStatus::ok();
}

::ndk::ScopedAStatus AidlBluetoothAudioProvider::streamSuspended( BluetoothAudioStatus in_status )
{
    LOG( INFO ) << __func__ << " with " << toString( in_status );
    auto mtk_module = module_manager::get_instance()
        ->get_module<mtk_aidl_local_service>(mtk_aidl_local_service::s_module_name);
    std::function<void()> fun;
    bluetooth_module::a2dp_stream_status status = convert(in_status);
    fun = std::bind(&mtk_aidl_local_service::handle_audio_stream_suspended, mtk_module, status);
    PageManager::GetInstance().PostEvent(std::make_shared<ExecutbleEvent>(fun));
    return ndk::ScopedAStatus::ok();
}

::ndk::ScopedAStatus AidlBluetoothAudioProvider::updateAudioConfiguration( const AudioConfiguration& in_audioConfig )
{
    LOG( INFO ) << __func__;
    handleAudioSessionChanged(in_audioConfig);
    return ndk::ScopedAStatus::ok();
}

::ndk::ScopedAStatus AidlBluetoothAudioProvider::setLowLatencyModeAllowed( bool in_allowed )
{
    LOG( INFO ) << __func__ << std::boolalpha << ": " << in_allowed;
    return ndk::ScopedAStatus::ok();
}

::ndk::ScopedAStatus AidlBluetoothAudioProvider::enterGameMode( int8_t in_enter )
{
    LOG( INFO ) << __func__ << ": " << in_enter;
    return ndk::ScopedAStatus::ok();
}

::ndk::ScopedAStatus AidlBluetoothAudioProvider::updataConnParam( const ConnParam& in_connPrameter )
{
    LOG( INFO ) << __func__;
    return ndk::ScopedAStatus::ok();
}

void AidlBluetoothAudioProvider::handleAudioSessionChanged( const AudioConfiguration& in_audioConfig )
{
    auto config_type = in_audioConfig.getTag();
    switch( config_type )
    {
    case AudioConfiguration::Tag::pcmConfig:
        {
            PcmConfiguration pcm = in_audioConfig.get<AudioConfiguration::Tag::pcmConfig>();
            LOG(INFO) << "Bluetooth service notify that PCM configuration.";

            auto icp_manager = module_manager::get_instance()
                ->get_module<ipc_manager>(ipc_manager::s_module_name);
            bluetooth_module::pcm_configuration pcm_config;
            pcm_config.sample_rate_hz = pcm.sampleRateHz;
            pcm_config.bits_per_sample = pcm.bitsPerSample;
            switch (pcm.channelMode)
            {
            case ChannelMode::UNKNOWN:
                pcm_config.channel_type = bluetooth_module::channel_mode::unknown;
                break;
            case ChannelMode::MONO:
                pcm_config.channel_type = bluetooth_module::channel_mode::mono;
                break;
            case ChannelMode::STEREO:
                pcm_config.channel_type = bluetooth_module::channel_mode::stereo;
                break;
            default:
                pcm_config.channel_type = bluetooth_module::channel_mode::unknown;
                break;
            }
            std::function<void()> fun;
            fun = std::bind(&ipc_manager::set_pcm_configuration, icp_manager, pcm_config);
            PageManager::GetInstance().PostEvent(std::make_shared<ExecutbleEvent>(fun));
            icp_manager->set_pcm_configuration(pcm_config);
            return;
        }
        break;
    case AudioConfiguration::Tag::a2dpConfig:
        {
            CodecConfiguration codec = in_audioConfig.get<AudioConfiguration::Tag::a2dpConfig>();
            LOG(INFO) << "Bluetooth service notify that codec configuration. Usually this is for offload";
            return;
        }
        break;
    case AudioConfiguration::Tag::leAudioConfig:
        {
            LeAudioConfiguration le_aduio = in_audioConfig.get<AudioConfiguration::Tag::leAudioConfig>();
            LOG(INFO) << "Bluetooth service notify that LE codec configuration. Usually this is for offload";
            return;
        }
        break;
    case AudioConfiguration::Tag::leAudioBroadcastConfig:
        {
            LeAudioBroadcastConfiguration le_broadcast = in_audioConfig.get<AudioConfiguration::Tag::leAudioBroadcastConfig>();
            LOG(INFO) << "Bluetooth service notify that LE broadcast configuration. Usually this is for offload";
            return;
        }
        break;
    default:
        LOG(INFO) << "Bluetooth service notify that code configuration that we unknown";
        break;
    }

}

}
