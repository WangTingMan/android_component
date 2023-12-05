#include <iostream>
#include <binderwrapper/observer.h>
#include <binderwrapper/service.h>
#include <linux/MessageLooper.h>

class BluetoothObserver : public BnObserver
{

public:

    void A2dpConnectionStatusChanged( std::vector<uint8_t> a_addr, bool a_connected );

    void A2dpActiveDeviceChanged( std::vector<uint8_t> a_addr );
};

class LocalRegistrationCallbackObserver : public android::IServiceManager::LocalRegistrationCallback
{

public:

    void onServiceRegistration( const android::String16& instance, const android::sp<android::IBinder>& binder )
    {
        android::sp<IBluetoothService> iservice = interface_cast<IBluetoothService>( binder );
        android::sp<IObserver> observer = android::sp<BluetoothObserver>::make();
        iservice->RegisterObserver( observer );
    }

};

int main()
{
    android::sp<android::IServiceManager> sm = android::defaultServiceManager();
    sm->registerForNotifications( android::String16( IBluetoothService::descriptor ),
                                  android::sp<LocalRegistrationCallbackObserver>::make() );

    android::IPCThreadState::self()->joinThreadPool();
    std::system( "pause" );
    return 0;
}

void BluetoothObserver::A2dpConnectionStatusChanged( std::vector<uint8_t> a_addr, bool a_connected )
{
}

void BluetoothObserver::A2dpActiveDeviceChanged( std::vector<uint8_t> a_addr )
{
}
