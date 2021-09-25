#pragma once

#include <functional>

#include "core/interfaces/constructed/factories/TimerFactory.h"
#include "core/types/Reference.h"

namespace vanadium {

class SdlTimerImpl;

class SdlTimerFactoryImpl : public TimerFactory {
 public:
  ~SdlTimerFactoryImpl() override = default;

  [[nodiscard]] Ref<Timer> construct() override;

  [[nodiscard]] Ref<Timer> construct(
      std::function<void(float timePassed)> callback, float seconds,
      bool repeating, bool startImmediately) override;
};

}  // namespace vanadium
