#pragma once

#include "core/interfaces/factories/TimerFactory.h"

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
