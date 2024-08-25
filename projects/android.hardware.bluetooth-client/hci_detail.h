#pragma once
#include "hci_backend.h"

namespace bluetooth::hal {

class HciBackendCallbacksDetail : public HciBackendCallbacks
{
 public:
  virtual ~HciBackendCallbacksDetail() = default;
  virtual void initializationComplete(void);
  virtual void hciEventReceived(const std::vector<uint8_t>&);
  virtual void aclDataReceived(const std::vector<uint8_t>&);
  virtual void scoDataReceived(const std::vector<uint8_t>&);
  virtual void isoDataReceived(const std::vector<uint8_t>&);
};

}
