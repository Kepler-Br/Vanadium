#pragma once

#include "vanadium/core/interfaces/constructed/Stopwatch.h"
#include "vanadium/core/interfaces/constructed/factories/StopwatchFactory.h"

namespace vanadium {

class SdlStopwatchFactoryImpl : public StopwatchFactory {
 private:
  static const std::string _implName;

 public:
  ~SdlStopwatchFactoryImpl() override = default;

  [[nodiscard]] Ref<Stopwatch> construct() override;

  [[nodiscard]] const std::string &getImplName() const noexcept override;
};

}  // namespace vanadium
