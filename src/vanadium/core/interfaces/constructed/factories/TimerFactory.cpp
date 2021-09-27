#include "TimerFactory.h"

namespace vanadium {

std::string TimerFactory::_name = "TimerFactory";

const std::string &TimerFactory::getName() const noexcept {
  return TimerFactory::_name;
}

const std::string &TimerFactory::getFactoryName() noexcept {
  return TimerFactory::_name;
}

}  // namespace vanadium
