#include "HidlIBluetoothAudioProvidersFactory_2_1.h"
#include <Zhen/logging.h>

#include <module/module_manager.h>
#include <module/ipc_manager.h>
#include "qcom_hidl_local_service.h"

extern "C"
{
    vendor::qti::hardware::bluetooth_audio::V2_1::IBluetoothAudioProvidersFactory* HIDL_FETCH_IBluetoothAudioProvidersFactoryQti( const char* /* name */ )
    {
        LogDebug() << "make a new qti BluetoothAudioProvidersFactory";
        return new vendor::qti::hardware::bluetooth_audio::V2_1::BluetoothAudioProvidersFactory();
    }
}

using ::android::hardware::Return;
using ::android::hardware::Void;

namespace vendor::qti::hardware::bluetooth_audio::V2_1 {

void register_generator()
{
    std::string name{ "vendor.qti.hardware.bluetooth_audio@2.1-impl.so:HIDL_FETCH_IBluetoothAudioProvidersFactory" };
    register_local_symbol( &HIDL_FETCH_IBluetoothAudioProvidersFactoryQti, name.c_str() );
}

::android::hardware::Return<void> BluetoothAudioProvidersFactory::openProvider
    (
    ::vendor::qti::hardware::bluetooth_audio::V2_0::SessionType sessionType,
    openProvider_cb _hidl_cb
    )
{
    LogDebug() << "open provider for v2.0 type: " << toString( sessionType );

    ::vendor::qti::hardware::bluetooth_audio::V2_0::Status status = V2_0::Status::SUCCESS;
    ::android::sp<::vendor::qti::hardware::bluetooth_audio::V2_1::IBluetoothAudioProvider> provider;
    auto hidl_local_service = module_manager::get_instance()
        ->get_module<qcom_hidl_local_service>( qcom_hidl_local_service::s_module_name );
    provider = hidl_local_service->get_audio_provider();
    _hidl_cb( status, provider );
    return Void();
}

::android::hardware::Return<void> BluetoothAudioProvidersFactory::getProviderCapabilities
    (
    ::vendor::qti::hardware::bluetooth_audio::V2_0::SessionType sessionType,
    getProviderCapabilities_cb _hidl_cb
    )
{
    auto icp_manager = module_manager::get_instance()
        ->get_module<ipc_manager>( ipc_manager::s_module_name );
    LogDebug() << "get provider capabilities for type: " << toString( sessionType );

    auto local_pcm_capabilities = icp_manager->get_local_supported_pcm_capabilities();

    std::vector<::vendor::qti::hardware::bluetooth_audio::V2_0::AudioCapabilities> audio_capabilities_std_vec;
    for( auto& ele : local_pcm_capabilities )
    {
        ::vendor::qti::hardware::bluetooth_audio::V2_0::PcmParameters pcm;
        pcm.bitsPerSample = ::vendor::qti::hardware::bluetooth_audio::V2_0::BitsPerSample::BITS_UNKNOWN;
        do
        {
            if( ele.bits_per_sample == 16 )
            {
                pcm.bitsPerSample = ::vendor::qti::hardware::bluetooth_audio::V2_0::BitsPerSample::BITS_16;
                break;
            }

            if( ele.bits_per_sample == 24 )
            {
                pcm.bitsPerSample = ::vendor::qti::hardware::bluetooth_audio::V2_0::BitsPerSample::BITS_24;
                break;
            }

            if( ele.bits_per_sample == 32 )
            {
                pcm.bitsPerSample = ::vendor::qti::hardware::bluetooth_audio::V2_0::BitsPerSample::BITS_32;
                break;
            }

        } while( false );

        pcm.channelMode = ::vendor::qti::hardware::bluetooth_audio::V2_0::ChannelMode::UNKNOWN;
        switch( ele.channel_type )
        {
        case bluetooth_module::channel_mode::mono:
        pcm.channelMode = ::vendor::qti::hardware::bluetooth_audio::V2_0::ChannelMode::MONO;
        break;
        case bluetooth_module::channel_mode::stereo:
        pcm.channelMode = ::vendor::qti::hardware::bluetooth_audio::V2_0::ChannelMode::STEREO;
        break;
        }

        pcm.sampleRate = ::vendor::qti::hardware::bluetooth_audio::V2_0::SampleRate::RATE_UNKNOWN;
        do
        {
            if( ele.sample_rate_hz == 44100 )
            {
                pcm.sampleRate = ::vendor::qti::hardware::bluetooth_audio::V2_0::SampleRate::RATE_44100;
                break;
            }

            if( ele.sample_rate_hz == 48000 )
            {
                pcm.sampleRate = ::vendor::qti::hardware::bluetooth_audio::V2_0::SampleRate::RATE_48000;
                break;
            }

            if( ele.sample_rate_hz == 96000 )
            {
                pcm.sampleRate = ::vendor::qti::hardware::bluetooth_audio::V2_0::SampleRate::RATE_96000;
                break;
            }

            if( ele.sample_rate_hz == 176400 )
            {
                pcm.sampleRate = ::vendor::qti::hardware::bluetooth_audio::V2_0::SampleRate::RATE_176400;
                break;
            }

            if( ele.sample_rate_hz == 192000 )
            {
                pcm.sampleRate = ::vendor::qti::hardware::bluetooth_audio::V2_0::SampleRate::RATE_192000;
                break;
            }

            if( ele.sample_rate_hz == 16000 )
            {
                pcm.sampleRate = ::vendor::qti::hardware::bluetooth_audio::V2_0::SampleRate::RATE_16000;
                break;
            }

            if( ele.sample_rate_hz == 24000 )
            {
                pcm.sampleRate = ::vendor::qti::hardware::bluetooth_audio::V2_0::SampleRate::RATE_24000;
                break;
            }
        } while( false );

        ::vendor::qti::hardware::bluetooth_audio::V2_0::AudioCapabilities audio_capabilities_ele;
        audio_capabilities_ele.pcmCapabilities = pcm;
        audio_capabilities_std_vec.push_back( audio_capabilities_ele );
    }
    ::android::hardware::hidl_vec<::vendor::qti::hardware::bluetooth_audio::V2_0::AudioCapabilities> audio_capabilities_hidl( audio_capabilities_std_vec );

    _hidl_cb( audio_capabilities_hidl );
    return Void();
}

::android::hardware::Return<void> BluetoothAudioProvidersFactory::openProvider_2_1
    (
    ::vendor::qti::hardware::bluetooth_audio::V2_0::SessionType sessionType,
    openProvider_2_1_cb _hidl_cb
    )
{
    LogDebug() << "open provider v2.1 for type: " << toString( sessionType );

    ::vendor::qti::hardware::bluetooth_audio::V2_0::Status status = V2_0::Status::SUCCESS;
    ::android::sp<::vendor::qti::hardware::bluetooth_audio::V2_1::IBluetoothAudioProvider> provider;
    auto hidl_local_service = module_manager::get_instance()
        ->get_module<qcom_hidl_local_service>( qcom_hidl_local_service::s_module_name );
    provider = hidl_local_service->get_audio_provider();
    _hidl_cb( status, provider );
    return Void();
}

::android::hardware::Return<void> BluetoothAudioProvidersFactory::getProviderCapabilities_2_1
    (
    ::vendor::qti::hardware::bluetooth_audio::V2_0::SessionType sessionType,
    getProviderCapabilities_2_1_cb _hidl_cb
    )
{
    auto icp_manager = module_manager::get_instance()
        ->get_module<ipc_manager>( ipc_manager::s_module_name );
    LogDebug() << "get provider capabilities v2.1 for type: " << toString( sessionType );

    auto local_pcm_capabilities = icp_manager->get_local_supported_pcm_capabilities();

    std::vector<::vendor::qti::hardware::bluetooth_audio::V2_1::AudioCapabilities> audio_capabilities_std_vec;
    for( auto& ele : local_pcm_capabilities )
    {
        ::vendor::qti::hardware::bluetooth_audio::V2_0::PcmParameters pcm;
        pcm.bitsPerSample = ::vendor::qti::hardware::bluetooth_audio::V2_0::BitsPerSample::BITS_UNKNOWN;
        do
        {
            if( ele.bits_per_sample == 16 )
            {
                pcm.bitsPerSample = ::vendor::qti::hardware::bluetooth_audio::V2_0::BitsPerSample::BITS_16;
                break;
            }

            if( ele.bits_per_sample == 24 )
            {
                pcm.bitsPerSample = ::vendor::qti::hardware::bluetooth_audio::V2_0::BitsPerSample::BITS_24;
                break;
            }

            if( ele.bits_per_sample == 32 )
            {
                pcm.bitsPerSample = ::vendor::qti::hardware::bluetooth_audio::V2_0::BitsPerSample::BITS_32;
                break;
            }

        } while( false );

        pcm.channelMode = ::vendor::qti::hardware::bluetooth_audio::V2_0::ChannelMode::UNKNOWN;
        switch( ele.channel_type )
        {
        case bluetooth_module::channel_mode::mono:
        pcm.channelMode = ::vendor::qti::hardware::bluetooth_audio::V2_0::ChannelMode::MONO;
        break;
        case bluetooth_module::channel_mode::stereo:
        pcm.channelMode = ::vendor::qti::hardware::bluetooth_audio::V2_0::ChannelMode::STEREO;
        break;
        }

        pcm.sampleRate = ::vendor::qti::hardware::bluetooth_audio::V2_0::SampleRate::RATE_UNKNOWN;
        do
        {
            if( ele.sample_rate_hz == 44100 )
            {
                pcm.sampleRate = ::vendor::qti::hardware::bluetooth_audio::V2_0::SampleRate::RATE_44100;
                break;
            }

            if( ele.sample_rate_hz == 48000 )
            {
                pcm.sampleRate = ::vendor::qti::hardware::bluetooth_audio::V2_0::SampleRate::RATE_48000;
                break;
            }

            if( ele.sample_rate_hz == 96000 )
            {
                pcm.sampleRate = ::vendor::qti::hardware::bluetooth_audio::V2_0::SampleRate::RATE_96000;
                break;
            }

            if( ele.sample_rate_hz == 176400 )
            {
                pcm.sampleRate = ::vendor::qti::hardware::bluetooth_audio::V2_0::SampleRate::RATE_176400;
                break;
            }

            if( ele.sample_rate_hz == 192000 )
            {
                pcm.sampleRate = ::vendor::qti::hardware::bluetooth_audio::V2_0::SampleRate::RATE_192000;
                break;
            }

            if( ele.sample_rate_hz == 16000 )
            {
                pcm.sampleRate = ::vendor::qti::hardware::bluetooth_audio::V2_0::SampleRate::RATE_16000;
                break;
            }

            if( ele.sample_rate_hz == 24000 )
            {
                pcm.sampleRate = ::vendor::qti::hardware::bluetooth_audio::V2_0::SampleRate::RATE_24000;
                break;
            }
        } while( false );

        ::vendor::qti::hardware::bluetooth_audio::V2_1::AudioCapabilities audio_capabilities_ele;
        audio_capabilities_ele.pcmCapabilities = pcm;
        audio_capabilities_std_vec.push_back( audio_capabilities_ele );
    }
    ::android::hardware::hidl_vec<::vendor::qti::hardware::bluetooth_audio::V2_1::AudioCapabilities> audio_capabilities_hidl( audio_capabilities_std_vec );

    _hidl_cb( audio_capabilities_hidl );

    return Void();
}

}
