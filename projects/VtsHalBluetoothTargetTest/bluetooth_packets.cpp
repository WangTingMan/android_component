
#include "gd/packet/bit_inserter.cc"
#include "gd/packet/byte_inserter.cc"
#include "gd/packet/byte_observer.cc"
#include "gd/packet/fragmenting_inserter.cc"
#include "gd/packet/iterator.cc"
#include "gd/packet/packet_view.cc"
#include "gd/packet/raw_builder.cc"
#include "gd/packet/view.cc"

#include "gd/hci/address.cc"
#include "log/src/vlog_android.cc"

#include <VtsCoreUtil.h>
#include <aidl/Gtest.h>
#include <aidl/Vintf.h>
#include <aidl/android/hardware/bluetooth/BnBluetoothHciCallbacks.h>
#include <aidl/android/hardware/bluetooth/IBluetoothHci.h>
#include <aidl/android/hardware/bluetooth/IBluetoothHciCallbacks.h>
#include <aidl/android/hardware/bluetooth/Status.h>
#include <android-base/properties.h>
#include <android/binder_auto_utils.h>
#include <android/binder_manager.h>
#include <android/binder_process.h>
#include <binder/IServiceManager.h>

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <future>
#include <queue>
#include <thread>
#include <utility>
#include <vector>

// TODO: Remove custom logging defines from PDL packets.
#undef LOG_INFO
#undef LOG_DEBUG
#undef LOG_TAG
#define LOG_TAG "VtsHalBluetooth"
#include "hci/hci_packets.h"
#include "packet/raw_builder.h"

void test()
{
    std::vector<uint8_t> cmd;
    ::bluetooth::packet::BitInserter bi{ cmd };
    ::bluetooth::hci::WriteSynchronousFlowControlEnableBuilder::Create(
        ::bluetooth::hci::Enable::ENABLED )
        ->Serialize( bi );

    cmd.clear();
    ::bluetooth::packet::BitInserter bi2{ cmd };
    ::bluetooth::hci::WriteLoopbackModeBuilder::Create(
        bluetooth::hci::LoopbackMode::ENABLE_LOCAL )
        ->Serialize( bi2 );

    std::vector<uint8_t> sco_packet;
    std::vector<uint8_t> payload;
    for( size_t i = 0; i < 30; i++ )
    {
        payload.push_back( static_cast<uint8_t>( i + 10 ) );
    }
    ::bluetooth::packet::BitInserter bi3{ sco_packet };
    ::bluetooth::hci::ScoBuilder::Create(
        0x1212, ::bluetooth::hci::PacketStatusFlag::CORRECTLY_RECEIVED, payload )
        ->Serialize( bi );

    int x = 0;
    x = 90;
}

