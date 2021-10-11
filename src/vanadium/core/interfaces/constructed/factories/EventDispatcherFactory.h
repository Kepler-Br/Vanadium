#pragma once

#include "vanadium/core/interfaces/Factory.h"
#include "vanadium/core/interfaces/constructed/EventDispatcher.h"
#include "vanadium/core/types/Reference.h"

namespace vanadium {

class EventDispatcherFactory : public Factory {
 private:
  static std::string _name;

 public:
  ~EventDispatcherFactory() override = default;

  [[nodiscard]] virtual Ref<EventDispatcher> construct() = 0;

  [[nodiscard]] const std::string &getName() const noexcept final;
  static const std::string &getFactoryName() noexcept;
};

}  // namespace vanadium
