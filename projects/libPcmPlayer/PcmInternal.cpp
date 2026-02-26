#include "PcmInternal.h"

PcmInternalControlBlock::PcmInternalControlBlock()
{
    soundio = soundio_create();
    soundio_connect_backend( soundio, SoundIoBackendWasapi );
    deviceName.assign( soundio_backend_name( soundio->current_backend ) );

    soundio_flush_events( soundio );
}

PcmInternalControlBlock::~PcmInternalControlBlock()
{
    if( soundio )
    {
        soundio_destroy( soundio );
        soundio = nullptr;
    }
}

PcmInternalControlBlock& PcmInternalControlBlock::GetInstance()
{
    static PcmInternalControlBlock instance;
    return instance;
}

SampleFormat SoundIoForMatToExternalFormat( SoundIoFormat a_sampleFormat )
{
    SampleFormat format = SampleFormat::FormatInvalid;
    switch( a_sampleFormat )
    {
    case SoundIoFormatS8:        ///< Signed 8 bit
        format = SampleFormat::FormatS8;
        break;
    case SoundIoFormatU8:        ///< Unsigned 8 bit  
        format = SampleFormat::FormatU8;
        break;
    case SoundIoFormatS16LE:     ///< Signed 16 bit Little Endian 
        format = SampleFormat::FormatS16LE;
        break;
    case SoundIoFormatS16BE:     ///< Signed 16 bit Big Endian  
        format = SampleFormat::FormatS16BE;
        break;
    case SoundIoFormatU16LE:     ///< Unsigned 16 bit Little Endian 
        format = SampleFormat::FormatU16LE;
        break;
    case SoundIoFormatU16BE:     ///< Unsigned 16 bit Big Endian   
        format = SampleFormat::FormatU16BE;
        break;
    case SoundIoFormatS24LE:     ///< Signed 24 bit Little Endian using low three bytes in 32-bit word  
        format = SampleFormat::FormatS24LE;
        break;
    case SoundIoFormatS24BE:     ///< Signed 24 bit Big Endian using low three bytes in 32-bit word 
        format = SampleFormat::FormatS24BE;
        break;
    case SoundIoFormatU24LE:     ///< Unsigned 24 bit Little Endian using low three bytes in 32-bit word  
        format = SampleFormat::FormatU24LE;
        break;
    case SoundIoFormatU24BE:     ///< Unsigned 24 bit Big Endian using low three bytes in 32-bit word    
        format = SampleFormat::FormatU24BE;
        break;
    case SoundIoFormatS32LE:     ///< Signed 32 bit Little Endian    
        format = SampleFormat::FormatS32LE;
        break;
    case SoundIoFormatS32BE:     ///< Signed 32 bit Big Endian   
        format = SampleFormat::FormatS32BE;
        break;
    case SoundIoFormatU32LE:     ///< Unsigned 32 bit Little Endian 
        format = SampleFormat::FormatU32LE;
        break;
    case SoundIoFormatU32BE:     ///< Unsigned 32 bit Big Endian 
        format = SampleFormat::FormatU32BE;
        break;
    case SoundIoFormatFloat32LE: ///< Float 32 bit Little Endian, Range -1.0 to 1.0  
        format = SampleFormat::FormatFloat32LE;
        break;
    case SoundIoFormatFloat32BE: ///< Float 32 bit Big Endian, Range -1.0 to 1.0 
        format = SampleFormat::FormatFloat32BE;
        break;
    case SoundIoFormatFloat64LE: ///< Float 64 bit Little Endian, Range -1.0 to 1.0   
        format = SampleFormat::FormatFloat64LE;
        break;
    case SoundIoFormatFloat64BE: ///< Float 64 bit Big Endian, Range -1.0 to 1.0  
        format = SampleFormat::FormatFloat64BE;
        break;
    default:
        break;
    }
    return format;
}

SoundIoFormat ExternalFormatToSoundIoFormat( SampleFormat a_sampleFormat )
{
    SoundIoFormat format = SoundIoFormat::SoundIoFormatS8;
    switch( a_sampleFormat )
    {
    case SampleFormat::FormatS8:        ///< Signed 8 bit
        format = SoundIoFormatS8;
        break;
    case SampleFormat::FormatU8:        ///< Unsigned 8 bit  
        format = SoundIoFormatU8;
        break;
    case SampleFormat::FormatS16LE:     ///< Signed 16 bit Little Endian 
        format = SoundIoFormatS16LE;
        break;
    case SampleFormat::FormatS16BE:     ///< Signed 16 bit Big Endian  
        format = SoundIoFormatS16BE;
        break;
    case SampleFormat::FormatU16LE:     ///< Unsigned 16 bit Little Endian 
        format = SoundIoFormatU16LE;
        break;
    case SampleFormat::FormatU16BE:     ///< Unsigned 16 bit Big Endian   
        format = SoundIoFormatU16BE;
        break;
    case SampleFormat::FormatS24LE:     ///< Signed 24 bit Little Endian using low three bytes in 32-bit word  
        format = SoundIoFormatS24LE;
        break;
    case SampleFormat::FormatS24BE:     ///< Signed 24 bit Big Endian using low three bytes in 32-bit word 
        format = SoundIoFormatS24BE;
        break;
    case SampleFormat::FormatU24LE:     ///< Unsigned 24 bit Little Endian using low three bytes in 32-bit word  
        format = SoundIoFormatU24LE;
        break;
    case SampleFormat::FormatU24BE:     ///< Unsigned 24 bit Big Endian using low three bytes in 32-bit word    
        format = SoundIoFormatU24BE;
        break;
    case SampleFormat::FormatS32LE:     ///< Signed 32 bit Little Endian    
        format = SoundIoFormatS32LE;
        break;
    case SampleFormat::FormatS32BE:     ///< Signed 32 bit Big Endian   
        format = SoundIoFormatS32BE;
        break;
    case SampleFormat::FormatU32LE:     ///< Unsigned 32 bit Little Endian 
        format = SoundIoFormatU32LE;
        break;
    case SampleFormat::FormatU32BE:     ///< Unsigned 32 bit Big Endian 
        format = SoundIoFormatU32BE;
        break;
    case SampleFormat::FormatFloat32LE: ///< Float 32 bit Little Endian, Range -1.0 to 1.0  
        format = SoundIoFormatFloat32LE;
        break;
    case SampleFormat::FormatFloat32BE: ///< Float 32 bit Big Endian, Range -1.0 to 1.0 
        format = SoundIoFormatFloat32BE;
        break;
    case SampleFormat::FormatFloat64LE: ///< Float 64 bit Little Endian, Range -1.0 to 1.0   
        format = SoundIoFormatFloat64LE;
        break;
    case SampleFormat::FormatFloat64BE: ///< Float 64 bit Big Endian, Range -1.0 to 1.0  
        format = SoundIoFormatFloat64BE;
        break;
    default:
        break;
    }
    return format;
}
