#include "FactoryContainerImpl.h"

namespace vanadium {

Ref<Factory> FactoryContainerImpl::getFactory(const std::string& name) {
  auto foundFactory = this->_factoryMap.find(name);

  if (foundFactory == this->_factoryMap.end()) {
    return nullptr;
  }

  return foundFactory->second;
}

Ref<Factory> FactoryContainerImpl::registerFactory(Ref<Factory> factory) {
  const std::string& name = factory->getName();

  if (this->_factoryMap.find(name) != this->_factoryMap.end()) {
    throw FactoryAlreadyRegistered("Factory with name " + name +
                                   " was already registered.");
  }

  this->_factoryMap.try_emplace(name, factory);

  return factory;
}

}  // namespace vanadium
