#pragma once

#include <bgfx/bgfx.h>

#include <string_view>

namespace vanadium {

enum class RendererApi {
  Direct3D9 = 0,
  Direct3D11,
  Direct3D12,
  Gnm,
  Metal,
  Nvn,
  OpenGLES,
  OpenGL,
  Vulkan,
  WebGPU,
  Noop,
  Any,
  Undefined,
};

std::string_view rendererApiToString(RendererApi rendererApi);

RendererApi bgfxTypeToRendererApi(bgfx::RendererType::Enum rendererType);

bgfx::RendererType::Enum rendererApiToBgfxType(RendererApi rendererApi);

}  // namespace vanadium
