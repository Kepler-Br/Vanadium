#pragma once

#include "vanadium/core/interfaces/constructed/EventDispatcher.h"
#include "vanadium/core/interfaces/constructed/factories/EventDispatcherFactory.h"

namespace vanadium {

class DefaultEventDispatcherFactoryImpl : public EventDispatcherFactory {
 private:
  const std::string _implName = "DefaultEventDispatcherFactoryImpl";

 public:
  Ref<EventDispatcher> construct() override;

  [[nodiscard]] const std::string& getImplName() const noexcept override;
};

}  // namespace vanadium