#pragma once

#include "module/audio_types.h"
#include "module/local_audio_service.h"

class mtk_hidl_local_service : public local_audio_service
{

public:

    static inline constexpr const char* s_module_name = "mtk_hidl_local_service";

    mtk_hidl_local_service();

    int init();

    void stop();

    void release();

    void start_stream();

    void stop_stream();

    void suspend_stream();

private:

    void init_detail();

    void handle_initialization_completed();

};


