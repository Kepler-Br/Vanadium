#pragma once

#include <functional>

namespace vanadium {

class Timer {
 public:
  virtual ~Timer() = default;

  virtual void start() = 0;
  virtual float stop() = 0;
  virtual float update() = 0;
  virtual bool isRunning() noexcept = 0;
  virtual float getCurrentTime() noexcept = 0;
  virtual void setRepeating(bool repeating) noexcept = 0;
  virtual bool getRepeating() noexcept = 0;
  virtual void setCallback(
      const std::function<void(float timePassed)> &callback) noexcept = 0;
  virtual void setTime(float seconds) noexcept = 0;
  virtual float getTime() noexcept = 0;
};

}  // namespace vanadium
