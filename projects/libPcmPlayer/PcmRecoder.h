#pragma once
#include <cstdint>
#include <memory>
#include <functional>
#include <vector>

#include "PcmPlayer.h"

#if defined(PCMPLAYER_IMPLEMENTATION)
#define PCMPLAYER_EXPORT __declspec(dllexport)
#else
#define PCMPLAYER_EXPORT __declspec(dllimport)
#endif  // defined(PCMPLAYER_IMPLEMENTATION)

struct PcmRecoderImpl;

struct SampleRateRange
{
    int min;
    int max;
};

class PCMPLAYER_EXPORT PcmRecoder
{

public:

    bool open
        (
        SampleFormat a_format,
        uint32_t a_sampleRate,
        std::function<void( void*, uint32_t )> a_dataCallback
        );

    void close();

    std::vector<SampleFormat> GetSupportedFormats();

    std::vector<SampleRateRange> GetSampleRates();

    SampleFormat GetCurrentSampleFormat();

    uint32_t GetCurrentSampleRate();

    uint8_t GetChannelCount();

    void SetPcmDataCallback( std::function<void(void*,uint32_t)> );

    static PcmRecoder& GetInstance();

public:

    std::shared_ptr<PcmRecoderImpl> m_impl;

private:

    PcmRecoder();
};

