#pragma once

#include "../abstract_module.h"
#include "module/audio_types.h"
#include "module/local_audio_service.h"

#include <mutex>

class aosp_aidl_local_service : public local_audio_service
{

public:

    static inline constexpr const char* s_module_name = "aosp_aidl_local_service";

    aosp_aidl_local_service();

    int init();

    void stop();

    void release();

    void start_stream();

    void stop_stream();

    void suspend_stream();

private:

    friend class AidlBluetoothAudioProvider;

    void handle_audio_stream_started( bluetooth_module::a2dp_stream_status a_status );

    void handle_audio_stream_suspended( bluetooth_module::a2dp_stream_status a_status );

private:

    void init_detail();

    std::recursive_mutex m_mutex;
};

