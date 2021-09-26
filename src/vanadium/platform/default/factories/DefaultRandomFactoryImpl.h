#pragma once

#include "vanadium/core/interfaces/constructed/factories/RandomFactory.h"

namespace vanadium {

class DefaultRandomFactoryImpl : public RandomFactory {
 public:
  ~DefaultRandomFactoryImpl() override = default;

  [[nodiscard]] Ref<Random> construct() override;
  [[nodiscard]] Ref<Random> construct(uint64_t seed) override;
};

}  // namespace vanadium
