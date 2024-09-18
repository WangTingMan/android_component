#include <windows.h>

#include <vendor/mediatek/hardware/bluetooth/audio/2.2/IBluetoothAudioProvidersFactory.h>

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

using vendor::mediatek::hardware::bluetooth::audio::V2_2::IBluetoothAudioProvidersFactory;
using ::android::hardware::Return;
using ::android::hardware::Void;
using ::android::hardware::hidl_vec;
using ::android::hardware::hidl_handle;
using ::android::hardware::hidl_string;

class BluetoothAudioProvidersFactory : public IBluetoothAudioProvidersFactory
{

public:

    ::android::hardware::Return<void> openProvider
        (
        ::vendor::mediatek::hardware::bluetooth::audio::V2_1::SessionType sessionType,
        openProvider_cb _hidl_cb
        ) override
    {
        return Void();
    }

    ::android::hardware::Return<void> getProviderCapabilities
        (
        ::vendor::mediatek::hardware::bluetooth::audio::V2_1::SessionType sessionType,
        getProviderCapabilities_cb _hidl_cb
        )override
    {
        return Void();
    }

    ::android::hardware::Return<void> openProvider_2_1
        (
        ::vendor::mediatek::hardware::bluetooth::audio::V2_2::SessionType sessionType,
        openProvider_2_1_cb _hidl_cb
        )override
    {
        return Void();
    }

    ::android::hardware::Return<void> getProviderCapabilities_2_1
        (
        ::vendor::mediatek::hardware::bluetooth::audio::V2_2::SessionType sessionType,
        getProviderCapabilities_2_1_cb _hidl_cb
        )override
    {
        return Void();
    }


};

extern "C"
{
    __declspec(dllexport) IBluetoothAudioProvidersFactory* HIDL_FETCH_IBluetoothAudioProvidersFactory(const char* /* name */)
    {
        return new BluetoothAudioProvidersFactory();
    }

}
