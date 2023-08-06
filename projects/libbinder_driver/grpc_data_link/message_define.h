#pragma once

#include <cstdint>
#include <memory>
#include <string>

#include <data_link/message_types.h>

namespace data_link
{
    struct message_from_client
    {
        uint64_t id = 0;
        uint32_t type = 0;
        std::string message;
        std::string raw_buffer;
    };

    struct message_from_server
    {
        uint64_t id = 0;
        uint32_t type = 0;
        std::string message;
        std::string raw_buffer;
    };
}
