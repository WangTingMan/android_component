#pragma once
#include <fstream>
#include <string>

#pragma once
#include <string>
#include <fstream>

#if defined(PCMPLAYER_IMPLEMENTATION)
#define PCMPLAYER_EXPORT __declspec(dllexport)
#else
#define PCMPLAYER_EXPORT __declspec(dllimport)
#endif  // defined(PCMPLAYER_IMPLEMENTATION)

class PCMPLAYER_EXPORT PCMRecorder
{

public:

    PCMRecorder();

    void update_pcm_record_setting( std::string path, bool record_pcm );

    void handle_pcm_data( void* audioBuffer, int bufferlen );

private:

    std::ofstream file_stream_;
    std::string pcm_record_path_;
    bool record_pcm_ = false;
    uint32_t size_wrote = 0u;

    // Single file's max size is 50 MB.
    static constexpr uint32_t MAX_SIZE_SIGNLE_FILE = 50 * 1000 * 1000;
};

