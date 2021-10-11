#pragma once

#include "vanadium/core/interfaces/Factory.h"
#include "vanadium/core/interfaces/constructed/EventProvider.h"
#include "vanadium/core/types/Reference.h"

namespace vanadium {

class EventProviderFactory : public Factory {
 private:
  static std::string _name;

 public:
  ~EventProviderFactory() override = default;

  [[nodiscard]] virtual Ref<EventProvider> construct() = 0;

  [[nodiscard]] const std::string &getName() const noexcept final;
  static const std::string &getFactoryName() noexcept;
};

}  // namespace vanadium
