#include "HidlBluetoothAudioProvider.h"
#include "mtk_hidl_local_service.h"
#include <module/module_manager.h>
#include "module/ipc_manager.h"

#include <Zhen/logging.h>
#include <Zhen/PageManager.h>
#include <Zhen/ExecutbleEvent.h>

namespace vendor::mediatek::hardware::bluetooth::audio::V2_1 {

HidlBluetoothAudioProvider::HidlBluetoothAudioProvider()
{

}

// Methods from ::vendor::mediatek::hardware::bluetooth::audio::V2_1::IBluetoothAudioProvider follow.
::android::hardware::Return<void> HidlBluetoothAudioProvider::startSession
    (
    const ::android::sp<IBluetoothAudioPort>& hostIf,
    const AudioConfiguration& audioConfig,
    startSession_cb _hidl_cb
    )
{
    LogDebug() << "start bluetooth audio session: " << toString( audioConfig );

    auto hidl_local_service = module_manager::get_instance()
        ->get_module<mtk_hidl_local_service>( mtk_hidl_local_service::s_module_name );
    std::function<void()> fun;
    fun = std::bind( &mtk_hidl_local_service::handle_update_bluetooth_port_interface, hidl_local_service,
                     hostIf );
    PageManager::GetInstance().PostEvent( std::make_shared<ExecutbleEvent>( fun ) );

    bluetooth_module::pcm_configuration selected_pcm_config;
    auto pcm = audioConfig.pcmConfig();
    switch( pcm.bitsPerSample )
    {
    case BitsPerSample::BITS_16:
        selected_pcm_config.bits_per_sample = 16;
    break;
    case BitsPerSample::BITS_24:
        selected_pcm_config.bits_per_sample = 24;
    break;
    case BitsPerSample::BITS_32:
        selected_pcm_config.bits_per_sample = 32;
    break;
    default:
        selected_pcm_config.bits_per_sample = 16;
    }

    switch( pcm.channelMode )
    {
    case ChannelMode::MONO:
        selected_pcm_config.channel_type = bluetooth_module::channel_mode::mono;
    break;
    case ChannelMode::STEREO:
        selected_pcm_config.channel_type = bluetooth_module::channel_mode::stereo;
    break;
    default:
        selected_pcm_config.channel_type = bluetooth_module::channel_mode::unknown;
    break;
    }

    switch( pcm.sampleRate )
    {
    case SampleRate::RATE_16000:
        selected_pcm_config.sample_rate_hz = 16000;
    break;
    case SampleRate::RATE_24000:
        selected_pcm_config.sample_rate_hz = 24000;
    break;
    case SampleRate::RATE_192000:
        selected_pcm_config.sample_rate_hz = 192000;
    break;
    case SampleRate::RATE_176400:
        selected_pcm_config.sample_rate_hz = 176400;
    break;
    case SampleRate::RATE_96000:
        selected_pcm_config.sample_rate_hz = 96000;
    break;
    case SampleRate::RATE_88200:
        selected_pcm_config.sample_rate_hz = 88200;
    break;
    case SampleRate::RATE_48000:
        selected_pcm_config.sample_rate_hz = 48000;
    break;
    case SampleRate::RATE_44100:
        selected_pcm_config.sample_rate_hz = 44100;
    break;
    default:
        selected_pcm_config.sample_rate_hz = 16000;
    break;
    }

    auto ipc_manager_ = module_manager::get_instance()
        ->get_module<ipc_manager>( ipc_manager::s_module_name );
    fun = std::bind( &ipc_manager::set_selected_pcm_configuration, ipc_manager_,
                     selected_pcm_config );
    PageManager::GetInstance().PostEvent( std::make_shared<ExecutbleEvent>( fun ) );

    std::string json_fmq = ipc_manager_->get_fmq_json_descriptor();
    ::android::hardware::MQDescriptorSync<uint8_t> mq_descriptor;
    mq_descriptor.fromString( json_fmq );
    _hidl_cb( Status::SUCCESS, mq_descriptor );

    return ::android::hardware::Void();
}

::android::hardware::Return<void> HidlBluetoothAudioProvider::streamStarted( Status status )
{
    if( status == Status::SUCCESS )
    {
        LogDebug() << "bluetooth stream started.";
        auto hidl_local_service = module_manager::get_instance()
            ->get_module<mtk_hidl_local_service>( mtk_hidl_local_service::s_module_name );
        std::function<void()> fun;
        fun = std::bind( &mtk_hidl_local_service::trigger_stream_started_signal, hidl_local_service );
        PageManager::GetInstance().PostEvent( std::make_shared<ExecutbleEvent>( fun ) );
    }
    else
    {
        LogDebug() << "bluetooth stream not started, status: " << toString( status );
    }

    return ::android::hardware::Void();
}

::android::hardware::Return<void> HidlBluetoothAudioProvider::streamSuspended( Status status )
{
    if( status == Status::SUCCESS )
    {
        LogDebug() << "bluetooth stream suspended.";
        auto hidl_local_service = module_manager::get_instance()
            ->get_module<mtk_hidl_local_service>( mtk_hidl_local_service::s_module_name );
        std::function<void()> fun;
        fun = std::bind( &mtk_hidl_local_service::trigger_stream_suspend_signal, hidl_local_service );
        PageManager::GetInstance().PostEvent( std::make_shared<ExecutbleEvent>( fun ) );
    }
    else
    {
        LogDebug() << "bluetooth stream not suspended, status: " << toString( status );
    }
    return ::android::hardware::Void();
}

::android::hardware::Return<void> HidlBluetoothAudioProvider::endSession()
{
    LogDebug() << "bluetooth audio session end";
    auto hidl_local_service = module_manager::get_instance()
        ->get_module<mtk_hidl_local_service>( mtk_hidl_local_service::s_module_name );
    std::function<void()> fun;
    fun = std::bind( &mtk_hidl_local_service::handle_bluetooth_audio_session_end, hidl_local_service );
    PageManager::GetInstance().PostEvent( std::make_shared<ExecutbleEvent>( fun ) );

    return ::android::hardware::Void();
}

::android::hardware::Return<void> HidlBluetoothAudioProvider::enterGameMode( uint8_t enter )
{
    return ::android::hardware::Void();
}

}

