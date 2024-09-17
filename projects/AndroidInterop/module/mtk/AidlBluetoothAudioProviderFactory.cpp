#include "AidlBluetoothAudioProviderFactory.h"
#include "AidlBluetoothAudioProvider.h"

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
    PcmCapabilities pcm_capabilities;
    pcm_capabilities.sampleRateHz.push_back( 44100 );
    pcm_capabilities.bitsPerSample.push_back( 16 );
    pcm_capabilities.dataIntervalUs.push_back( 50 );
    pcm_capabilities.channelMode.push_back( ChannelMode::STEREO );
    AudioCapabilities pcm_capability;
    pcm_capability.set<AudioCapabilities::pcmCapabilities>( pcm_capabilities );
    audioCapabilities_.push_back( pcm_capability );
 
    CodecCapabilities codec_capabilites;
    codec_capabilites.codecType = CodecType::SBC;
    CodecCapabilities::Capabilities sbc_capabilites;
    SbcCapabilities sbc_;
    sbc_.sampleRateHz.push_back(44100);
    sbc_.channelMode.push_back( SbcChannelMode::STEREO );
    sbc_.blockLength.push_back( 10 );
    sbc_.numSubbands.push_back( 5 );
    sbc_.allocMethod.push_back( SbcAllocMethod::ALLOC_MD_L );
    sbc_.bitsPerSample.push_back( 16 );
    sbc_.minBitpool = 0;
    sbc_.maxBitpool = 20;
    sbc_capabilites.set<CodecCapabilities::Capabilities::Tag::sbcCapabilities>( sbc_ );
    codec_capabilites.capabilities = sbc_capabilites;
    AudioCapabilities codec_capabilities;
    codec_capabilities.set<AudioCapabilities::Tag::a2dpCapabilities>( codec_capabilites );
    audioCapabilities_.push_back( codec_capabilities );

}

}

