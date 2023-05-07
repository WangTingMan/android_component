#pragma once

/**
 * From https://github.com/chloro-pn/event_pool
 */

#include <atomic>
#include <chrono>
#include <functional>
#include <future>
#include <string>
#include <mutex>

namespace EventPool {

class TimeEventHandler {
 public:
  explicit TimeEventHandler() : stop_(false) {}

  // 多次调用只有第一次返回true，之后返回false
  // 只有time_point类型允许Stop
  bool IsStop() {
    return stop_;
  }

  void SetStop()
  {
      stop_.exchange( true );
  }

 private:
  std::atomic<bool> stop_;
};

class TimeEvent {
  friend class EventPool;

 public:
  using time_type = std::chrono::time_point<std::chrono::steady_clock, std::chrono::milliseconds>;

  template <typename Rep, typename Period>
  explicit TimeEvent(std::chrono::duration<Rep, Period> duration)
      : start_point_(std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now())),
        duration_(std::chrono::duration_cast<std::chrono::milliseconds>(duration))
  {
      time_point_ = start_point_ + duration_;
      triger_count = 1;
      SetTimerId();
      CheckValid();
  }

  TimeEvent()
  {
      start_point_ = std::chrono::time_point_cast< std::chrono::milliseconds >( std::chrono::steady_clock::now() );
      duration_ = std::chrono::milliseconds( 0 );
      SetTimerId();
      CheckValid();
  }

  TimeEvent(const TimeEvent&) = delete;
  TimeEvent& operator=(const TimeEvent&) = delete;
  TimeEvent(TimeEvent&&) = delete;
  TimeEvent& operator=(TimeEvent&&) = delete;
  ~TimeEvent() = default;

  // 完美转发
  template <typename TaskType>
  void SetCallBack( TaskType&& task )
  {
    std::unique_lock<std::recursive_mutex> locker( mutex_ );
    call_back_ = std::forward<TaskType>(task);
    CheckValid();
  }

  bool OnExpire( bool pool_exit )
  {
    std::unique_lock<std::recursive_mutex> locker( mutex_ );
    // 首先检查是否被调用线程Stop，如果是则直接返回false
    if (handler_->IsStop()) {
      return false;
    }
    if (valid && call_back_) {
      auto timer_callback = call_back_;
      locker.unlock();
      bool result = timer_callback(pool_exit);
      return result;
    }
    return false;
  }

  time_type& GetTimePoint()
  {
      std::lock_guard<std::recursive_mutex> locker( mutex_ );
      return time_point_;
  }

  const time_type& GetTimePoint() const
  {
      std::lock_guard<std::recursive_mutex> locker( mutex_ ); 
      return time_point_;
  }

  void UpdateTimePoint()
  {
    std::lock_guard<std::recursive_mutex> locker( mutex_ );
    triger_count++;
    time_point_ = start_point_ + ( duration_ * triger_count );
  }

  uint32_t GetTimerId() const
  {
      std::lock_guard<std::recursive_mutex> locker( mutex_ );
      return timer_id_;
  }

  void SetName(std::string name)
  {
      std::lock_guard<std::recursive_mutex> locker( mutex_ );
      name_ = name;
  }

  void SetDuration(std::chrono::milliseconds a_duration)
  {
      std::lock_guard<std::recursive_mutex> locker( mutex_ );
      start_point_ = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now());
      duration_ = a_duration;
      triger_count = 1;
      time_point_ = start_point_ + duration_ * triger_count;
      CheckValid();
  }

  void Stop()
  {
      std::lock_guard<std::recursive_mutex> locker( mutex_ );
      valid = false;
  }

  int RemainMs()const
  {
      std::lock_guard<std::recursive_mutex> locker( mutex_ );
      auto _now = std::chrono::time_point_cast< std::chrono::milliseconds >( std::chrono::steady_clock::now() );
      if( time_point_ >= _now )
      {
          return static_cast<int>( (time_point_ - _now).count() );
      }
      return 0;
  }

  bool IsScheduled()
  {
      return valid;
  }

 private:

  void SetTimerId();

  void CheckValid()
  {
      if( !call_back_ )
      {
          valid = false;
          return;
      }

      if( duration_.count() == 0 )
      {
          valid = false;
      }

      valid = true;

  }

  mutable std::recursive_mutex mutex_;
  bool valid = true;
  uint32_t timer_id_ = 0;
  std::string name_;
  uint32_t triger_count = 0;
  time_type time_point_;
  time_type start_point_;
  std::function<bool(bool)> call_back_;
  std::chrono::milliseconds duration_;
  std::shared_ptr<TimeEventHandler> handler_;
};

inline std::chrono::time_point<std::chrono::steady_clock, std::chrono::milliseconds> SecondsAfter(uint64_t sec) {
  return std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() +
                                                                 std::chrono::seconds(sec));
}
}  // namespace EventPool