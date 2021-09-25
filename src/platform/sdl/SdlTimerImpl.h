#pragma once

#include <cstdint>
#include <functional>

#include "core/interfaces/Timer.h"

namespace vanadium {

class SdlTimerImpl : public Timer {
 private:
  std::function<void(float timePassed)> _callback = nullptr;
  bool _isRunning = false;
  bool _repeating = false;
  float _current = 0.0f;
  float _target = 0.0f;
  uint32_t _sdlStartTicks = 0;

 public:
  SdlTimerImpl() = default;
  SdlTimerImpl(std::function<void(float timePassed)> callback, float seconds,
               bool repeating);
  ~SdlTimerImpl() override = default;

  void start() override;
  float stop() override;
  float update() override;
  bool isRunning() noexcept override;
  float getCurrentTime() noexcept override;
  void setRepeating(bool repeating) noexcept override;
  bool getRepeating() noexcept override;
  void setCallback(
      const std::function<void(float timePassed)> &callback) noexcept override;
  void setTime(float seconds) noexcept override;
  float getTime() noexcept override;
};

}  // namespace vanadium
