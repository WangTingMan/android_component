#include <iostream>

#include <BluetoothAudioSession.h>

using namespace android::bluetooth::audio;

int main()
{
    BluetoothAudioSession session( SessionType::A2DP_SOFTWARE_ENCODING_DATAPATH );
    session.StartStream();

    system( "pause" );
    std::cout << "Hello World!\n";
}


