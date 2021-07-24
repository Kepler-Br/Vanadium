#include "core/Timer.h"

#include "core/Log.h"

#if defined(VANADIUM_PLATFORM_LINUX) | defined(VANADIUM_PLATFORM_MACOS) | \
    defined(VANADIUM_PLATFORM_WINDOWS)
#include "platform/default/DefaultTimer.h"
using TimerImpl = vanadium::DefaultTimer;
#endif

namespace vanadium {

void Timer::setRepeating(bool repeating) noexcept {
  this->_repeating = repeating;
}

void Timer::setCallback(const std::function<void()> &callback) noexcept {
  if (_isRunning) return;
  this->_callback = callback;
}

void Timer::setTimer(double seconds) noexcept {
  if (_isRunning) return;
  this->_secondsLeft = seconds;
}

Timer *Timer::create(const std::function<void()> &callback, double seconds,
                     bool repeating, bool startImmediately) {
  Timer *timer;

  VAN_ENGINE_TRACE("Creating Timer.");
  timer = new TimerImpl(callback, seconds, repeating);
  return timer;
}

}  // namespace vanadium