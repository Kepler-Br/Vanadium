#pragma once

#include "core/types/Reference.h"

namespace vanadium {

class Stopwatch {
 public:
  virtual ~Stopwatch() = default;

  virtual void start() noexcept = 0;
  virtual float stop() noexcept = 0;
  virtual float restart() noexcept = 0;

  static Ref<Stopwatch> create(bool startImmediately = false);
};

}  // namespace vanadium
