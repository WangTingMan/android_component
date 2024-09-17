#include "AospAidlBluetoothAudioProviderFactory.h"

namespace aidl::android::hardware::bluetooth::audio {

AospAidlBluetoothAudioProviderFactory::AospAidlBluetoothAudioProviderFactory()
{
    init();
    setBinderCreater( [ this ]()mutable->::ndk::SpAIBinder
                      {
                          return createBinder();
                      } );
    m_getProviderCapabilitiesFun = std::bind( &AospAidlBluetoothAudioProviderFactory::getProviderCapabilities,
                                              this, std::placeholders::_1, std::placeholders::_2 );
    m_openProviderFun = std::bind( &AospAidlBluetoothAudioProviderFactory::openProvider,
                                   this, std::placeholders::_1, std::placeholders::_2 );
    m_getProviderInfoFun = std::bind( &AospAidlBluetoothAudioProviderFactory::getProviderInfo,
                                      this, std::placeholders::_1, std::placeholders::_2 );
}

::ndk::ScopedAStatus AospAidlBluetoothAudioProviderFactory::getProviderCapabilities
    (
    SessionType in_sessionType,
    std::vector<AudioCapabilities>* _aidl_return
    )
{
    return ::ndk::ScopedAStatus( AStatus_newOk() );
}

::ndk::ScopedAStatus AospAidlBluetoothAudioProviderFactory::openProvider
    (
    SessionType in_sessionType,
    std::shared_ptr<IBluetoothAudioProvider>* _aidl_return
    )
{
    return ::ndk::ScopedAStatus( AStatus_newOk() );
}

::ndk::ScopedAStatus AospAidlBluetoothAudioProviderFactory::getProviderInfo
    (
    SessionType in_sessionType,
    std::optional<IBluetoothAudioProviderFactory::ProviderInfo>* _aidl_return
    )
{
    return ::ndk::ScopedAStatus( AStatus_newOk() );
}

void AospAidlBluetoothAudioProviderFactory::init()
{

}

}

