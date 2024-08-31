#pragma once

#include "../abstract_module.h"
#include "AidlBluetoothAudioProviderFactory.h"
#include <aidl/vendor/mediatek/hardware/bluetooth/audio/IBluetoothAudioProvider.h>

#include <mutex>

class mtk_aidl_local_service : public abstract_module
{

public:

    using BluetoothAudioProviderFactory = ::aidl::vendor::mediatek
        ::hardware::bluetooth::audio::BluetoothAudioProviderFactory;
    using IBluetoothAudioPort = ::aidl::vendor::mediatek
        ::hardware::bluetooth::audio::IBluetoothAudioPort;

    static inline constexpr const char* s_module_name = "mtk_aidl_local_service";

    mtk_aidl_local_service();

    int init();

    void stop();

    void release();

    void update_bluetooth_audio_port(std::shared_ptr<IBluetoothAudioPort> a_bluetoothAudioPort);

private:

    void init_detail();

    std::recursive_mutex m_mutex;
    std::shared_ptr<BluetoothAudioProviderFactory> m_service;
    std::shared_ptr<IBluetoothAudioPort> m_bluetooth_audio_port;
};

