#pragma once

namespace vanadium {

class Stopwatch {
 public:
  virtual ~Stopwatch() = default;

  virtual void start() noexcept = 0;
  virtual float stop() noexcept = 0;
  virtual float restart() noexcept = 0;
};

}  // namespace vanadium
