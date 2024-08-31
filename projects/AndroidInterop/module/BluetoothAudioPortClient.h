#pragma once
#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <variant>
#include <vector>

#include "module/audio_types.h"

namespace bluetooth_module {

class bluetooth_audio_port_client
{

public:

    static std::shared_ptr<bluetooth_audio_port_client> create_aidl();

    virtual ~bluetooth_audio_port_client(){}
    virtual presentation_position get_presentation_postion() = 0;
    virtual bool start_stream( bool a_low_latency ) = 0;
    virtual bool stop_stream() = 0;
    virtual bool suspend_stream() = 0;
    virtual bool update_source_metadata( std::vector<playback_track_metadata> a_source_meta_data ) = 0;
    virtual bool update_sink_metadata( std::vector<record_track_metadata> a_source_meta_data ) = 0;
    virtual bool set_latency_mode( latency_mode a_latency ) = 0;
};

}
