#pragma once
#include <string>
#include <vector>
#include <hardware\audio.h>

#include "bluetooth_observer.h"

struct audio_component
{
    std::string name;
    std::string component;
};

class audio_component_config
{

public:

    static audio_component_config& get_instance();

    void add_component( audio_component a_component )
    {
        m_components.push_back( a_component );
    }

    void load_all_component();

    void handle_connection_status_changed( std::vector<uint8_t> a_addr, bool a_connected );

    void handle_active_device_changed( std::vector<uint8_t> a_addr );

private:

    audio_component_config();

    void register_observer();

    void load_android_bluetooth_audio();

    std::vector<audio_component> m_components;
    audio_module* m_audio_module = nullptr;
    hw_module_t m_module;
    audio_hw_device* m_audio_hw = nullptr;
    android::sp<IObserver> m_observer;
};

