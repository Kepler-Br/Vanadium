#pragma once

#include "vanadium/core/interfaces/Factory.h"
#include "vanadium/core/interfaces/constructed/Stopwatch.h"
#include "vanadium/core/types/Reference.h"

namespace vanadium {

class StopwatchFactory : public Factory {
 private:
  static std::string _name;

 public:
  ~StopwatchFactory() override = default;

  [[nodiscard]] virtual Ref<Stopwatch> construct() = 0;

  [[nodiscard]] const std::string &getName() const noexcept final;
  static const std::string &getFactoryName() noexcept;
};

}  // namespace vanadium