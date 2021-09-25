#pragma once

#include "core/interfaces/Stopwatch.h"
#include "core/interfaces/factories/StopwatchFactory.h"

namespace vanadium {

class SdlStopwatchFactoryImpl : public StopwatchFactory {
 public:
  ~SdlStopwatchFactoryImpl() override = default;

  [[nodiscard]] Ref<Stopwatch> construct() override;
};

}  // namespace vanadium
