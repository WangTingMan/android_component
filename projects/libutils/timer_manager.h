#pragma once

#include "event_pool.h"

typedef void (*alarm_callback_t)(void* data);

class TimerManager
{

public:

    TimerManager();

    static TimerManager& GetInstance();

    int MakeNewAlarm
        (
        std::string&& a_ame,
        bool a_periodic = false
        );

    int MakeNewAlarm
        (
        std::string&& a_ame,
        std::function<void()> a_callBack,
        bool a_periodic = false
        );

    void DeleteAlarm(int a_alarm);

    void SetAlarm
        (
        int a_alarm,
        uint64_t a_interval_ms,
        alarm_callback_t a_cb,
        void* a_data
        );

    void SetAlarm
        (
        int a_alarm,
        uint64_t a_interval_ms,
        std::function<void()> a_callback
        );

    void SetAlarm
        (
        int a_alarm,
        uint64_t a_interval_ms
        );

    void SetAlarm
        (
        int a_alarm,
        uint64_t a_timeOut,
        uint64_t a_interval_ms
        );

    void CancelAlarm(int a_alarm);

    void StopAlarm(int a_alarm);

    bool IsScheduled(int const a_larm);

private:

    EventPool::EventPool m_pool;
};

