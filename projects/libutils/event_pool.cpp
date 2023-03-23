#include "event_pool.h"

void EventPool::EventPool::RemoveTimer(int id)
{
    std::priority_queue<std::shared_ptr<TimeEvent>, std::vector<std::shared_ptr<TimeEvent>>, cmp_for_time_event> other;
    std::unique_lock<std::mutex> guard(mut_);
    while(!timer_queue_.empty())
    {
        std::shared_ptr<TimeEvent> timer_ = timer_queue_.top();
        if (timer_->timer_id_ != id)
        {
            other.push(std::move(timer_));
        }
        timer_queue_.pop();
    }

    std::swap(other, timer_queue_);
}

