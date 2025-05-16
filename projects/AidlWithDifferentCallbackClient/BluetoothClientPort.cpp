#include "BluetoothClientPort.h"

::ndk::ScopedAStatus BluetoothPort::getPresentationPosition(::aidl::android::hardware::bluetooth::audio::PresentationPosition* _aidl_return)
{

    return ::ndk::ScopedAStatus(AStatus_newOk());
}

::ndk::ScopedAStatus BluetoothPort::startStream(bool in_isLowLatency)
{

    return ::ndk::ScopedAStatus(AStatus_newOk());
}

::ndk::ScopedAStatus BluetoothPort::stopStream()
{

    return ::ndk::ScopedAStatus(AStatus_newOk());
}

::ndk::ScopedAStatus BluetoothPort::suspendStream()
{

    return ::ndk::ScopedAStatus(AStatus_newOk());
}

::ndk::ScopedAStatus BluetoothPort::updateSourceMetadata(const ::aidl::android::hardware::audio::common::SourceMetadata& in_sourceMetadata)
{

    return ::ndk::ScopedAStatus(AStatus_newOk());
}

::ndk::ScopedAStatus BluetoothPort::updateSinkMetadata(const ::aidl::android::hardware::audio::common::SinkMetadata& in_sinkMetadata)
{

    return ::ndk::ScopedAStatus(AStatus_newOk());
}

::ndk::ScopedAStatus BluetoothPort::setLatencyMode(::aidl::android::hardware::bluetooth::audio::LatencyMode in_latencyMode)
{

    return ::ndk::ScopedAStatus(AStatus_newOk());
}

::ndk::ScopedAStatus BluetoothPort::getInterfaceVersion(int32_t* _aidl_return)
{

    return ::ndk::ScopedAStatus(AStatus_newOk());
}

::ndk::ScopedAStatus BluetoothPort::getInterfaceHash(std::string* _aidl_return)
{

    return ::ndk::ScopedAStatus(AStatus_newOk());
}
