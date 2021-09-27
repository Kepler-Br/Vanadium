#pragma once

#include "vanadium/core/interfaces/Factory.h"
#include "vanadium/core/interfaces/constructed/Window.h"
#include "vanadium/core/types/Reference.h"

namespace vanadium {

class WindowFactory : public Factory {
 private:
  static std::string _name;

 public:
  ~WindowFactory() override = default;

  [[nodiscard]] virtual Ref<Window> construct(
      const WindowProperties &properties) = 0;

  [[nodiscard]] const std::string &getName() const noexcept final;
  static const std::string &getFactoryName() noexcept;
};

}  // namespace vanadium
