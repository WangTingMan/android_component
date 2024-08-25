#include "BluetoothHci.h"
#include "BluetoothDeathRecipient.h"

namespace aidl::android::hardware::bluetooth::impl {

    BluetoothHci::BluetoothHci()
    {
        mDeathRecipient = std::make_shared<BluetoothDeathRecipient>( this );
#ifdef _MSC_VER
        setBinderCreater( [ this ]()mutable->::ndk::SpAIBinder
                          {
                              return createBinder();
                          } );
        m_initializer = std::bind( &BluetoothHci::initialize, this, std::placeholders::_1 );
        m_closer = std::bind( &BluetoothHci::close, this );
        m_acldataSender = std::bind( &BluetoothHci::sendAclData, this, std::placeholders::_1 );
        m_cmddataSender = std::bind( &BluetoothHci::sendHciCommand, this, std::placeholders::_1 );
        m_isodataSender = std::bind( &BluetoothHci::sendIsoData, this, std::placeholders::_1 );
        m_scodataSender = std::bind( &BluetoothHci::sendScoData, this, std::placeholders::_1 );
#endif
    }

    ndk::ScopedAStatus BluetoothHci::initialize(
        const std::shared_ptr<IBluetoothHciCallbacks>& cb )
    {
        mCb = cb;
        mDeathRecipient->LinkToDeath( cb );
        ndk::ScopedAStatus status = ndk::ScopedAStatus::ok();
        return status;
    }

    ndk::ScopedAStatus BluetoothHci::sendHciCommand(
        const std::vector<uint8_t>& packet )
    {
        ndk::ScopedAStatus status = ndk::ScopedAStatus::ok();
        return status;
    }

    ndk::ScopedAStatus BluetoothHci::sendAclData( const std::vector<uint8_t>& packet )
    {
        ndk::ScopedAStatus status = ndk::ScopedAStatus::ok();
        return status;
    }

    ndk::ScopedAStatus BluetoothHci::sendScoData( const std::vector<uint8_t>& packet )
    {
        ndk::ScopedAStatus status = ndk::ScopedAStatus::ok();
        return status;
    }

    ndk::ScopedAStatus BluetoothHci::sendIsoData( const std::vector<uint8_t>& packet )
    {
        ndk::ScopedAStatus status = ndk::ScopedAStatus::ok();
        return status;
    }

    ndk::ScopedAStatus BluetoothHci::close()
    {
        if( mCb != nullptr )
        {
            mDeathRecipient->UnlinkToDeath( mCb );
        }
        ndk::ScopedAStatus status = ndk::ScopedAStatus::ok();
        return status;
    }


}

