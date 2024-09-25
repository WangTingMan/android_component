
#include "HidlBluetoothAudioProviderFactory_2_2.h"

#include <cutils/native_handle.h>
#include <Zhen/logging.h>
#include <module/ipc_manager.h>
#include <module/module_manager.h>
#include "mtk_hidl_local_service.h"

extern "C"
{
    vendor::mediatek::hardware::bluetooth::audio::V2_2::IBluetoothAudioProvidersFactory* HIDL_FETCH_IBluetoothAudioProvidersFactory( const char* /* name */ )
    {
        LogDebug() << "make a new BluetoothAudioProvidersFactory";
        return new vendor::mediatek::hardware::bluetooth::audio::V2_2::BluetoothAudioProvidersFactory();
    }
}

namespace vendor::mediatek::hardware::bluetooth::audio::V2_2 {

void register_generator()
{
    std::string name{"vendor.mediatek.hardware.bluetooth.audio@2.2-impl.so:HIDL_FETCH_IBluetoothAudioProvidersFactory"};
    register_local_symbol(&HIDL_FETCH_IBluetoothAudioProvidersFactory, name.c_str());
}

::android::hardware::Return<void> BluetoothAudioProvidersFactory::openProvider
    (
    ::vendor::mediatek::hardware::bluetooth::audio::V2_1::SessionType sessionType,
    openProvider_cb _hidl_cb
    )
{
    LogDebug() << "open provider for type: " << toString( sessionType );

    ::vendor::mediatek::hardware::bluetooth::audio::V2_1::Status status = V2_1::Status::SUCCESS;
    ::android::sp<::vendor::mediatek::hardware::bluetooth::audio::V2_1::IBluetoothAudioProvider> provider;
    auto hidl_local_service = module_manager::get_instance()
        ->get_module<mtk_hidl_local_service>( mtk_hidl_local_service::s_module_name );
    provider = hidl_local_service->get_audio_provider();
    _hidl_cb( status, provider );

    return Void();
}

::android::hardware::Return<void> BluetoothAudioProvidersFactory::getProviderCapabilities
    (
    ::vendor::mediatek::hardware::bluetooth::audio::V2_1::SessionType sessionType,
    getProviderCapabilities_cb _hidl_cb
    )
{
    auto icp_manager = module_manager::get_instance()
        ->get_module<ipc_manager>( ipc_manager::s_module_name );
    LogDebug() << "get provider capabilities for type: " << toString( sessionType );

    auto local_pcm_capabilities = icp_manager->get_local_supported_pcm_capabilities();
    std::vector<::vendor::mediatek::hardware::bluetooth::audio::V2_1::AudioCapabilities> audio_capabilities;
    for( auto& ele : local_pcm_capabilities )
    {
        ::vendor::mediatek::hardware::bluetooth::audio::V2_1::PcmParameters pcm;
        pcm.bitsPerSample = ::vendor::mediatek::hardware::bluetooth::audio::V2_1::BitsPerSample::BITS_UNKNOWN;
        do 
        {
            if( ele.bits_per_sample == 16 )
            {
                pcm.bitsPerSample = ::vendor::mediatek::hardware::bluetooth::audio::V2_1::BitsPerSample::BITS_16;
                break;
            }

            if( ele.bits_per_sample == 24 )
            {
                pcm.bitsPerSample = ::vendor::mediatek::hardware::bluetooth::audio::V2_1::BitsPerSample::BITS_24;
                break;
            }

            if( ele.bits_per_sample == 32 )
            {
                pcm.bitsPerSample = ::vendor::mediatek::hardware::bluetooth::audio::V2_1::BitsPerSample::BITS_32;
                break;
            }

        } while (false);

        pcm.channelMode = ::vendor::mediatek::hardware::bluetooth::audio::V2_1::ChannelMode::UNKNOWN;
        switch( ele.channel_type )
        {
        case bluetooth_module::channel_mode::mono:
            pcm.channelMode = ::vendor::mediatek::hardware::bluetooth::audio::V2_1::ChannelMode::MONO;
        break;
        case bluetooth_module::channel_mode::stereo:
            pcm.channelMode = ::vendor::mediatek::hardware::bluetooth::audio::V2_1::ChannelMode::STEREO;
        break;
        }

        pcm.sampleRate = ::vendor::mediatek::hardware::bluetooth::audio::V2_1::SampleRate::RATE_UNKNOWN;
        do
        {
            if( ele.sample_rate_hz == 44100 )
            {
                pcm.sampleRate = ::vendor::mediatek::hardware::bluetooth::audio::V2_1::SampleRate::RATE_44100;
                break;
            }

            if( ele.sample_rate_hz == 48000 )
            {
                pcm.sampleRate = ::vendor::mediatek::hardware::bluetooth::audio::V2_1::SampleRate::RATE_48000;
                break;
            }

            if( ele.sample_rate_hz == 96000 )
            {
                pcm.sampleRate = ::vendor::mediatek::hardware::bluetooth::audio::V2_1::SampleRate::RATE_96000;
                break;
            }

            if( ele.sample_rate_hz == 176400 )
            {
                pcm.sampleRate = ::vendor::mediatek::hardware::bluetooth::audio::V2_1::SampleRate::RATE_176400;
                break;
            }

            if( ele.sample_rate_hz == 192000 )
            {
                pcm.sampleRate = ::vendor::mediatek::hardware::bluetooth::audio::V2_1::SampleRate::RATE_192000;
                break;
            }

            if( ele.sample_rate_hz == 16000 )
            {
                pcm.sampleRate = ::vendor::mediatek::hardware::bluetooth::audio::V2_1::SampleRate::RATE_16000;
                break;
            }

            if( ele.sample_rate_hz == 24000 )
            {
                pcm.sampleRate = ::vendor::mediatek::hardware::bluetooth::audio::V2_1::SampleRate::RATE_24000;
                break;
            }
        } while( false );

        pcm.isLowLatencyEnabled = ::vendor::mediatek::hardware::bluetooth::audio::V2_1::LhdcLowLatencyEn::Disabled;

        ::vendor::mediatek::hardware::bluetooth::audio::V2_1::AudioCapabilities audio_capabilities_ele;
        audio_capabilities_ele.pcmCapabilities( pcm );
        audio_capabilities.push_back( audio_capabilities_ele );
    }
    ::android::hardware::hidl_vec<::vendor::mediatek::hardware::bluetooth::audio::V2_1::AudioCapabilities> audio_capabilities_hidl( audio_capabilities );

    _hidl_cb( audio_capabilities );
    return Void();
}

::android::hardware::Return<void> BluetoothAudioProvidersFactory::openProvider_2_1
    (
    ::vendor::mediatek::hardware::bluetooth::audio::V2_2::SessionType sessionType,
    openProvider_2_1_cb _hidl_cb
    )
{
    return Void();
}

::android::hardware::Return<void> BluetoothAudioProvidersFactory::getProviderCapabilities_2_1
    (
    ::vendor::mediatek::hardware::bluetooth::audio::V2_2::SessionType sessionType,
    getProviderCapabilities_2_1_cb _hidl_cb
    )
{
    return Void();
}

}

