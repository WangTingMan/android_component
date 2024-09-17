#pragma once

namespace bluetooth_module {

enum class init_status
{
    deinitialized = 0,
    initializing = 1,
    initialized = 2,
    deinitializing = 4
};

}
