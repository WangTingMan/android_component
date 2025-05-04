#pragma once

#include "../abstract_module.h"
#include "module/audio_types.h"
#include "module/local_audio_service.h"

#include <mutex>

namespace aidl::android::hardware::bluetooth::audio {
    class AospAidlBluetoothAudioProviderFactory;
    class IBluetoothAudioPort;
}

class aosp_aidl_local_service : public local_audio_service
{

public:

    using AospAidlBluetoothAudioProviderFactory = 
        aidl::android::hardware::bluetooth::audio::AospAidlBluetoothAudioProviderFactory;
    using IBluetoothAudioPort =
        aidl::android::hardware::bluetooth::audio::IBluetoothAudioPort;

    static inline constexpr const char* s_module_name = "aosp_aidl_local_service";

    aosp_aidl_local_service();

    int init();

    void stop();

    void release();

    void start_stream();

    void stop_stream();

    void suspend_stream();

    void request_presentaion_delay();

    bool is_enabled()
    {
        return static_cast<bool>(m_service);
    }

    void handle_update_bluetooth_port_interface(std::shared_ptr<IBluetoothAudioPort> a_stack_bt_interface)
    {
        m_stack_bt_interface = a_stack_bt_interface;
    }

private:

    friend class AidlBluetoothAudioProvider;

    void handle_audio_stream_started( bluetooth_module::a2dp_stream_status a_status );

    void handle_audio_stream_suspended( bluetooth_module::a2dp_stream_status a_status );

private:

    void init_detail();

    void handle_initialization_completed(std::shared_ptr<AospAidlBluetoothAudioProviderFactory> a_service);

    std::shared_ptr<IBluetoothAudioPort> m_stack_bt_interface;

    std::recursive_mutex m_mutex;
    std::shared_ptr<AospAidlBluetoothAudioProviderFactory> m_service;
};

