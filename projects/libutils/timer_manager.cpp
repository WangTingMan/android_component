#include "timer_manager.h"
#include <utils/Timers.h>

TimerManager::TimerManager()
    : m_current_id{ 1 }
{
    std::promise<void> start_up_promise;
    std::future<void> start_up_future = start_up_promise.get_future();
    m_running_thread = std::thread( &TimerManager::Run, this,
                                    std::move( start_up_promise ) );
    start_up_future.wait_for( std::chrono::seconds( 1 ) );
}

TimerManager::~TimerManager()
{
    std::unique_lock<std::recursive_mutex> locker( m_mutex );
    std::shared_ptr<base::MessageLoop> message_loop;
    message_loop = m_message_loop;
    locker.unlock();

    if( !message_loop )
    {
        return;
    }

    message_loop->task_runner()->PostDelayedTask(
        FROM_HERE,
        base::BindOnce( &TimerManager::Quit, base::Unretained( this ) ),
        base::TimeDelta() );

    message_loop.reset();
    if( m_running_thread.joinable() )
    {
        m_running_thread.detach();
    }

    auto future = m_quit_promise.get_future();
    future.wait();
}

TimerManager& TimerManager::GetInstance()
{
    static TimerManager instance;
    return instance;
}

uint32_t TimerManager::MakeNewAlarm
    (
    std::string&& a_name,
    bool a_periodic
    )
{
    return MakeNewAlarm( std::move(a_name), std::function<void()>{}, a_periodic );
}

uint32_t TimerManager::MakeNewAlarm
    (
    std::string&& a_name,
    std::function<void()> a_callBack,
    bool a_periodic
    )
{
    std::shared_ptr<std::promise<uint32_t>> id_promise;
    id_promise = std::make_shared<std::promise<uint32_t>>();
    std::future id_future = id_promise->get_future();

    if( m_message_loop )
    {
        m_message_loop->task_runner()->PostDelayedTask(
            FROM_HERE,
            base::BindOnce( &TimerManager::MakeNewAlarmInternal,
                            base::Unretained( this ), id_promise, a_name,
                            a_callBack, a_periodic ),
            base::TimeDelta() );
        uint32_t id = id_future.get();
        return id;
    }
    return 0;
}

