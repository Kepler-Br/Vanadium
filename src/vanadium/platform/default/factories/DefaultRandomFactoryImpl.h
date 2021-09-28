#pragma once

#include "vanadium/core/interfaces/constructed/factories/RandomFactory.h"

namespace vanadium {

class DefaultRandomFactoryImpl : public RandomFactory {
 private:
  static const std::string _implName;

 public:
  ~DefaultRandomFactoryImpl() override = default;

  [[nodiscard]] Ref<Random> construct() override;
  [[nodiscard]] Ref<Random> construct(uint64_t seed) override;

  [[nodiscard]] const std::string &getImplName() const noexcept override;
};

}  // namespace vanadium
