#ifndef VANADIUM_DEFAULTSTOPWATCH_H
#define VANADIUM_DEFAULTSTOPWATCH_H

#include <cstdint>

#include "../../core/Stopwatch.h"
//#warning "DefaultStopwatch is not implemented."

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

#endif  // VANADIUM_DEFAULTSTOPWATCH_H
