#include "time_event.h"

static std::atomic_uint32_t s_current_id = 0u;

void EventPool::TimeEvent::SetTimerId()
{
    timer_id_ = s_current_id.fetch_add( 1 );
}
