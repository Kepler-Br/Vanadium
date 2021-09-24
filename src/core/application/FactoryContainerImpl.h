#pragma once

#include <stdexcept>
#include <unordered_map>

#include "core/Exceptions.h"
#include "core/interfaces/Factory.h"
#include "core/interfaces/FactoryContainer.h"
#include "core/types/Reference.h"

namespace vanadium {

class FactoryContainerImpl : public FactoryContainer {
 private:
  std::unordered_map<std::string, Ref<Factory>> _factoryMap = {};

 public:
  FactoryContainerImpl() = default;
  ~FactoryContainerImpl() override = default;

  Ref<Factory> getFactory(const std::string &name) override;

  Ref<Factory> registerFactory(Ref<Factory> factory) override;
};

}  // namespace vanadium
