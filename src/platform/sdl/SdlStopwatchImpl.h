#pragma once

#include <cstdint>

#include "core/interfaces/constructed/Stopwatch.h"

namespace vanadium {

class SdlStopwatchImpl : public Stopwatch {
 private:
  bool _isRunning = false;
  uint32_t _time = 0;

 public:
  SdlStopwatchImpl() = default;

  void start() noexcept override;
  float stop() noexcept override;
  float restart() noexcept override;
};

}  // namespace vanadium
