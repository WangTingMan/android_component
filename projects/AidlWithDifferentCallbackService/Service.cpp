#include "Service.h"

Service& Service::get_instance()
{
    static Service instance;
    return instance;
}

std::shared_ptr<AospBluetoothAudioProvider> Service::get_audio_provider(SessionType a_session)
{
    auto it = m_audio_providers.find(a_session);
    if (it != m_audio_providers.end())
    {
        return it->second;
    }

    std::shared_ptr<AospBluetoothAudioProvider> provider = nullptr;
    provider = ndk::SharedRefBase::make<AospBluetoothAudioProvider>();
    m_audio_providers[a_session] = provider;
    provider->setSessionType(a_session);
    std::string name = AospBluetoothAudioProvider::descriptor;
    name.append("/").append(toString(a_session));
    name = AospBluetoothAudioProvider::makeServiceName(toString(a_session));
    provider->setObjectName(name);
    return provider;
}
