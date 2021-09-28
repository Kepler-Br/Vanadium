#pragma once

#include <functional>

#include "vanadium/core/interfaces/constructed/factories/TimerFactory.h"
#include "vanadium/core/types/Reference.h"

namespace vanadium {

class SdlTimerImpl;

class SdlTimerFactoryImpl : public TimerFactory {
 private:
  static const std::string _implName;

 public:
  ~SdlTimerFactoryImpl() override = default;

  [[nodiscard]] Ref<Timer> construct() override;

  [[nodiscard]] Ref<Timer> construct(
      std::function<void(float timePassed)> callback, float seconds,
      bool repeating, bool startImmediately) override;

  [[nodiscard]] const std::string &getImplName() const noexcept override;
};

}  // namespace vanadium
