#pragma once
#include <binderwrapper/observer.h>

class BluetoothObserver : public BnObserver
{

public:

    void A2dpConnectionStatusChanged( std::vector<uint8_t> a_addr, bool a_connected );

    void A2dpActiveDeviceChanged( std::vector<uint8_t> a_addr );
};

