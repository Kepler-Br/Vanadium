#include "RendererApiEnum.h"

namespace vanadium {

std::string_view rendererApiToString(RendererApi rendererApi) {
  switch (rendererApi) {
    case RendererApi::Direct3D11:
      return "Direct3D11";
    case RendererApi::Direct3D9:
      return "Direct3D9";
    case RendererApi::Direct3D12:
      return "Direct3D12";
    case RendererApi::Gnm:
      return "Gnm";
    case RendererApi::Metal:
      return "Metal";
    case RendererApi::Nvn:
      return "Nvn";
    case RendererApi::OpenGLES:
      return "OpenGLES";
    case RendererApi::OpenGL:
      return "OpenGL";
    case RendererApi::Vulkan:
      return "Vulkan";
    case RendererApi::WebGPU:
      return "WebGPU";
    case RendererApi::Noop:
      return "Noop";
    case RendererApi::Any:
      return "Any";
    case RendererApi::Undefined:
      return "Undefined";
  }
}

RendererApi bgfxTypeToRendererApi(bgfx::RendererType::Enum rendererType) {
    using namespace bgfx;

    switch (rendererType) {
      case RendererType::Enum::Direct3D9:
        return RendererApi::Direct3D9;
      case RendererType::Noop:
        return RendererApi::Noop;
      case RendererType::Direct3D11:
        return RendererApi::Direct3D11;
      case RendererType::Direct3D12:
        return RendererApi::Direct3D12;
      case RendererType::Gnm:
        return RendererApi::Gnm;
      case RendererType::Metal:
        return RendererApi::Metal;
      case RendererType::Nvn:
        return RendererApi::Nvn;
      case RendererType::OpenGLES:
        return RendererApi::OpenGLES;
      case RendererType::OpenGL:
        return RendererApi::OpenGL;
      case RendererType::Vulkan:
        return RendererApi::Vulkan;
      case RendererType::WebGPU:
        return RendererApi::WebGPU;
      case RendererType::Count:
        return RendererApi::Noop;
    }
  }

  bgfx::RendererType::Enum rendererApiToBgfxType(RendererApi rendererApi) {
    using namespace bgfx;

    switch (rendererApi) {
      case RendererApi::Direct3D11:
        return RendererType::Enum::Direct3D11;
      case RendererApi::Direct3D9:
        return RendererType::Enum::Direct3D9;
      case RendererApi::Direct3D12:
        return RendererType::Enum::Direct3D12;
      case RendererApi::Gnm:
        return RendererType::Enum::Gnm;
      case RendererApi::Metal:
        return RendererType::Enum::Metal;
      case RendererApi::Nvn:
        return RendererType::Enum::Nvn;
      case RendererApi::OpenGLES:
        return RendererType::Enum::OpenGLES;
      case RendererApi::OpenGL:
        return RendererType::Enum::OpenGL;
      case RendererApi::Vulkan:
        return RendererType::Enum::Vulkan;
      case RendererApi::WebGPU:
        return RendererType::Enum::WebGPU;
      case RendererApi::Noop:
      case RendererApi::Any:
      case RendererApi::Undefined:
        return RendererType::Enum::Noop;
    }
  }

}  // namespace vanadium