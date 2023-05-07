#pragma once

#include "event_pool.h"
#include <mutex>

typedef void (*alarm_callback_t)(void* data);

class TimerManager
{

public:

    TimerManager();

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

    std::shared_ptr<EventPool::TimeEvent> FindTimer( uint32_t a_alarm );

    EventPool::EventPool m_pool;
    std::recursive_mutex m_mutex;
    std::vector<std::shared_ptr<EventPool::TimeEvent>> m_timers;
};

