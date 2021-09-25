#pragma once

#include "core/interfaces/Factory.h"
#include "core/interfaces/constructed/Stopwatch.h"
#include "core/types/Reference.h"

namespace vanadium {

class StopwatchFactory : public Factory {
 private:
  static std::string _name;

 public:
  ~StopwatchFactory() override = default;

  [[nodiscard]] virtual Ref<Stopwatch> construct() = 0;

  [[nodiscard]] const std::string &getName() const noexcept final {
    return StopwatchFactory::_name;
  }

  static const std::string &getFactoryName() noexcept {
    return StopwatchFactory::_name;
  }
};

std::string StopwatchFactory::_name = "StopwatchFactory";

}  // namespace vanadium