void TimerManager::DeleteAlarm( uint32_t a_alarm)
{
    if( m_message_loop )
    {
        m_message_loop->task_runner()->PostDelayedTask(
            FROM_HERE,
            base::BindOnce( &TimerManager::DeleteAlarmInternal,
                            base::Unretained( this ), a_alarm ),
            base::TimeDelta() );
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
    if( m_message_loop )
    {
        m_message_loop->task_runner()->PostDelayedTask(
            FROM_HERE,
            base::BindOnce( &TimerManager::SetAlarmInternal,
                            base::Unretained( this ), a_alarm,
                            a_interval_ms, a_callback ),
            base::TimeDelta() );
    }
}

void TimerManager::SetAlarm
    (
    uint32_t a_alarm,
    uint64_t a_interval_ms
    )
{
    if( m_message_loop )
    {
        m_message_loop->task_runner()->PostDelayedTask(
            FROM_HERE,
            base::BindOnce( &TimerManager::SetAlarmInterval,
                            base::Unretained( this ), a_alarm,
                            a_interval_ms ),
            base::TimeDelta() );
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
    if( m_message_loop )
    {
        m_message_loop->task_runner()->PostDelayedTask(
            FROM_HERE,
            base::BindOnce( &TimerManager::StopAlarmInternal,
                            base::Unretained( this ), a_alarm ),
            base::TimeDelta() );
    }
}
bool TimerManager::IsScheduled( uint32_t const a_larm)
{
    std::shared_ptr<std::promise<bool>> id_promise;
    id_promise = std::make_shared<std::promise<bool>>();
    std::future id_future = id_promise->get_future();

    if( m_message_loop )
    {
        m_message_loop->task_runner()->PostDelayedTask(
            FROM_HERE,
            base::BindOnce( &TimerManager::IsScheduledInternal,
                            base::Unretained( this ), id_promise, a_larm ),
            base::TimeDelta() );
        return id_future.get();
    }

    return false;
}

int TimerManager::GetRemainingMs( uint32_t a_alarm )
{
    std::shared_ptr<std::promise<uint32_t>> id_promise;
    id_promise = std::make_shared<std::promise<uint32_t>>();
    std::future id_future = id_promise->get_future();

    if( m_message_loop )
    {
        m_message_loop->task_runner()->PostDelayedTask(
            FROM_HERE,
            base::BindOnce( &TimerManager::GetRemainingMsInternal,
                            base::Unretained( this ), id_promise, a_alarm ),
            base::TimeDelta() );
        return id_future.get();
    }

    return 0;
}

void TimerManager::Quit()
{
    if( m_run_loop )
    {
        m_run_loop->Quit();
    }
}

void TimerManager::Run( std::promise<void> a_start_up_promise )
{
    base::PlatformThread::SetName( "Timer Thread" );
    std::unique_lock<std::recursive_mutex> locker( m_mutex );
    m_message_loop = std::make_shared<base::MessageLoop>();
    m_run_loop = std::make_shared<base::RunLoop>();
    locker.unlock();

    a_start_up_promise.set_value();

    // Blocking until ShutDown() is called
    m_run_loop->Run();

    locker.lock();
    m_message_loop.reset();
    m_run_loop.reset();
    m_quit_promise.set_value();
}

void TimerManager::MakeNewAlarmInternal
    (
    std::shared_ptr<std::promise<uint32_t>> a_promised_id,
    std::string&& a_name,
    std::function<void()> a_callBack,
    bool a_periodic
    )
{
    std::shared_ptr<TimerControlBlock> cb;
    cb = std::make_shared<TimerControlBlock>();
    cb->m_id = ++m_current_id;
    cb->m_name = a_name;
    cb->m_periodic = a_periodic;
    cb->m_callback = a_callBack;
    a_promised_id->set_value( cb->m_id );
    m_timers.emplace_back( std::move( cb ) );
}

void TimerManager::DeleteAlarmInternal( uint32_t a_alarm )
{
    for( auto it = m_timers.begin(); it != m_timers.end(); )
    {
        auto& cb = *it;
        if( cb->m_id == a_alarm )
        {
            cb->m_timer.AbandonAndStop();
            it = m_timers.erase( it );
            continue;
        }
        else
        {
            ++it;
        }
    }
}

void TimerManager::SetAlarmInternal
    (
    uint32_t a_alarm,
    uint64_t a_interval_ms,
    std::function<void()> a_callback
    )
{
    auto timer = FindTimer( a_alarm );
    if( !timer )
    {
        return;
    }

    timer->m_callback = a_callback;
    timer->m_intervalms = a_interval_ms;
    if( timer->m_timer.IsRunning() )
    {
        timer->m_timer.AbandonAndStop();
    }

    timer->m_timer.Start( FROM_HERE, base::TimeDelta::FromMilliseconds( timer->m_intervalms ),
                          base::BindRepeating( &TimerManager::TimerEvent,
                                               base::Unretained( this ), timer->m_id ) );
}

void TimerManager::SetAlarmInterval
    (
    uint32_t a_alarm,
    uint64_t a_interval_ms
    )
{
    auto timer = FindTimer( a_alarm );
    if( !timer )
    {
        return;
    }

    timer->m_intervalms = a_interval_ms;
    if( timer->m_timer.IsRunning() )
    {
        timer->m_timer.AbandonAndStop();
    }

    timer->m_timer.Start( FROM_HERE, base::TimeDelta::FromMilliseconds( timer->m_intervalms ),
                          base::BindRepeating( &TimerManager::TimerEvent,
                                               base::Unretained( this ), timer->m_id ) );
}

void TimerManager::StopAlarmInternal( uint32_t a_alarm )
{
    auto timer = FindTimer( a_alarm );
    if( !timer )
    {
        return;
    }

    if( timer->m_timer.IsRunning() )
    {
        timer->m_timer.AbandonAndStop();
    }
}

void TimerManager::TimerEvent( uint32_t a_alarm )
{
    auto timer = FindTimer( a_alarm );
    if( !timer )
    {
        return;
    }

    if( !timer->m_periodic )
    {
        timer->m_timer.AbandonAndStop();
    }

    std::function<void()> callback = timer->m_callback;
    callback();
}

void TimerManager::IsScheduledInternal
    (
    std::shared_ptr<std::promise<bool>> a_running,
    uint32_t const a_alarm
    )
{
    auto timer = FindTimer( a_alarm );
    if( !timer )
    {
        a_running->set_value( false );
        return;
    }

    a_running->set_value( timer->m_timer.IsRunning() );
}

void TimerManager::GetRemainingMsInternal
    (
    std::shared_ptr<std::promise<uint32_t>> a_remain_time,
    uint32_t const a_alarm
    )
{
    auto timer = FindTimer( a_alarm );
    if( !timer )
    {
        a_remain_time->set_value( 0 );
        return;
    }

    auto time = timer->m_timer.GetCurrentDelay();
    uint32_t remains = time.InMilliseconds();
    a_remain_time->set_value( remains );
}

std::shared_ptr<TimerControlBlock> TimerManager::FindTimer( uint32_t a_alarm )
{
    for( auto& ele : m_timers )
    {
        if( ele->m_id == a_alarm )
        {
            return ele;
        }
    }

    return nullptr;
}

uint32_t create_timer(std::function<void()> a_fun, std::string a_name, bool a_periodic )
{
    return TimerManager::GetInstance().MakeNewAlarm( std::move(a_name), a_fun, a_periodic );
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
        TimerManager::GetInstance().StopAlarm(timer_id);
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

