#pragma once

#include <functional>
#include <vector>

#include "Stopwatch.h"

namespace vanadium {

enum class AnimationStepType {
  Wait = 0,
  Linear,
  Step,
  Function,
};

template <typename T>
struct AnimationStep {
  using AnimationFunction =
      std::function<void(T *target, double duration, double currentTime,
                         const T &start, const T &end)>;

  double duration;
  AnimationStepType stepType;
  T target;
  T start;
  AnimationFunction function = nullptr;
};

template <typename T>
class Animation {
 private:
  using AnimationFunction =
      std::function<void(T *target, double duration, double currentTime,
                         const T &start, const T &end)>;

  Stopwatch *_stopwatch = nullptr;
  T *_animationTarget = nullptr;
  std::vector<AnimationStep<T>> _frames;
  std::function<void(T *)> _onDestroyFun = nullptr;

 public:
  explicit Animation(T *animationTarget) {
    this->_stopwatch = Stopwatch::create(false);
    animationTarget = animationTarget;
  }

  virtual ~Animation() {
    if (this->_onDestroyFun) this->_onDestroyFun(this->_animationTarget);
    delete _stopwatch;
  }

  virtual void setOnDestroy(std::function<void(T *)> function) {
    this->_onDestroyFun = function;
  }

  virtual Animation<T> *wait(double seconds) {
    this->_frames.template emplace_back(seconds, AnimationStepType::Wait);
  }

  virtual Animation<T> *linear(double seconds, const T &start, const T &end) {
    // noop.
  }

  virtual Animation<T> *step(double seconds, const T &start, const T &end) {
    // noop.
  }

  virtual Animation<T> *function(double seconds, const AnimationFunction &fun) {
    // noop.
  }

  virtual void update() {
    // noop.
  }

  virtual Animation<T> *start() {
    // noop.
  }

  virtual void stop() {
    // noop.
  }

  virtual void reset() {
    // noop.
  }
};

}  // namespace vanadium
