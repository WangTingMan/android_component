
#include "BluetoothDeathRecipient.h"

namespace aidl::android::hardware::bluetooth::impl {

void OnDeath(void* cookie) {
  auto* death_recipient = static_cast<BluetoothDeathRecipient*>(cookie);
  death_recipient->serviceDied();
}



}
