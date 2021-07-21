#ifndef VANADIUM_DEFAULTSTOPWATCH_H
#define VANADIUM_DEFAULTSTOPWATCH_H

#include <cstdint>

#include "../../core/Stopwatch.h"
//#warning "DefaultStopwatch is not implemented."

namespace Vanadium {

class DefaultStopwatch : public Stopwatch {
 private:
  uint32_t time = 0;

 public:
  DefaultStopwatch() = default;

  void start() noexcept override;
  double stop() noexcept override;
};

}  // namespace Vanadium

#endif  // VANADIUM_DEFAULTSTOPWATCH_H
