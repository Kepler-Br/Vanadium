#include "EventProviderFactory.h"

namespace vanadium {

std::string EventProviderFactory::_name = "EventProviderFactory";

const std::string &EventProviderFactory::getName() const noexcept {
  return EventProviderFactory::_name;
}

const std::string &EventProviderFactory::getFactoryName() noexcept {
  return EventProviderFactory::_name;
}

}
