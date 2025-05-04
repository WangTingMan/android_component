#pragma once

#include "module/audio_types.h"
#include "module/local_audio_service.h"

#include <vendor/mediatek/hardware/bluetooth/audio/2.1/IBluetoothAudioProvider.h>
#include <vendor/mediatek/hardware/bluetooth/audio/2.1/IBluetoothAudioPort.h>
#include <mutex>

class mtk_hidl_local_service : public local_audio_service
{

public:

    using IBluetoothAudioProvider = ::vendor::mediatek::hardware::bluetooth::audio::V2_1::IBluetoothAudioProvider;

    using IBluetoothAudioPort = ::vendor::mediatek::hardware::bluetooth::audio::V2_1::IBluetoothAudioPort;

    static inline constexpr const char* s_module_name = "mtk_hidl_local_service";

    mtk_hidl_local_service();

    int init();

    void stop();

    void release();

    void start_stream();

    void stop_stream();

    void suspend_stream();

    void request_presentaion_delay();

    ::android::sp<IBluetoothAudioProvider> get_audio_provider()
    {
        std::lock_guard locker( m_mutex );
        return m_bluetooth_audio_provider;
    }

    void handle_update_bluetooth_port_interface( ::android::sp<IBluetoothAudioPort> a_bluetooth_audio_port );

    void handle_bluetooth_audio_session_end();

    bool is_enabled()
    {
        return static_cast<bool>(m_bluetooth_audio_provider);
    }

private:

    void get_presentation();

    void init_detail();

    /**
     * Remote call this function
     */
    void presentation_updated
        (
        ::vendor::mediatek::hardware::bluetooth::audio::V2_1::Status status,
        uint64_t remoteDeviceAudioDelayNanos,
        uint64_t transmittedOctets,
        const ::vendor::mediatek::hardware::bluetooth::audio::V2_1::TimeSpec& transmittedOctetsTimeStamp
        );

    void handle_initialization_completed( ::android::sp<IBluetoothAudioProvider> a_provider );

    ::android::sp<IBluetoothAudioPort> m_bluetooth_audio_port;

    std::mutex m_mutex;
    ::android::sp<IBluetoothAudioProvider> m_bluetooth_audio_provider;
};


