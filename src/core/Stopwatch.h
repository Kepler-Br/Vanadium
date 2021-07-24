#ifndef VANADIUM_STOPWATCH_H
#define VANADIUM_STOPWATCH_H

#include "core/Types.h"

namespace vanadium {

class Stopwatch {
 protected:
  bool _isRunning = false;

 public:
  virtual ~Stopwatch() = default;

  virtual void start() noexcept = 0;
  virtual double stop() noexcept = 0;

  static Ref<Stopwatch> create(bool startImmediately = false);
};

}  // namespace vanadium

#endif  // VANADIUM_STOPWATCH_H
