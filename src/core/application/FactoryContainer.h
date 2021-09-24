#pragma once

#include <unordered_map>

#include "core/interfaces/Factory.h"
#include "core/types/Reference.h"

namespace vanadium {

class FactoryContainer {
 private:
  std::unordered_map<std::string, Ref<Factory>> _factoryMap = {};

 public:
  FactoryContainer() = default;
  ~FactoryContainer() = default;

  template <class TFactory>
  Ref<TFactory> getFactory() {
    const std::string &name = TFactory::getFactoryName();

    auto foundFactory = this->_factoryMap.find(name);

    if (foundFactory == this->_factoryMap.end()) {
      throw std::out_of_range("Cannot find factory with name: " + name);
    }

    return (Ref<TFactory>)foundFactory->second;
  }

  Ref<Factory> getFactory(const std::string &name);

  template <class TFactory>
  Ref<Factory> registerFactory() {
    const std::string &name = TFactory::getFactoryName();
    Ref<TFactory> factory = MakeRef<TFactory>();

    this->_factoryMap.try_emplace(name, factory);

    return factory;
  }

  Ref<Factory> registerFactory(Ref<Factory> factory);
};

}  // namespace vanadium
