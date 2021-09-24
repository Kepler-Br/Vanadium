#pragma once

#include "core/interfaces/Factory.h"
#include "core/interfaces/Window.h"
#include "core/types/Reference.h"

namespace vanadium {

class WindowFactory : public Factory {
 private:
  static std::string _name;

 public:
  ~WindowFactory() override = default;

  [[nodiscard]] virtual Ref<Window> construct(
      const WindowProperties &properties) = 0;

  [[nodiscard]] const std::string &getName() const noexcept override {
    return WindowFactory::_name;
  }

  static const std::string &getFactoryName() noexcept {
    return WindowFactory::_name;
  }
};

std::string WindowFactory::_name = "WindowFactory";

}  // namespace vanadium
