#include "RenderApi.h"

#include "../core/Assert.h"

#if defined(VANADIUM_RENDERAPI_OPENGL)
#include "../platform/opengl/OpenGLRenderApi.h"
using RendereApiImpl = Vanadium::OpenGLRenderApi;
#endif

namespace Vanadium {

RenderApi *RenderApi::renderApi = nullptr;

RenderApi *RenderApi::instance() {
  if (RenderApi::renderApi == nullptr)
    RenderApi::renderApi = new RendereApiImpl();
  return RenderApi::renderApi;
}

RenderApi::Api RenderApi::getApi() {
#if defined(VANADIUM_RENDERAPI_OPENGL)
  return Api::OpenGL;
#else
#error "Unsupported render API."
#endif
}

std::string RenderApi::apiToString(RenderApi::Api api) {
  switch (api) {
    case Api::OpenGL:
      return "OpenGL";
    case Api::OpenGLES:
      return "OpenGLES";
    case Api::WebGL:
      return "WebGL";
    case Api::Vulkan:
      return "Vulkan";
    case Api::Metal:
      return "Metal";
    case Api::DirectX:
      return "DirectX";
    case Api::DirectX12:
      return "DirectX12";
  }
  VAN_ENGINE_ASSERT(false, "RenderApi::apiToString: unknown render api.");
  return std::string();
}

}  // namespace Vanadium