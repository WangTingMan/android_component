#include "hci_detail.h"

namespace bluetooth::hal {

void HciBackendCallbacksDetail::initializationComplete(void)
{
}

void HciBackendCallbacksDetail::hciEventReceived( const std::vector<uint8_t>& )
{
}

void HciBackendCallbacksDetail::aclDataReceived( const std::vector<uint8_t>& )
{
}

void HciBackendCallbacksDetail::scoDataReceived( const std::vector<uint8_t>& )
{
}

void HciBackendCallbacksDetail::isoDataReceived( const std::vector<uint8_t>& )
{
}


}
