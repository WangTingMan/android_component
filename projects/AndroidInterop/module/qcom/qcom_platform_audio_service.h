#pragma once
#include "module/audio_types.h"
#include "module/local_audio_service.h"

#include <bluetooth_audio_interface.h>

class qcom_platform_audio_service : public local_audio_service
{

public:

    static inline constexpr const char* s_module_name = "qcom_platform_audio_service";

    qcom_platform_audio_service();

    int init();

    void stop();

    void release();

    void start_stream();

    void stop_stream();

    void suspend_stream();

    void request_presentaion_delay();

    bool is_enabled();

private:

    void create_qcom_local_service();

    void async_schedule_task(bluetooth_audio_interface::async_task_type a_tsk, int a_execute_time);

    void* m_platform_lib = nullptr;
    bluetooth_audio_interface* m_low_level_interface = nullptr;
};

