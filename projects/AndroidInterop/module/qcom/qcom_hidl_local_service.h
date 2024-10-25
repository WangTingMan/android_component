#pragma once

#include "module/audio_types.h"
#include "module/local_audio_service.h"

#include <vendor/qti/hardware/bluetooth_audio/2.1/IBluetoothAudioProvidersFactory.h>
#include <vendor/qti/hardware/bluetooth_audio/2.1/IBluetoothAudioPort.h>
#include <mutex>

class qcom_hidl_local_service : public local_audio_service
{

public:

    using IBluetoothAudioProvider = ::vendor::qti::hardware::bluetooth_audio::V2_1::IBluetoothAudioProvider;

    using IBluetoothAudioPort = ::vendor::qti::hardware::bluetooth_audio::V2_0::IBluetoothAudioPort;

    using IBluetoothAudioPortV21 = ::vendor::qti::hardware::bluetooth_audio::V2_1::IBluetoothAudioPort;

    static inline constexpr const char* s_module_name = "qcom_hidl_local_service";

    qcom_hidl_local_service();

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

    void handle_update_bluetooth_port_interface_v21( ::android::sp<IBluetoothAudioPortV21> a_bluetooth_audio_port );

    void handle_bluetooth_audio_session_end();

private:

    void get_presentation();

    void init_detail();

    /**
     * Remote call this function
     */
    void presentation_updated
        (
        ::vendor::qti::hardware::bluetooth_audio::V2_0::Status status,
        uint64_t remoteDeviceAudioDelayNanos,
        uint64_t transmittedOctets,
        const ::vendor::qti::hardware::bluetooth_audio::V2_0::TimeSpec& transmittedOctetsTimeStamp
        );

    void handle_initialization_completed( ::android::sp<IBluetoothAudioProvider> a_provider );

    ::android::sp<IBluetoothAudioPort> m_bluetooth_audio_port;
    ::android::sp<IBluetoothAudioPortV21> m_bluetooth_audio_port_v2_1;

    std::mutex m_mutex;
    ::android::sp<IBluetoothAudioProvider> m_bluetooth_audio_provider;
};


