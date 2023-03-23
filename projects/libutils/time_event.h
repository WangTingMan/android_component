#pragma once

/**
 * From https://github.com/chloro-pn/event_pool
 */

#include <atomic>
#include <chrono>
#include <functional>
#include <future>
#include <string>

namespace EventPool {
enum class Type {
  TIME_POINT,
  DURATION,
};

class TimeEventHandler {
 public:
  explicit TimeEventHandler(Type type) : type_(type), stop_(false) {}

  // 多次调用只有第一次返回true，之后返回false
  // 只有time_point类型允许Stop
  bool Stop() {
    if (type_ != Type::TIME_POINT) {
      return false;
    }
    bool expect = false;
    return stop_.compare_exchange_strong(expect, true);
  }

 private:
  Type type_;
  std::atomic<bool> stop_;
};

class TimeEvent {
  friend class EventPool;

 public:
  using time_type = std::chrono::time_point<std::chrono::steady_clock, std::chrono::milliseconds>;

  template <typename Duration>
  explicit TimeEvent(std::chrono::time_point<std::chrono::steady_clock, Duration> time_point)
      : time_point_(std::chrono::time_point_cast<std::chrono::milliseconds>(time_point)), type_(Type::TIME_POINT)
  {
      SetTimerId();
  }

  template <typename Rep, typename Period>
  explicit TimeEvent(std::chrono::duration<Rep, Period> duration)
      : time_point_(std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now())),
        type_(Type::DURATION),
        duration_(std::chrono::duration_cast<std::chrono::milliseconds>(duration))
  {
      time_point_ = time_point_ + duration_;
      SetTimerId();
  }

  TimeEvent()
  {
      SetTimerId();
  }

  TimeEvent(const TimeEvent&) = delete;
  TimeEvent& operator=(const TimeEvent&) = delete;
  TimeEvent(TimeEvent&&) = delete;
  TimeEvent& operator=(TimeEvent&&) = delete;
  ~TimeEvent() = default;

  // 完美转发
  template <typename TaskType>
  void SetCallBack(TaskType&& task) {
    call_back_ = std::forward<TaskType>(task);
  }

  bool OnExpire(bool pool_exit) {
    // 首先检查是否被调用线程Stop，如果是则直接返回false
    if (type_ == Type::TIME_POINT && !handler_->Stop()) {
      return false;
    }
    if (valid && call_back_) {
      bool result = call_back_(pool_exit);
      return result;
    }
    return false;
  }

  time_type& GetTimePoint() { return time_point_; }

  const time_type& GetTimePoint() const { return time_point_; }

  Type GetType() const { return type_; }

  void SetType(Type a_type)
  {
      type_ = a_type;
  }

  void UpdateTimePoint() {
    if (GetType() != Type::DURATION) {
      return;
    }
    time_point_ = time_point_ + duration_;
  }

  int GetTimerId() const
  {
      return timer_id_;
  }

  void SetName(std::string name)
  {
      name_ = name;
  }

  void SetDuration(std::chrono::milliseconds a_duration)
  {
      time_point_ = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now());
      duration_ = a_duration;
      time_point_ = time_point_ + duration_;
      valid = true;
  }

  void Stop()
  {
      valid = false;
  }

 private:

  void SetTimerId();

  bool valid = true;
  int timer_id_ = 0;
  std::string name_;
  time_type time_point_;
  Type type_;
  std::function<bool(bool)> call_back_;
  std::chrono::milliseconds duration_;
  std::shared_ptr<TimeEventHandler> handler_;
};

inline std::chrono::time_point<std::chrono::steady_clock, std::chrono::milliseconds> SecondsAfter(uint64_t sec) {
  return std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() +
                                                                 std::chrono::seconds(sec));
}
}  // namespace EventPool