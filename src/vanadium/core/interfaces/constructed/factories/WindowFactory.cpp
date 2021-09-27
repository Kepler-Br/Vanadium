#include "WindowFactory.h"

namespace vanadium {

std::string WindowFactory::_name = "WindowFactory";

const std::string &WindowFactory::getName() const noexcept {
  return WindowFactory::_name;
}

const std::string &WindowFactory::getFactoryName() noexcept {
  return WindowFactory::_name;
}

}  // namespace vanadium
