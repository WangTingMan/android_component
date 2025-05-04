#include "AospAidlBluetoothAudioProviderFactory.h"
#include "AospBluetoothAudioProvider.h"

#include <module/ipc_manager.h>
#include <module/module_manager.h>

namespace aidl::android::hardware::bluetooth::audio {

AospAidlBluetoothAudioProviderFactory::AospAidlBluetoothAudioProviderFactory()
{
    init();
    setBinderCreater( [ this ]()mutable->::ndk::SpAIBinder
                      {
                          return createBinder();
                      } );
    m_getProviderCapabilitiesFun = std::bind( &AospAidlBluetoothAudioProviderFactory::getProviderCapabilities,
                                              this, std::placeholders::_1, std::placeholders::_2 );
    m_openProviderFun = std::bind( &AospAidlBluetoothAudioProviderFactory::openProvider,
                                   this, std::placeholders::_1, std::placeholders::_2 );
    m_getProviderInfoFun = std::bind( &AospAidlBluetoothAudioProviderFactory::getProviderInfo,
                                      this, std::placeholders::_1, std::placeholders::_2 );
}

::ndk::ScopedAStatus AospAidlBluetoothAudioProviderFactory::getProviderCapabilities
    (
    SessionType in_sessionType,
    std::vector<AudioCapabilities>* _aidl_return
    )
{
    if (!_aidl_return)
    {
        LOG(ERROR) << "got empty with _aidl_return";
        return ::ndk::ScopedAStatus(
            AStatus_fromExceptionCodeWithMessage(
                EX_NULL_POINTER, "_aidl_return is empty!"));
    }

    auto ipc_manager_ = module_manager::get_instance()
        ->get_module<ipc_manager>(ipc_manager::s_module_name);
    auto local_pcm_capabilities = ipc_manager_->get_local_supported_pcm_capabilities();
    for (auto& capability : local_pcm_capabilities)
    {
        AudioCapabilities audio_cap;
        ::aidl::android::hardware::bluetooth::audio::PcmCapabilities pcm_cap;
        ::aidl::android::hardware::bluetooth::audio::ChannelMode ch_mode = ChannelMode::UNKNOWN;
        switch (capability.channel_type)
        {
        case bluetooth_module::channel_mode::mono:
            ch_mode = ChannelMode::MONO;
            break;
        case bluetooth_module::channel_mode::stereo:
            ch_mode = ChannelMode::STEREO;
            break;
        default:
            break;
        }

        pcm_cap.bitsPerSample.push_back(capability.bits_per_sample);
        pcm_cap.channelMode.push_back(ch_mode);
        pcm_cap.sampleRateHz.push_back(capability.sample_rate_hz);

        audio_cap.set<AudioCapabilities::Tag::pcmCapabilities>(pcm_cap);
        _aidl_return->push_back(audio_cap);
    }

    return ::ndk::ScopedAStatus( AStatus_newOk() );
}

::ndk::ScopedAStatus AospAidlBluetoothAudioProviderFactory::openProvider
    (
    SessionType in_sessionType,
    std::shared_ptr<IBluetoothAudioProvider>* _aidl_return
    )
{
    LOG( INFO ) << __func__ << " - SessionType=" << toString( in_sessionType );
    std::shared_ptr<AospBluetoothAudioProvider> provider = nullptr;
    provider = ndk::SharedRefBase::make<AospBluetoothAudioProvider>();

    *_aidl_return = provider;

    return ::ndk::ScopedAStatus( AStatus_newOk() );
}

::ndk::ScopedAStatus AospAidlBluetoothAudioProviderFactory::getProviderInfo
    (
    SessionType in_sessionType,
    std::optional<IBluetoothAudioProviderFactory::ProviderInfo>* _aidl_return
    )
{
    return ::ndk::ScopedAStatus( AStatus_newOk() );
}

void AospAidlBluetoothAudioProviderFactory::init()
{
    auto icp_manager = module_manager::get_instance()
        ->get_module<ipc_manager>( ipc_manager::s_module_name );
    auto local_pcm_capabilities = icp_manager->get_local_supported_pcm_capabilities();

    PcmCapabilities pcm_capabilities;
    for( auto& ele : local_pcm_capabilities )
    {
        pcm_capabilities.sampleRateHz.push_back( ele.sample_rate_hz );
        pcm_capabilities.bitsPerSample.push_back( ele.bits_per_sample );
        ChannelMode cm = ChannelMode::STEREO;
        switch( ele.channel_type )
        {
        case bluetooth_module::channel_mode::mono:
            cm = ChannelMode::MONO;
        break;
        case bluetooth_module::channel_mode::stereo:
            cm = ChannelMode::STEREO;
        break;
        case bluetooth_module::channel_mode::unknown:
            cm = ChannelMode::UNKNOWN;
        break;
        default:
            cm = ChannelMode::UNKNOWN;
        break;
        }

        pcm_capabilities.dataIntervalUs.push_back( 50 );
        pcm_capabilities.channelMode.push_back( cm );
    }

    AudioCapabilities pcm_capability;
    pcm_capability.set<AudioCapabilities::pcmCapabilities>( pcm_capabilities );
    audioCapabilities_.push_back( pcm_capability );
}

}

