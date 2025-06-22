#include "BluetoothClientPort.h"
#include <iostream>
#include <map>
#include <binder/IPCThreadState.h>
#include <android\binder_manager.h>
#include <base/logging.h>

#include <aidl\android\hardware\bluetooth\audio\IBluetoothAudioProviderFactory.h>

int main()
{
#ifdef __set_default_log_file_name_defined
    __set_default_log_file_name(nullptr, true);
#endif

    using ::aidl::android::hardware::bluetooth::audio::
        IBluetoothAudioProviderFactory;
    using ::aidl::android::hardware::bluetooth::audio::IBluetoothAudioProvider;
    using ::aidl::android::hardware::bluetooth::audio::SessionType;
    const std::string kDefaultAudioProviderFactoryInterface =
        std::string() + IBluetoothAudioProviderFactory::descriptor + "/default_test";

    std::shared_ptr<IBluetoothAudioProviderFactory> provider_factory;
    std::map<SessionType, std::shared_ptr<IBluetoothAudioProvider>> audio_providers;
    int version = 0;

    if (AServiceManager_checkService(
        kDefaultAudioProviderFactoryInterface.c_str()) != nullptr) {
        LOG(INFO) << __func__ << ": Going with AIDL: ";

        provider_factory = IBluetoothAudioProviderFactory::fromBinder(
            ::ndk::SpAIBinder(AServiceManager_waitForService(
                kDefaultAudioProviderFactoryInterface.c_str())));
        if (!provider_factory)
        {
            return 0;
        }
    }

    auto aidl_retval = provider_factory->m_getInterfaceVersion(&version);
    std::vector<SessionType> types;
    types.push_back(SessionType::HEARING_AID_SOFTWARE_ENCODING_DATAPATH);
    types.push_back(SessionType::A2DP_SOFTWARE_ENCODING_DATAPATH);
    types.push_back(SessionType::A2DP_HARDWARE_OFFLOAD_DECODING_DATAPATH);
    types.push_back(SessionType::LE_AUDIO_SOFTWARE_ENCODING_DATAPATH);
    types.push_back(SessionType::LE_AUDIO_SOFTWARE_DECODING_DATAPATH);
    types.push_back(SessionType::LE_AUDIO_HARDWARE_OFFLOAD_ENCODING_DATAPATH);
    for (auto& ele : types)
    {
        std::shared_ptr<::aidl::android::hardware::bluetooth::audio::IBluetoothAudioProvider> _aidl_return;
        provider_factory->m_openProviderFun(ele, &_aidl_return);
        if (_aidl_return)
        {
            audio_providers[ele] = _aidl_return;
        }
    }

    std::shared_ptr<::aidl::android::hardware::bluetooth::audio::IBluetoothAudioProvider> _aidl_return;
    provider_factory->m_openProviderFun(SessionType::A2DP_HARDWARE_OFFLOAD_DECODING_DATAPATH, &_aidl_return);

    for (auto& ele : audio_providers)
    {
        SessionType type = ele.first;
        ele.second->m_setLowLatencyModeAllowed(true);
        std::cout << "Session: " << toString(type) << ", set low latency mode allowed\n";
    }

    android::IPCThreadState::self()->joinThreadPool();
    std::cout << "Hello World!\n";
    return 0;
}

