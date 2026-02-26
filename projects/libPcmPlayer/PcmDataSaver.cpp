#include "PcmDataSaver.h"

PCMRecorder::PCMRecorder()
{

}

void PCMRecorder::update_pcm_record_setting( std::string path,
    bool record_pcm )
{
    this->pcm_record_path_ = path;
    this->record_pcm_ = record_pcm;
    if( !record_pcm_ && file_stream_.is_open() )
    {
        file_stream_.flush();
        file_stream_.close();
        size_wrote = 0;
    }
}

void PCMRecorder::handle_pcm_data( void* audioBuffer, int bufferlen )
{

    if( record_pcm_ )
    {

        if( !file_stream_.is_open() )
        {
            file_stream_.open( pcm_record_path_,
                std::ios::binary | std::ios::trunc | std::ios::out );
        }

        if( file_stream_.is_open() )
        {
            file_stream_.write( reinterpret_cast< char* >( audioBuffer ), bufferlen );
            size_wrote += bufferlen;
            if( size_wrote > MAX_SIZE_SIGNLE_FILE )
            {
                file_stream_.flush();
                file_stream_.close();
                size_wrote = 0;
                record_pcm_ = false;
            }
        }
    }
}