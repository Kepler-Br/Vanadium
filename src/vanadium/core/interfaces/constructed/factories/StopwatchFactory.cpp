#include "StopwatchFactory.h"

namespace vanadium {

std::string StopwatchFactory::_name = "StopwatchFactory";

const std::string &StopwatchFactory::getName() const noexcept {
  return StopwatchFactory::_name;
}

const std::string &StopwatchFactory::getFactoryName() noexcept {
  return StopwatchFactory::_name;
}

}  // namespace vanadium
