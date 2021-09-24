#include "FactoryContainer.h"

namespace vanadium {

Ref<Factory> FactoryContainer::getFactory(const std::string& name) {
  auto foundFactory = this->_factoryMap.find(name);

  if (foundFactory == this->_factoryMap.end()) {
    throw std::out_of_range("Cannot find factory with name: " + name);
  }

  return foundFactory->second;
}

Ref<Factory> FactoryContainer::registerFactory(Ref<Factory> factory) {
  const std::string& name = factory->getName();

  this->_factoryMap.try_emplace(name, factory);

  return factory;
}

}  // namespace vanadium
