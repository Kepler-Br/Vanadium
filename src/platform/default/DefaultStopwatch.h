#pragma once

#include <cstdint>

#include "core/Stopwatch.h"

namespace vanadium {

class DefaultStopwatch : public Stopwatch {
 private:
  bool _isRunning = false;
  uint32_t _time = 0;

 public:
  DefaultStopwatch() = default;

  void start() noexcept override;
  float stop() noexcept override;
  float restart() noexcept override;
};

}  // namespace vanadium
