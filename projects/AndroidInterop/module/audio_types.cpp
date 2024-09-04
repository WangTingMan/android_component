#include "audio_types.h"

namespace bluetooth_module {

std::string to_string(a2dp_stream_status const& a_status)
{
    switch(a_status)
    {
    case a2dp_stream_status::unknown:
        return "unknown";
        break;
    case a2dp_stream_status::success:
        return "success";
        break;
    case a2dp_stream_status::failure:
        return "failure";
        break;
    case a2dp_stream_status::reconfiguration:
        return "reconfiguration";
        break;
    case a2dp_stream_status::unsupported_codec_configuration:
        return "unsupported_codec_configuration";
        break;
    default:
        return "unknown";
        break;
    }
    return "unknown";
}

}
