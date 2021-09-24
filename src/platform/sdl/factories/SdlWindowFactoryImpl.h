#pragma once

#include "core/interfaces/Window.h"
#include "core/interfaces/factories/WindowFactory.h"
#include "core/types/window/WindowProperties.h"

namespace vanadium {

class SdlWindowFactoryImpl : public WindowFactory {
 public:
  ~SdlWindowFactoryImpl() override = default;

  [[nodiscard]] Ref<Window> construct(
      const WindowProperties &properties) override;
};

}  // namespace vanadium
