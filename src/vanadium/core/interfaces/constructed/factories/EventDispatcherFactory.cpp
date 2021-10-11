#include "EventDispatcherFactory.h"

namespace vanadium {

std::string EventDispatcherFactory::_name = "EventDispatcherFactory";

const std::string &EventDispatcherFactory::getName() const noexcept {
  return EventDispatcherFactory::_name;
}

const std::string &EventDispatcherFactory::getFactoryName() noexcept {
  return EventDispatcherFactory::_name;
}

}
