#pragma once
#include <cstdint>
#include <memory>

#if defined(PCMPLAYER_IMPLEMENTATION)
#define PCMPLAYER_EXPORT __declspec(dllexport)
#else
#define PCMPLAYER_EXPORT __declspec(dllimport)
#endif  // defined(PCMPLAYER_IMPLEMENTATION)

struct PcmPlayerImpl;

enum class SampleFormat : char
{
    FormatInvalid,
    FormatS8,        ///< Signed 8 bit
    FormatU8,        ///< Unsigned 8 bit
    FormatS16LE,     ///< Signed 16 bit Little Endian
    FormatS16BE,     ///< Signed 16 bit Big Endian
    FormatU16LE,     ///< Unsigned 16 bit Little Endian
    FormatU16BE,     ///< Unsigned 16 bit Big Endian
    FormatS24LE,     ///< Signed 24 bit Little Endian using low three bytes in 32-bit word
    FormatS24BE,     ///< Signed 24 bit Big Endian using low three bytes in 32-bit word
    FormatU24LE,     ///< Unsigned 24 bit Little Endian using low three bytes in 32-bit word
    FormatU24BE,     ///< Unsigned 24 bit Big Endian using low three bytes in 32-bit word
    FormatS32LE,     ///< Signed 32 bit Little Endian
    FormatS32BE,     ///< Signed 32 bit Big Endian
    FormatU32LE,     ///< Unsigned 32 bit Little Endian
    FormatU32BE,     ///< Unsigned 32 bit Big Endian
    FormatFloat32LE, ///< Float 32 bit Little Endian, Range -1.0 to 1.0
    FormatFloat32BE, ///< Float 32 bit Big Endian, Range -1.0 to 1.0
    FormatFloat64LE, ///< Float 64 bit Little Endian, Range -1.0 to 1.0
    FormatFloat64BE, ///< Float 64 bit Big Endian, Range -1.0 to 1.0
};

class PCMPLAYER_EXPORT PcmPlayer
{

public:

    static PcmPlayer& GetInstance();

    void SetPcmParameters
        (
        uint32_t a_sampleFrequency,
        uint8_t a_chnnelCount,
        SampleFormat a_bitSize
        );

    /**
     * Play PCM data. a_data is the pointer point to
     * the data to play, and a_iLen is the total size
     * of the data to play.
     */
    void PlayPcmData
        (
        unsigned char* a_data,
        unsigned int a_iLen
        );

    /**
     * Play PCM data. a_data is the pointer point to
     * the data to play, and a_frameCount is the total frame
     * of the data to play. In this case, the total size
     * of the data chunk is 
     * a_frameCount * channel count * one frame size
     */
    void PlayPcmFrames
        (
        unsigned char* a_data,
        unsigned int a_frameCount
        );

    ~PcmPlayer();

    std::shared_ptr<PcmPlayerImpl> GetInternalImpl()
    {
        return m_impl;
    }

private:

    PcmPlayer();

    std::shared_ptr<PcmPlayerImpl> m_impl;
};
