#pragma once
#include <future>
#include <list>
#include <memory>
#include <thread>

#include "abstract_module.h"

namespace ndk {
    class SharedRefBase;
}

class ipc_manager : public abstract_module
{

public:

    static inline constexpr const char* s_module_name = "ipc_manager";

    ipc_manager();

    int init();

    void stop();

    void release();

private:

    void trigger_run();

    void run_detail(std::shared_ptr<std::promise<void>> a_promise);

    std::thread m_running_thread;
};

