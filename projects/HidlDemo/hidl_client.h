#pragma once
#include <cstdint>
#include <functional>

struct hidl_callbacks
{
    std::function<void()> hci_initialized_cb;
};

enum class hci_data_type
{
    hci_cmd,
    hci_acl,
    hci_event,
    hci_iso,
    hci_sco
};

void hci_transmit( uint8_t* p_data, uint32_t a_size, hci_data_type a_type );

void hci_initialize();

void set_hidl_callbacks( hidl_callbacks a_cbs );
