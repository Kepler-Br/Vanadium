#pragma once

#include "vanadium/core/interfaces/Factory.h"
#include "vanadium/core/interfaces/constructed/Timer.h"
#include "vanadium/core/types/Reference.h"

namespace vanadium {

class TimerFactory : public Factory {
 private:
  static std::string _name;

 public:
  ~TimerFactory() override = default;

  [[nodiscard]] virtual Ref<Timer> construct() = 0;

  [[nodiscard]] virtual Ref<Timer> construct(
      std::function<void(float timePassed)> callback, float seconds,
      bool repeating, bool startImmediately) = 0;

  [[nodiscard]] const std::string &getName() const noexcept final {
    return TimerFactory::_name;
  }

  static const std::string &getFactoryName() noexcept {
    return TimerFactory::_name;
  }
};

std::string TimerFactory::_name = "TimerFactory";

}  // namespace vanadium
