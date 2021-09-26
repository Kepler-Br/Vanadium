#pragma once

#include "vanadium/core/interfaces/Factory.h"
#include "vanadium/core/interfaces/constructed/Random.h"
#include "vanadium/core/types/Reference.h"

namespace vanadium {

class RandomFactory : public Factory {
 private:
  static std::string _name;

 public:
  ~RandomFactory() override = default;

  [[nodiscard]] virtual Ref<Random> construct() = 0;
  [[nodiscard]] virtual Ref<Random> construct(uint64_t seed) = 0;

  [[nodiscard]] const std::string &getName() const noexcept final {
    return RandomFactory::_name;
  }

  static const std::string &getFactoryName() noexcept {
    return RandomFactory::_name;
  }
};

std::string RandomFactory::_name = "RandomFactory";

}  // namespace vanadium
