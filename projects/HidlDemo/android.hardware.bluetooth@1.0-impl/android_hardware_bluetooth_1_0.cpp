#include <android/hardware/bluetooth/1.0/IBluetoothHci.h>
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>
#include <log/log.h>
#include <linux/MessageLooper.h>
#include <hwbinder/IPCThreadState.h>

using ::android::hardware::Return;
using ::android::hardware::Void;
using ::android::hardware::hidl_vec;
using ::android::hardware::bluetooth::V1_0::IBluetoothHci;
using ::android::hardware::bluetooth::V1_0::IBluetoothHciCallbacks;
using ::android::hardware::hidl_handle;
using ::android::hardware::hidl_string;

::android::sp<IBluetoothHciCallbacks> s_cb;

class BluetoothHci : public IBluetoothHci
{

public:

    BluetoothHci()
    {
        ALOGI( "create new bluetooth hci instance." );
    }

    Return<void> initialize(
        const ::android::sp<IBluetoothHciCallbacks>& cb ) override
    {
        auto currrent_ipc_state = android::hardware::IPCThreadState::self();
        if( currrent_ipc_state )
        {
            pid_t calling_pid = currrent_ipc_state->getCallingPid();
            const char* calling_sid = currrent_ipc_state->getCallingSid();
            if( !calling_sid )
            {
                calling_sid = "No calling sid";
            }
            uid_t calling_uid = currrent_ipc_state->getCallingUid();
        }

        ALOGI( "initialize" );
        ::android::hardware::Return<void> ret;
        ret = cb->initializationComplete( ::android::hardware::bluetooth::V1_0::Status::SUCCESS );
        s_cb = cb;
        bool status = ret.isOk();
        auto send_data_fun = []()
            {
                ALOGI( "send ACL data test..." );
                std::vector<uint8_t> buffer;
                buffer.push_back( 0x01 );
                buffer.push_back( 0x02 );
                buffer.push_back( 0x03 );
                ::android::hardware::hidl_vec<uint8_t> data( buffer );
                s_cb->aclDataReceived( data );
            };

        MessageLooper::GetDefault().PostDelayTask( 2000, send_data_fun );
        return Void();
    }

    Return<void> sendHciCommand( const hidl_vec<uint8_t>& packet ) override
    {
        ALOGI( "sendHciCommand" );
        return Void();
    }

    Return<void> sendAclData( const hidl_vec<uint8_t>& data ) override
    {
        ALOGI( "sendAclData" );
        return Void();
    }

    Return<void> sendScoData( const hidl_vec<uint8_t>& data ) override
    {
        ALOGI( "sendScoData" );
        return Void();
    }

    Return<void> close() override
    {
        ALOGI( "close" );
        return Void();
    }

    Return<void> debug( const hidl_handle& handle,
                        const hidl_vec<hidl_string>& options ) override
    {
        ALOGI( "debug" );
        return Void();
    }

private:

};

extern "C"
{
    __declspec( dllexport ) IBluetoothHci* HIDL_FETCH_IBluetoothHci( const char* /* name */ )
    {
        return new BluetoothHci();
    }

}
