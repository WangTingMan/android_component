#pragma once
#include <future>
#include <list>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include "abstract_module.h"
#include "module/audio_types.h"
#include "module/local_audio_service.h"

namespace ndk {
    class SharedRefBase;
}

class ipc_manager_impl;

class ipc_manager : public abstract_module
{

public:

    static inline constexpr const char* s_module_name = "ipc_manager";

    ipc_manager();

    int init();

    void stop();

    void release();

    std::string get_fmq_json_descriptor();

    void start_stream();

    void stop_stream();

    void suspend_stream();

    void request_presentaion_delay();

    std::vector<bluetooth_module::pcm_configuration> get_local_supported_pcm_capabilities()
    {
        std::lock_guard locker(m_mutex);
        return m_local_psm_capabilities;
    }

public:

    void set_selected_pcm_configuration(bluetooth_module::pcm_configuration a_pcm_config);

private:

    void trigger_run();

    void run_detail(std::shared_ptr<std::promise<void>> a_promise);

    void load_config();

    std::thread m_running_thread;
    std::shared_ptr<ipc_manager_impl> m_impl;
    std::list<std::shared_ptr<local_audio_service>> m_audio_services;

    std::mutex m_mutex;
    bluetooth_module::pcm_configuration m_pcm_config;
    std::vector<bluetooth_module::pcm_configuration> m_local_psm_capabilities;
};

