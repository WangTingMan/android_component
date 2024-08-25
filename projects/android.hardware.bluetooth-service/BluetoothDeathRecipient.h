#pragma once
#include "BluetoothHci.h"

#include <aidl/android/hardware/bluetooth/BnBluetoothHci.h>
#include <aidl/android/hardware/bluetooth/IBluetoothHciCallbacks.h>

namespace aidl::android::hardware::bluetooth::impl {

void OnDeath( void* cookie );

class BluetoothDeathRecipient {
public:
  BluetoothDeathRecipient(BluetoothHci *hci) : mHci(hci) {}

  void LinkToDeath(const std::shared_ptr<IBluetoothHciCallbacks> &cb) {
    ALOGI("%s", __func__);
    mCb = cb;
    clientDeathRecipient_ = AIBinder_DeathRecipient_new(OnDeath);
    auto linkToDeathReturnStatus = AIBinder_linkToDeath(
        mCb->asBinder().get(), clientDeathRecipient_, this /* cookie */);

    if (linkToDeathReturnStatus != STATUS_OK) {
      ALOGE("%s: Unable to link to death recipient(%d)", __func__,
            linkToDeathReturnStatus);
    }
  }

  void UnlinkToDeath(const std::shared_ptr<IBluetoothHciCallbacks> &cb) {
    ALOGI("%s", __func__);
    if (cb != mCb) {
      ALOGE("Unable to unlink mismatched pointers");
    }
  }

  void serviceDied() {
    ALOGE("%s", __func__);
    if (mCb != nullptr && !AIBinder_isAlive(mCb->asBinder().get())) {
      ALOGE("Bluetooth remote service has died");
    } else {
      ALOGE("BluetoothDeathRecipient::serviceDied called but service not dead");
      return;
    }

    has_died_ = true;
    mHci->close();
  }
  BluetoothHci *mHci;
  std::shared_ptr<IBluetoothHciCallbacks> mCb;
  AIBinder_DeathRecipient *clientDeathRecipient_ = nullptr;
  bool getHasDied() const { return has_died_; }

private:
  bool has_died_{false};
};

}
