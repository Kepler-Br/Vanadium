#include "RandomFactory.h"

namespace vanadium {

std::string RandomFactory::_name = "RandomFactory";

const std::string &RandomFactory::getName() const noexcept {
  return RandomFactory::_name;
}

const std::string &RandomFactory::getFactoryName() noexcept {
  return RandomFactory::_name;
}

}  // namespace vanadium
