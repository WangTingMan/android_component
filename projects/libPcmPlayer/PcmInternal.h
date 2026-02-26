#pragma once

#include "soundio/soundio.h"
#include <string>

#include "PcmPlayer.h"

class PcmInternalControlBlock
{

public:

    static PcmInternalControlBlock& GetInstance();

    PcmInternalControlBlock();

    ~PcmInternalControlBlock();

    struct SoundIo* soundio = nullptr;
    std::string deviceName;
};

SampleFormat SoundIoForMatToExternalFormat( SoundIoFormat a_sampleFormat );
SoundIoFormat ExternalFormatToSoundIoFormat( SampleFormat a_sampleFormat );

