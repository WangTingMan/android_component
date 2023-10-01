/******************************************************************************
 *
 *  Copyright (C) 2017 Google, Inc.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at:
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 ******************************************************************************/

#define LOG_TAG "bt_hci"

#include "hidl_client.h"

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <base/location.h>
#include <base/logging.h>
#include <cutils/properties.h>

#include <android/hardware/bluetooth/1.0/IBluetoothHci.h>
#include <android/hardware/bluetooth/1.0/IBluetoothHciCallbacks.h>
#include <android/hardware/bluetooth/1.0/types.h>
#include <android/hardware/bluetooth/1.1/IBluetoothHci.h>
#include <android/hardware/bluetooth/1.1/IBluetoothHciCallbacks.h>
#include <hwbinder/ProcessState.h>
#include <hwbinder/IPCThreadState.h>
#include <linux/MessageLooper.h>

#define LOG_PATH "/data/misc/bluetooth/logs/firmware_events.log"
#define LAST_LOG_PATH "/data/misc/bluetooth/logs/firmware_events.log.last"

using android::hardware::IPCThreadState;
using android::hardware::bluetooth::V1_0::HciPacket;
using android::hardware::bluetooth::V1_0::Status;
using android::hardware::ProcessState;
using android::hardware::Return;
using android::hardware::Void;
using android::hardware::hidl_vec;
using namespace ::android::hardware::bluetooth;

static std::mutex bthci_mutex;

android::sp<V1_0::IBluetoothHci> btHci;
android::sp<V1_1::IBluetoothHci> btHci_1_1;
hidl_callbacks hidl_cbs;

const bool IsLazyHalSupported( property_get_bool( "ro.vendor.bt.enablelazyhal", false ) );

void set_hidl_callbacks( hidl_callbacks a_cbs )
{
    std::lock_guard<std::mutex> lcker( bthci_mutex );
    hidl_cbs = a_cbs;
}

class BluetoothHciCallbacks : public V1_1::IBluetoothHciCallbacks
{
public:
    BluetoothHciCallbacks()
    {
    }

    Return<void> initializationComplete( Status status )
    {
        if( status == Status::SUCCESS )
        {
            ALOGE( "%s: HCI Init OK ", __func__ );
            if( hidl_cbs.hci_initialized_cb )
            {
                hidl_cbs.hci_initialized_cb();
            }
            auto send_data_fun = []()
                {
                    ALOGI( "send hci command test..." );
                    std::vector<uint8_t> buffer;
                    buffer.push_back( 0x05 );
                    buffer.push_back( 0x06 );
                    buffer.push_back( 0x07 );
                    ::android::hardware::hidl_vec<uint8_t> cmd( buffer );
                    btHci->sendHciCommand( cmd );
                };
            MessageLooper::GetDefault().PostDelayTask( 1000, send_data_fun );
        }
        else
        {
            ALOGE( "%s: HCI Init failed ", __func__ );
        }
        return Void();
    }

    Return<void> hciEventReceived( const hidl_vec<uint8_t>& event )
    {
        return Void();
    }

    Return<void> aclDataReceived( const hidl_vec<uint8_t>& data )
    {
        ALOGI( "Received ACL data" );
        return Void();
    }

    Return<void> scoDataReceived( const hidl_vec<uint8_t>& data )
    {
        return Void();
    }

    Return<void> isoDataReceived( const hidl_vec<uint8_t>& data )
    {
        /* customized change based on the requirements */
        ALOGI( "%s", __func__ );
        return Void();
    }

};

void hci_initialize()
{
    ALOGI( "%s", __func__ );

    btHci_1_1 = V1_1::IBluetoothHci::getService();

    if( btHci_1_1 != nullptr )
    {
        ALOGI( "%s Using IBluetoothHci 1.1 service", __func__ );
        btHci = btHci_1_1;
    }
    else
    {
        ALOGI( "%s Using IBluetoothHci 1.0 service", __func__ );
        btHci = V1_0::IBluetoothHci::getService();
    }
    // If android.hardware.bluetooth* is not found, Bluetooth can not continue.
    CHECK( btHci != nullptr );
    ALOGI( "%s: IBluetoothHci::getService() returned %p (%s)",
              __func__, btHci.get(), ( btHci->isRemote() ? "remote" : "local" ) );

    // Block allows allocation of a variable that might be bypassed by goto.
    {
        android::sp<V1_1::IBluetoothHciCallbacks> callbacks =
            new BluetoothHciCallbacks();
        ALOGI( "Start initialize HCI" );
        auto hidl_daemon_status = btHci_1_1 != nullptr ?
            btHci_1_1->initialize_1_1( callbacks ) :
            btHci->initialize( callbacks );
        ALOGI( "HCI initialization started. Waiting for result." );

        if( !hidl_daemon_status.isOk() )
        {
            ALOGE( "%s: HIDL daemon is dead", __func__ );
            if( IsLazyHalSupported )
                IPCThreadState::self()->flushCommands();
            btHci = nullptr;
            btHci_1_1 = nullptr;
        }
    }
}

void hci_close()
{
    ALOGI( "%s", __func__ );

    std::lock_guard<std::mutex> lock( bthci_mutex );
    if( btHci != nullptr )
    {
        auto hidl_daemon_status = btHci->close();
        if( !hidl_daemon_status.isOk() )
            ALOGI( "%s: HIDL daemon is dead", __func__ );

        if( IsLazyHalSupported )
            IPCThreadState::self()->flushCommands();

        btHci = nullptr;
    }
}

void hci_transmit( uint8_t* p_data, uint32_t a_size, hci_data_type a_type )
{
    HciPacket data;
    std::lock_guard<std::mutex> lock( bthci_mutex );

    if( btHci == nullptr )
    {
        ALOGI( "%s: Link with Bluetooth HIDL service is closed", __func__ );
        return;
    }

    data.setToExternal( p_data, a_size );

    switch( a_type )
    {
    case hci_data_type::hci_cmd:
    {
        auto hidl_daemon_status = btHci->sendHciCommand( data );
        if( !hidl_daemon_status.isOk() )
        {
            ALOGE( "%s: send Command failed, HIDL daemon is dead", __func__ );
        }
        break;
    }
    case hci_data_type::hci_acl:
    {
        auto hidl_daemon_status = btHci->sendAclData( data );
        if( !hidl_daemon_status.isOk() )
        {
            ALOGE( "%s: send acl packet failed, HIDL daemon is dead", __func__ );
        }
        break;
    }
    case hci_data_type::hci_iso:
    {
        if( btHci_1_1 != nullptr )
        {
            auto hidl_daemon_status = btHci_1_1->sendIsoData( data );
            if( !hidl_daemon_status.isOk() )
            {
                ALOGE( "%s: send iso data failed, HIDL daemon is dead", __func__ );
            }
        }
        else
        {
            ALOGE( "ISO is not supported in HAL v1.0" );
        }
        break;
    }
    case hci_data_type::hci_sco:
    {
        auto hidl_daemon_status = btHci->sendScoData( data );
        if( !hidl_daemon_status.isOk() )
        {
            ALOGE( "%s: send sco data failed, HIDL daemon is dead", __func__ );
        }
        break;
    }
    default:
        ALOGE( "Unknown packet type (%d)", (uint32_t)a_type );
        break;
    }

    return;
}
