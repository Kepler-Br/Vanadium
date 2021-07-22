#ifndef VANADIUM_DEFAULTTIMER_H
#define VANADIUM_DEFAULTTIMER_H

#include <functional>

#include "../../core/Timer.h"

namespace vanadium {

class DefaultTimer : public Timer {
 public:
  DefaultTimer(const std::function<void()> &callback, double seconds,
               bool repeating) {
    this->callback = callback;
    this->secondsLeft = seconds;
    this->repeating = repeating;
  }

  void start() override {
    if (this->isRunning) return;
  }

  void stop() override { this->isRunning = false; }
};

}  // namespace Vanadium

#endif  // VANADIUM_DEFAULTTIMER_H
