#pragma once
#include <map>
#include "AospBluetoothAudioProvider.h"

#include <aidl\android\hardware\bluetooth\audio\SessionType.h>

class Service
{

public:

    using SessionType = aidl::android::hardware::bluetooth::audio::SessionType;

    static Service& get_instance();

    std::shared_ptr<AospBluetoothAudioProvider> get_audio_provider(SessionType a_session);

private:

    std::map<SessionType, std::shared_ptr<AospBluetoothAudioProvider>> m_audio_providers;
};

