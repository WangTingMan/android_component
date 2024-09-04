#pragma once

#include "../abstract_module.h"
#include "module/audio_types.h"
#include "AidlBluetoothAudioProviderFactory.h"
#include <aidl/vendor/mediatek/hardware/bluetooth/audio/IBluetoothAudioProvider.h>

#include <mutex>

namespace aidl::vendor::mediatek::hardware::bluetooth::audio {
    class AidlBluetoothAudioProvider;
}

class mtk_aidl_local_service : public abstract_module
{

public:

    using BluetoothAudioProviderFactory = ::aidl::vendor::mediatek
        ::hardware::bluetooth::audio::BluetoothAudioProviderFactory;
    using IBluetoothAudioPort = ::aidl::vendor::mediatek
        ::hardware::bluetooth::audio::IBluetoothAudioPort;
    using AidlBluetoothAudioProvider = ::aidl::vendor::mediatek
        ::hardware::bluetooth::audio::AidlBluetoothAudioProvider;

    static inline constexpr const char* s_module_name = "mtk_aidl_local_service";

    mtk_aidl_local_service();

    int init();

    void stop();

    void release();

    void update_bluetooth_audio_port(std::shared_ptr<IBluetoothAudioPort> a_bluetoothAudioPort);

private:

    friend class AidlBluetoothAudioProvider;

    void handle_audio_stream_started(bluetooth_module::a2dp_stream_status a_status);

    void handle_audio_stream_suspended(bluetooth_module::a2dp_stream_status a_status);

private:

    void init_detail();

    std::recursive_mutex m_mutex;
    std::shared_ptr<BluetoothAudioProviderFactory> m_service;
    std::shared_ptr<IBluetoothAudioPort> m_bluetooth_audio_port;
};

