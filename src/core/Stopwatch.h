#ifndef VANADIUM_STOPWATCH_H
#define VANADIUM_STOPWATCH_H

namespace vanadium {

class Stopwatch {
 protected:
  bool _isRunning = false;

 public:
  virtual ~Stopwatch() = default;

  virtual void start() noexcept = 0;
  virtual double stop() noexcept = 0;

  static Stopwatch *create(bool startImmediately = false);
};

}  // namespace vanadium

#endif  // VANADIUM_STOPWATCH_H
