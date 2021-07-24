#ifndef VANADIUM_BGFXCONTEXT_H
#define VANADIUM_BGFXCONTEXT_H

#include <bgfx/bgfx.h>

#include <glm/vec2.hpp>

#include "BgfxCallback.h"

namespace vanadium {

class Window;

class BgfxContext {
 private:
  Window *_window;
  uint32_t _resetFlags;
  bgfx::TextureFormat::Enum _format = bgfx::TextureFormat::Count;

  BgfxCallback bgfxCallback;

 public:
  BgfxContext(Window *window);
  ~BgfxContext();

  void reset(const glm::ivec2 &resolution);
  void reset(const glm::ivec2 &resolution, uint32_t resetFlags,
             bgfx::TextureFormat::Enum format = bgfx::TextureFormat::Count);
};

}  // namespace vanadium

#endif  // VANADIUM_BGFXCONTEXT_H
