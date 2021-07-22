#ifndef VANADIUM_ANIMATION_H
#define VANADIUM_ANIMATION_H

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

  Stopwatch *stopwatch = nullptr;
  T *animationTarget = nullptr;
  std::vector<AnimationStep<T>> frames;
  std::function<void(T *)> onDestroyFun = nullptr;

 public:
  explicit Animation(T *animationTarget) {
    this->stopwatch = Stopwatch::create(false);
    animationTarget = animationTarget;
  }

  virtual ~Animation() {
    if (this->onDestroyFun) this->onDestroyFun(this->animationTarget);
    delete stopwatch;
  }

  virtual void setOnDestroy(std::function<void(T *)> function) {
    this->onDestroyFun = function;
  }

  virtual Animation<T> *wait(double seconds) {
    this->frames.template emplace_back(seconds, AnimationStepType::Wait);
  }

  virtual Animation<T> *linear(double seconds, const T &start, const T &end) {}

  virtual Animation<T> *step(double seconds, const T &start, const T &end) {}

  virtual Animation<T> *function(double seconds, const AnimationFunction &fun) {

  }

  virtual void update() {}

  virtual Animation<T> *start() {}

  virtual void stop() {}

  virtual void reset() {}
};

}  // namespace Vanadium

#endif  // VANADIUM_ANIMATION_H
