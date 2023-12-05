#include <iostream>
#include <vector>

#include <binderwrapper/service.h>
#include <linux/MessageLooper.h>

class BluetoothService : public BnBluetoothService
{

public:

    void        RegisterObserver( android::sp<IObserver> a_observer )
    {
        m_observers.push_back( a_observer );
        auto fun = [this]()
            {
                std::vector<uint8_t> addr;
                for( auto& ele : m_observers )
                {
                    ele->A2dpActiveDeviceChanged( addr );
                }
            };
        MessageLooper::GetDefault().PostTask( fun );
    }

private:

    std::vector<android::sp<IObserver>> m_observers;
};


int main()
{
    android::sp<BluetoothService> service( new BluetoothService );
    auto desc = service->getInterfaceDescriptor();
    android::defaultServiceManager()->addService( desc, service );
    android::ProcessState::self()->startThreadPool();
    android::IPCThreadState::self()->joinThreadPool();

    std::cout << "Hello World!\n";
}
