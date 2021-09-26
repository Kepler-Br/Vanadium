#pragma once

#include <stdexcept>
#include <unordered_map>

#include "vanadium/core/Exceptions.h"
#include "vanadium/core/interfaces/Factory.h"
#include "vanadium/core/interfaces/FactoryContainer.h"
#include "vanadium/core/types/Reference.h"

namespace vanadium {

class FactoryContainerImpl : public FactoryContainer {
 private:
  std::unordered_map<std::string, Ref<Factory>> _factoryMap = {};

 public:
  FactoryContainerImpl() = default;
  ~FactoryContainerImpl() override = default;

  Ref<Factory> getFactory(const std::string &name) override;

  Ref<Factory> registerFactory(Ref<Factory> factory) override;

  bool hasFactory(const std::string &name) override;
};

}  // namespace vanadium
