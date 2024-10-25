#include "AidlBluetoothAudioProviderFactory.h"
#include "AidlBluetoothAudioProvider.h"

#include <module/ipc_manager.h>
#include <module/module_manager.h>

namespace aidl::vendor::mediatek::hardware::bluetooth::audio {

BluetoothAudioProviderFactory::BluetoothAudioProviderFactory()
{
    init();
    setBinderCreater( [ this ]()mutable->::ndk::SpAIBinder
                      {
                          return createBinder();
                      } );
    m_getProviderCapabilitiesFun = std::bind( &BluetoothAudioProviderFactory::getProviderCapabilities,
                                              this, std::placeholders::_1, std::placeholders::_2 );
    m_openProviderFun = std::bind( &BluetoothAudioProviderFactory::openProvider,
                                   this, std::placeholders::_1, std::placeholders::_2 );
}

::ndk::ScopedAStatus BluetoothAudioProviderFactory::getProviderCapabilities
    (
    SessionType in_sessionType,
    std::vector<AudioCapabilities>* _aidl_return
    )
{
    LOG( INFO ) << __func__ << " - SessionType=" << toString( in_sessionType );
    *_aidl_return = audioCapabilities_;
    return ::ndk::ScopedAStatus( AStatus_newOk() );
}

::ndk::ScopedAStatus BluetoothAudioProviderFactory::openProvider
    (
    SessionType in_sessionType,
    std::shared_ptr<IBluetoothAudioProvider>* _aidl_return
    )
{
    LOG( INFO ) << __func__ << " - SessionType=" << toString( in_sessionType );
    std::shared_ptr<AidlBluetoothAudioProvider> provider = nullptr;
    provider = ndk::SharedRefBase::make<AidlBluetoothAudioProvider>();
    *_aidl_return = provider;

    return ::ndk::ScopedAStatus( AStatus_newOk() );
}

void BluetoothAudioProviderFactory::init()
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

