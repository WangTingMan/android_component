#include "time_event.h"

static int s_current_id = 0;

void EventPool::TimeEvent::SetTimerId()
{
    timer_id_ = s_current_id++;
}
