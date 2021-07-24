#ifndef VANADIUM_DEFAULTTIMER_H
#define VANADIUM_DEFAULTTIMER_H

#include <functional>

#include "../../core/Timer.h"

namespace vanadium {

class DefaultTimer : public Timer {
 public:
  DefaultTimer(const std::function<void()> &callback, double seconds,
               bool repeating) {
    this->_callback = callback;
    this->_secondsLeft = seconds;
    this->_repeating = repeating;
  }

  void start() override {
    if (this->_isRunning) return;
  }

  void stop() override { this->_isRunning = false; }
};

}  // namespace vanadium

#endif  // VANADIUM_DEFAULTTIMER_H
