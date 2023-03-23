#include "timer_manager.h"
#include <utils/Timers.h>

TimerManager::TimerManager()
    : m_pool(102400)
{
    m_pool.Start();
}

TimerManager& TimerManager::GetInstance()
{
    static TimerManager instance;
    return instance;
}

int TimerManager::MakeNewAlarm
    (
    std::string&& a_ame,
    bool a_periodic
    )
{
    std::shared_ptr<EventPool::TimeEvent> timer;
    timer = std::make_shared<EventPool::TimeEvent>();
    timer->SetName(a_ame);
    timer->SetType(a_periodic ? EventPool::Type::DURATION : EventPool::Type::TIME_POINT);
    timer->SetDuration(std::chrono::hours(4028));
    m_pool.PushTimeEvent(timer);

    return timer->GetTimerId();
}

int TimerManager::MakeNewAlarm
    (
    std::string&& a_ame,
    std::function<void()> a_callBack,
    bool a_periodic
    )
{
    std::shared_ptr<EventPool::TimeEvent> timer;
    timer = std::make_shared<EventPool::TimeEvent>();
    timer->SetName(a_ame);
    timer->SetType(a_periodic ? EventPool::Type::DURATION : EventPool::Type::TIME_POINT);
    timer->SetDuration(std::chrono::hours(4028));
    timer->SetCallBack([a_callBack](bool)
        {
            a_callBack();
            return true;
        });

    m_pool.PushTimeEvent(timer);

    return timer->GetTimerId();
}

void TimerManager::DeleteAlarm(int a_alarm)
{
    m_pool.RemoveTimer(a_alarm);
}

void TimerManager::SetAlarm
    (
    int a_alarm,
    uint64_t a_interval_ms,
    alarm_callback_t a_cb,
    void* a_data
    )
{
    std::shared_ptr<EventPool::TimeEvent> timer;
    timer = m_pool.FindTimer(a_alarm);

    if (timer)
    {
        m_pool.PushTask([a_interval_ms, a_cb, a_data, timer, this]()
            {
                timer->SetDuration(std::chrono::milliseconds(a_interval_ms));
                timer->SetCallBack(
                    [a_cb, a_data](bool)
                    {
                        a_cb(a_data);
                        return true;
                    }
                    );
                m_pool.SechduleTimers();
            });
    }
}

void TimerManager::SetAlarm
    (
    int a_alarm,
    uint64_t a_interval_ms,
    std::function<void()> a_callback
    )
{
    std::shared_ptr<EventPool::TimeEvent> timer;
    timer = m_pool.FindTimer(a_alarm);

    if (timer)
    {
        m_pool.PushTask([a_interval_ms, a_callback, timer, this]()
            {
                timer->SetDuration(std::chrono::milliseconds(a_interval_ms));
                timer->SetCallBack([a_callback](bool)
                {
                    a_callback();
                    return true;
                });
                m_pool.SechduleTimers();
            });
    }
}

void TimerManager::SetAlarm
    (
    int a_alarm,
    uint64_t a_interval_ms
    )
{
    std::shared_ptr<EventPool::TimeEvent> timer;
    timer = m_pool.FindTimer(a_alarm);

    if (timer)
    {
        m_pool.PushTask([a_interval_ms, timer, this]()
            {
                timer->SetDuration(std::chrono::milliseconds(a_interval_ms));
                m_pool.SechduleTimers();
            });
    }
}

void TimerManager::SetAlarm
    (
    int a_alarm,
    uint64_t a_timeOut,
    uint64_t a_interval_ms
    )
{

}

void TimerManager::CancelAlarm(int a_alarm)
{
    m_pool.RemoveTimer(a_alarm);
}

void TimerManager::StopAlarm(int a_alarm)
{
    std::shared_ptr<EventPool::TimeEvent> timer;
    timer = m_pool.FindTimer(a_alarm);

    if (timer)
    {
        m_pool.PushTask([timer, this]()
            {
                timer->Stop();
                m_pool.SechduleTimers();
            });
    }
}
bool TimerManager::IsScheduled(int const a_larm)
{
    std::shared_ptr<EventPool::TimeEvent> timer;
    timer = m_pool.FindTimer(a_larm);
    return static_cast<bool>(timer);
}

#ifdef __cplusplus
extern "C" {
#endif

    int common_timer_create(timer_expired_callback_type a_callback, void* a_user_data)
    {
        return TimerManager::GetInstance().MakeNewAlarm("", std::bind(a_callback, a_user_data), true);
    }

    int common_timer_create_no_paras(timer_expired_callback_no_paras_type a_callback)
    {
        return TimerManager::GetInstance().MakeNewAlarm("", std::bind(a_callback), true);
    }

    void stop_timer(int timer_id)
    {
        TimerManager::GetInstance().CancelAlarm(timer_id);
    }

    void delete_timer(int timer_id)
    {
        TimerManager::GetInstance().DeleteAlarm(timer_id);
    }

    void set_timer_duration(int timer_id, int milliseconds)
    {
        TimerManager::GetInstance().SetAlarm(timer_id, milliseconds);
    }

#ifdef __cplusplus
} // extern "C"
#endif

