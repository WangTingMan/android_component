#pragma once

#include <atomic>
#include <list>
#include <map>
#include <mutex>
#include <future>

#include <base/message_loop/message_loop.h>
#include <base/cancelable_callback.h>
#include <base/timer/timer.h>

typedef void (*alarm_callback_t)(void* data);

struct TimerControlBlock
{
    std::string m_name;
    uint32_t m_id{ 0 };
    uint32_t m_intervalms{ 0 };
    bool m_periodic{ false };
    base::RepeatingTimer m_timer;
    std::function<void()> m_callback;
};

class TimerManager
{

public:

    TimerManager();

    ~TimerManager();

    static TimerManager& GetInstance();

    uint32_t MakeNewAlarm
        (
        std::string&& a_ame,
        bool a_periodic = false
        );

    uint32_t MakeNewAlarm
        (
        std::string&& a_ame,
        std::function<void()> a_callBack,
        bool a_periodic = false
        );

    void DeleteAlarm( uint32_t a_alarm);

    void SetAlarm
        (
        uint32_t a_alarm,
        uint64_t a_interval_ms,
        alarm_callback_t a_cb,
        void* a_data
        );

    void SetAlarm
        (
        uint32_t a_alarm,
        uint64_t a_interval_ms,
        std::function<void()> a_callback
        );

    void SetAlarm
        (
        uint32_t a_alarm,
        uint64_t a_interval_ms
        );

    void SetAlarm
        (
        uint32_t a_alarm,
        uint64_t a_timeOut,
        uint64_t a_interval_ms
        );

    void CancelAlarm( uint32_t a_alarm);

    void StopAlarm( uint32_t a_alarm);

    bool IsScheduled( uint32_t const a_larm);

    int GetRemainingMs( uint32_t a_alarm );

private:

    void Quit();

    void Run( std::promise<void> a_start_up_promise );

    void MakeNewAlarmInternal
        (
        std::shared_ptr<std::promise<uint32_t>> a_promised_id,
        std::string&& a_ame,
        std::function<void()> a_callBack,
        bool a_periodic = false
        );

    void DeleteAlarmInternal( uint32_t a_alarm );

    void SetAlarmInternal
        (
        uint32_t a_alarm,
        uint64_t a_interval_ms,
        std::function<void()> a_callback
        );

    void SetAlarmInterval
        (
        uint32_t a_alarm,
        uint64_t a_interval_ms
        );

    void StopAlarmInternal( uint32_t a_alarm );

    void TimerEvent( uint32_t id );

    void IsScheduledInternal
        (
        std::shared_ptr<std::promise<bool>> a_running,
        uint32_t const a_larm 
        );

    void GetRemainingMsInternal
        (
        std::shared_ptr<std::promise<uint32_t>> a_remain_time,
        uint32_t const a_larm
        );

    std::shared_ptr<TimerControlBlock> FindTimer( uint32_t a_alarm );

    std::atomic_uint32_t m_current_id;

    std::recursive_mutex m_mutex;
    std::promise<void> m_quit_promise;
    std::shared_ptr<base::MessageLoop> m_message_loop;
    std::shared_ptr<base::RunLoop> m_run_loop;
    std::list<std::shared_ptr<TimerControlBlock>> m_timers;
    std::thread m_running_thread;
};

