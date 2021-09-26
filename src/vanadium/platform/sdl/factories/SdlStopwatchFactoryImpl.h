#pragma once

#include "vanadium/core/interfaces/constructed/Stopwatch.h"
#include "vanadium/core/interfaces/constructed/factories/StopwatchFactory.h"

namespace vanadium {

class SdlStopwatchFactoryImpl : public StopwatchFactory {
 public:
  ~SdlStopwatchFactoryImpl() override = default;

  [[nodiscard]] Ref<Stopwatch> construct() override;
};

}  // namespace vanadium
