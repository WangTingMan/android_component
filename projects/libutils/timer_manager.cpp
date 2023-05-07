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

uint32_t TimerManager::MakeNewAlarm
    (
    std::string&& a_ame,
    bool a_periodic
    )
{
    std::shared_ptr<EventPool::TimeEvent> timer;
    timer = std::make_shared<EventPool::TimeEvent>();
    timer->SetName(a_ame);
    timer->Stop();
    m_pool.PushTimeEvent(timer);

    return timer->GetTimerId();
}

uint32_t TimerManager::MakeNewAlarm
    (
    std::string&& a_ame,
    std::function<void()> a_callBack,
    bool a_periodic
    )
{
    std::shared_ptr<EventPool::TimeEvent> timer;
    timer = std::make_shared<EventPool::TimeEvent>();
    timer->SetName(a_ame);
    timer->SetDuration(std::chrono::hours(4028));
    timer->SetCallBack([a_callBack](bool)
        {
            a_callBack();
            return true;
        });
    timer->Stop();

    m_pool.PushTimeEvent(timer);

    return timer->GetTimerId();
}

void TimerManager::DeleteAlarm( uint32_t a_alarm)
{
    m_pool.RemoveTimer(a_alarm);
    std::lock_guard<std::recursive_mutex> locker( m_mutex );
    for( auto it = m_timers.begin(); it != m_timers.end(); ++it )
    {
        if( ( *it )->GetTimerId() == a_alarm )
        {
            it = m_timers.erase( it );
            return;
        }
    }
}

void TimerManager::SetAlarm
    (
    uint32_t a_alarm,
    uint64_t a_interval_ms,
    alarm_callback_t a_cb,
    void* a_data
    )
{
    SetAlarm( a_alarm, a_interval_ms, std::bind( a_cb, a_data ) );
}

void TimerManager::SetAlarm
    (
    uint32_t a_alarm,
    uint64_t a_interval_ms,
    std::function<void()> a_callback
    )
{
    bool need_push_local = true;
    std::shared_ptr<EventPool::TimeEvent> timer;
    timer = m_pool.FindTimer(a_alarm);
    if( !timer )
    {
        std::lock_guard<std::recursive_mutex> locker( m_mutex );
        for( auto& ele : m_timers )
        {
            if( ele->GetTimerId() == a_alarm )
            {
                timer = ele;
                need_push_local = false;
                break;
            }
        }
    }

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

        if( need_push_local )
        {
            m_timers.push_back( timer );
        }
    }
}

void TimerManager::SetAlarm
    (
    uint32_t a_alarm,
    uint64_t a_interval_ms
    )
{
    bool need_push_local = true;
    std::shared_ptr<EventPool::TimeEvent> timer;
    timer = m_pool.FindTimer(a_alarm);
    if( !timer )
    {
        std::lock_guard<std::recursive_mutex> locker( m_mutex );
        for( auto& ele : m_timers )
        {
            if( ele->GetTimerId() == a_alarm )
            {
                timer = ele;
                need_push_local = false;
                break;
            }
        }
    }

    if (timer)
    {
        m_pool.PushTask([a_interval_ms, timer, this]()
            {
                timer->SetDuration(std::chrono::milliseconds(a_interval_ms));
                m_pool.SechduleTimers();
            });

        if( need_push_local )
        {
            m_timers.push_back( timer );
        }
    }
}

void TimerManager::SetAlarm
    (
    uint32_t a_alarm,
    uint64_t a_timeOut,
    uint64_t a_interval_ms
    )
{

}

void TimerManager::CancelAlarm( uint32_t a_alarm)
{
    DeleteAlarm(a_alarm);
}

void TimerManager::StopAlarm( uint32_t a_alarm)
{
    std::shared_ptr<EventPool::TimeEvent> timer;
    timer = FindTimer(a_alarm);

    if (timer)
    {
        m_pool.PushTask([timer, this]()
            {
                timer->Stop();
                m_pool.SechduleTimers();
            });
    }
}
bool TimerManager::IsScheduled( uint32_t const a_larm)
{
    std::shared_ptr<EventPool::TimeEvent> timer;
    timer = FindTimer(a_larm);
    return static_cast<bool>(timer);
}

int TimerManager::GetRemainingMs( uint32_t a_alarm )
{
    std::shared_ptr<EventPool::TimeEvent> timer;
    timer = FindTimer( a_alarm );
    if( timer )
    {
        return timer->RemainMs();
    }
    return 0;
}

std::shared_ptr<EventPool::TimeEvent> TimerManager::FindTimer( uint32_t a_alarm )
{
    std::shared_ptr<EventPool::TimeEvent> timer;
    timer = m_pool.FindTimer( a_alarm );
    if( timer )
    {
        return timer;
    }

    std::lock_guard<std::recursive_mutex> locker( m_mutex );
    for( auto& ele : m_timers )
    {
        if( ele->GetTimerId() == a_alarm )
        {
            return ele;
        }
    }

    return timer;
}

uint32_t create_timer(std::function<void()> a_fun, std::string a_name)
{
    return TimerManager::GetInstance().MakeNewAlarm( std::move(a_name), a_fun, true);
}

void set_timer_option( uint32_t timer_id, int milliseconds, std::function<void()> a_fun )
{
    TimerManager::GetInstance().SetAlarm( timer_id, milliseconds, a_fun );
}

#ifdef __cplusplus
extern "C" {
#endif

    uint32_t common_timer_create(timer_expired_callback_type a_callback, void* a_user_data)
    {
        return TimerManager::GetInstance().MakeNewAlarm("", std::bind(a_callback, a_user_data), true);
    }

    uint32_t common_timer_create_no_paras(timer_expired_callback_no_paras_type a_callback)
    {
        return TimerManager::GetInstance().MakeNewAlarm("", std::bind(a_callback), true);
    }

    void stop_timer( uint32_t timer_id)
    {
        TimerManager::GetInstance().CancelAlarm(timer_id);
    }

    void delete_timer( uint32_t timer_id)
    {
        TimerManager::GetInstance().DeleteAlarm(timer_id);
    }

    void set_timer_duration( uint32_t timer_id, int milliseconds)
    {
        TimerManager::GetInstance().SetAlarm(timer_id, milliseconds);
    }

    void set_timer( uint32_t timer_id, int milliseconds,
        timer_expired_callback_type a_callback, void* a_user_data )
    {
        TimerManager::GetInstance().SetAlarm( timer_id, milliseconds, std::bind( a_callback, a_user_data ) );
    }

    int is_timer_scheduled( uint32_t timer_id )
    {
        bool result = TimerManager::GetInstance().IsScheduled( timer_id );
        return result ? 1 : 0;
    }

    int get_timer_remaining_ms( uint32_t timer_id )
    {
        return TimerManager::GetInstance().GetRemainingMs( timer_id );
    }

#ifdef __cplusplus
} // extern "C"
#endif

