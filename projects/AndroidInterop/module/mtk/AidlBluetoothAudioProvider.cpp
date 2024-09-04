#include "AidlBluetoothAudioProvider.h"
#include "../module_manager.h"
#include "mtk_aidl_local_service.h"
#include "utils.h"

#include <Zhen/PageManager.h>
#include <Zhen/ExecutbleEvent.h>

namespace aidl::vendor::mediatek::hardware::bluetooth::audio {

AidlBluetoothAudioProvider::AidlBluetoothAudioProvider()
{
    using namespace std::placeholders;
    m_endSessionFun = std::bind(&AidlBluetoothAudioProvider::endSession, this);
    m_startSessionFun = std::bind( &AidlBluetoothAudioProvider::startSession, this, _1, _2, _3, _4 );
    m_streamStartedFun = std::bind( &AidlBluetoothAudioProvider::streamStarted, this, _1 );
    m_streamSuspendedFun = std::bind( &AidlBluetoothAudioProvider::streamSuspended, this, _1 );
    m_updateAudioConfigurationFun = std::bind( &AidlBluetoothAudioProvider::updateAudioConfiguration, this, _1 );
    m_setLowLatencyModeAllowedFun = std::bind( &AidlBluetoothAudioProvider::setLowLatencyModeAllowed, this, _1 );
    m_enterGameModeFun = std::bind( &AidlBluetoothAudioProvider::enterGameMode, this, _1 );
    m_updataConnParamFun = std::bind( &AidlBluetoothAudioProvider::updataConnParam, this, _1 );
}

::ndk::ScopedAStatus AidlBluetoothAudioProvider::endSession()
{
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
    auto mtk_module = module_manager::get_instance()
        ->get_module<mtk_aidl_local_service>(mtk_aidl_local_service::s_module_name);
    mtk_module->update_bluetooth_audio_port(in_hostIf);
    return ndk::ScopedAStatus::ok();
}

::ndk::ScopedAStatus AidlBluetoothAudioProvider::streamStarted( BluetoothAudioStatus in_status )
{
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
    return ndk::ScopedAStatus::ok();
}

::ndk::ScopedAStatus AidlBluetoothAudioProvider::setLowLatencyModeAllowed( bool in_allowed )
{
    return ndk::ScopedAStatus::ok();
}

::ndk::ScopedAStatus AidlBluetoothAudioProvider::enterGameMode( int8_t in_enter )
{
    return ndk::ScopedAStatus::ok();
}

::ndk::ScopedAStatus AidlBluetoothAudioProvider::updataConnParam( const ConnParam& in_connPrameter )
{
    return ndk::ScopedAStatus::ok();
}

}
