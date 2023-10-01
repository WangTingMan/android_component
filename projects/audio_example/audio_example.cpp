#include <iostream>
#include <vector>

#include <BluetoothAudioSession.h>
#include <BluetoothAudioProvidersFactory.h>

using namespace android::bluetooth::audio;
using namespace android::hardware::bluetooth::audio::V2_0::implementation;

int main()
{
    BluetoothAudioProvidersFactory fact;
    auto fun = []( ::android::hardware::bluetooth::audio::V2_0::Status status,
              const ::android::sp<::android::hardware::bluetooth::audio::V2_0::IBluetoothAudioProvider>& provider )
        {
            std::cout << "Hello World!\n";
        };
    fact.openProvider( SessionType::A2DP_SOFTWARE_ENCODING_DATAPATH, fun );

    BluetoothAudioSession session( SessionType::A2DP_SOFTWARE_ENCODING_DATAPATH );
    session.StartStream();

    system( "pause" );
    std::cout << "Hello World!\n";
}


