#include "RenderApi.h"

#if defined(VANADIUM_RENDERAPI_OPENGL)
    #include "../platform/opengl/OpenGLRenderApi.h"
#endif

namespace Vanadium
{

Ref<RenderApi> RenderApi::renderApi = nullptr;

Ref<RenderApi> RenderApi::instance()
{
    if (RenderApi::renderApi == nullptr)
#if defined(VANADIUM_RENDERAPI_OPENGL)
        RenderApi::renderApi = MakeRef<OpenGLRenderApi>();
#else
        #error "Unsupported render API."
#endif
    return RenderApi::renderApi;
}

RenderApi::Api RenderApi::getApi()
{
#if defined(VANADIUM_RENDERAPI_OPENGL)
    return Api::OpenGL;
#else
    #error "Unsupported render API."
#endif
}

}