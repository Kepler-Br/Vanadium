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

  [[nodiscard]] const std::string &getName() const noexcept final;
  static const std::string &getFactoryName() noexcept;
};

}  // namespace vanadium
