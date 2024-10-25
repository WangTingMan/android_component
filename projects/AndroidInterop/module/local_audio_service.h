#pragma once
#include "abstract_module.h"

#include <boost/signals2.hpp>

class local_audio_service : public abstract_module
{

public:

    virtual void start_stream() = 0;

    virtual void stop_stream() = 0;

    virtual void suspend_stream() = 0;

    virtual void request_presentaion_delay() = 0;

    void trigger_stream_started_signal()
    {
        m_stream_started_signal();
    }

    void trigger_stream_suspend_signal()
    {
        m_stream_suspend_signal();
    }

private:

    boost::signals2::signal<void()> m_stream_started_signal;
    boost::signals2::signal<void()> m_stream_suspend_signal;
};

