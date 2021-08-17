#pragma once

#include <bgfx/bgfx.h>

#include <glm/vec2.hpp>

#include "BgfxCallback.h"
#include "core/interfaces/Subsystem.h"

namespace vanadium {

class Window;

class BgfxSubsystem : public Subsystem {
 protected:
  Ref<Window> _window;

  BgfxCallback _bgfxCallback;

 public:
  explicit BgfxSubsystem(Ref<Window> mainWindow);

  void init() override;
  void shutdown() override;
};

}  // namespace vanadium
