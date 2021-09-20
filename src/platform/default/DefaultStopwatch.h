#pragma once

#include <cstdint>

#include "core/Stopwatch.h"

namespace vanadium {

class DefaultStopwatch : public Stopwatch {
 private:
  uint32_t _time = 0;

 public:
  DefaultStopwatch() = default;

  void start() noexcept override;
  double stop() noexcept override;
};

}  // namespace vanadium
