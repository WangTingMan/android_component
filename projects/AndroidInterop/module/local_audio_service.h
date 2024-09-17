#pragma once
#include "abstract_module.h"

class local_audio_service : public abstract_module
{

public:

    virtual void start_stream() = 0;

    virtual void stop_stream() = 0;

    virtual void suspend_stream() = 0;


};

