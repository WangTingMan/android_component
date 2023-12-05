#include "bluetooth_observer.h"
#include "audio_component_config.h"

#include <linux/MessageLooper.h>

void BluetoothObserver::A2dpConnectionStatusChanged( std::vector<uint8_t> a_addr, bool a_connected )
{
    MessageLooper::GetDefault().PostTask(
        std::bind( &audio_component_config::handle_connection_status_changed,
                   std::ref( audio_component_config::get_instance() ),
                   a_addr,
                   a_connected ) );
}

void BluetoothObserver::A2dpActiveDeviceChanged( std::vector<uint8_t> a_addr )
{
    MessageLooper::GetDefault().PostDelayTask(2000,
        std::bind( &audio_component_config::handle_active_device_changed,
                   std::ref( audio_component_config::get_instance() ),
                   a_addr ) );
}

