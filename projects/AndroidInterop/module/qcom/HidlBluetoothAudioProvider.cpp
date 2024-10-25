#include "HidlBluetoothAudioProvider.h"
#include "qcom_hidl_local_service.h"
#include <module/module_manager.h>
#include "module/ipc_manager.h"

#include <Zhen/logging.h>
#include <Zhen/PageManager.h>
#include <Zhen/ExecutbleEvent.h>

using ::android::hardware::Return;
using ::android::hardware::Void;

namespace vendor::qti::hardware::bluetooth_audio::V2_1 {

::android::hardware::Return<void> HidlBluetoothAudioProvider::startSession
    (
    const ::android::sp<::vendor::qti::hardware::bluetooth_audio::V2_0::IBluetoothAudioPort>& hostIf,
    const ::vendor::qti::hardware::bluetooth_audio::V2_0::AudioConfiguration& audioConfig,
    startSession_cb _hidl_cb
    )
{
    using namespace ::vendor::qti::hardware::bluetooth_audio::V2_0;

    LogDebug() << "start bluetooth audio session: " << toString( audioConfig );

    auto hidl_local_service = module_manager::get_instance()
        ->get_module<qcom_hidl_local_service>( qcom_hidl_local_service::s_module_name );
    std::function<void()> fun;
    fun = std::bind( &qcom_hidl_local_service::handle_update_bluetooth_port_interface, hidl_local_service,
                     hostIf );
    PageManager::GetInstance().PostEvent( std::make_shared<ExecutbleEvent>( fun ) );

    bluetooth_module::pcm_configuration selected_pcm_config;
    auto pcm = audioConfig.pcmConfig;
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
    _hidl_cb( ::vendor::qti::hardware::bluetooth_audio::V2_0::Status::SUCCESS, mq_descriptor );

    return Void();
}

::android::hardware::Return<void> HidlBluetoothAudioProvider::streamStarted
    (
    ::vendor::qti::hardware::bluetooth_audio::V2_0::Status status
    )
{
    if( status == ::vendor::qti::hardware::bluetooth_audio::V2_0::Status::SUCCESS )
    {
        LogDebug() << "bluetooth stream started.";
        auto hidl_local_service = module_manager::get_instance()
            ->get_module<qcom_hidl_local_service>( qcom_hidl_local_service::s_module_name );
        std::function<void()> fun;
        fun = std::bind( &qcom_hidl_local_service::trigger_stream_started_signal, hidl_local_service );
        PageManager::GetInstance().PostEvent( std::make_shared<ExecutbleEvent>( fun ) );
    }
    else
    {
        LogDebug() << "bluetooth stream not started, status: " << toString( status );
    }

    return Void();
}

::android::hardware::Return<void> HidlBluetoothAudioProvider::streamSuspended
    (
    ::vendor::qti::hardware::bluetooth_audio::V2_0::Status status 
    )
{
    if( status == ::vendor::qti::hardware::bluetooth_audio::V2_0::Status::SUCCESS )
    {
        LogDebug() << "bluetooth stream suspended.";
        auto hidl_local_service = module_manager::get_instance()
            ->get_module<qcom_hidl_local_service>( qcom_hidl_local_service::s_module_name );
        std::function<void()> fun;
        fun = std::bind( &qcom_hidl_local_service::trigger_stream_suspend_signal, hidl_local_service );
        PageManager::GetInstance().PostEvent( std::make_shared<ExecutbleEvent>( fun ) );
    }
    else
    {
        LogDebug() << "bluetooth stream not suspended, status: " << toString( status );
    }
    return Void();
}

::android::hardware::Return<void> HidlBluetoothAudioProvider::updateSessionParams
    (
    const ::vendor::qti::hardware::bluetooth_audio::V2_0::SessionParams& sessionParams
    )
{
    return Void();
}

::android::hardware::Return<void> HidlBluetoothAudioProvider::endSession()
{
    LogDebug() << "bluetooth audio session end";
    auto hidl_local_service = module_manager::get_instance()
        ->get_module<qcom_hidl_local_service>( qcom_hidl_local_service::s_module_name );
    std::function<void()> fun;
    fun = std::bind( &qcom_hidl_local_service::handle_bluetooth_audio_session_end, hidl_local_service );
    PageManager::GetInstance().PostEvent( std::make_shared<ExecutbleEvent>( fun ) );
    return Void();
}

::android::hardware::Return<void> HidlBluetoothAudioProvider::startSession_2_1
    (
    const ::android::sp<::vendor::qti::hardware::bluetooth_audio::V2_1::IBluetoothAudioPort>& hostIf,
    const ::vendor::qti::hardware::bluetooth_audio::V2_1::AudioConfiguration& audioConfig,
    startSession_2_1_cb _hidl_cb
    )
{

    using namespace ::vendor::qti::hardware::bluetooth_audio::V2_0;

    LogDebug() << "start bluetooth audio session for 2.1: " << toString( audioConfig );

    auto hidl_local_service = module_manager::get_instance()
        ->get_module<qcom_hidl_local_service>( qcom_hidl_local_service::s_module_name );
    std::function<void()> fun;
    fun = std::bind( &qcom_hidl_local_service::handle_update_bluetooth_port_interface_v21, hidl_local_service,
                     hostIf );
    PageManager::GetInstance().PostEvent( std::make_shared<ExecutbleEvent>( fun ) );

    bluetooth_module::pcm_configuration selected_pcm_config;
    auto pcm = audioConfig.pcmConfig;
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
    _hidl_cb( ::vendor::qti::hardware::bluetooth_audio::V2_0::Status::SUCCESS, mq_descriptor );

    return Void();
}

}

