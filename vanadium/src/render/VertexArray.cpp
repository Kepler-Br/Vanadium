#include "VertexArray.h"

#if defined(VANADIUM_RENDERAPI_OPENGL)
    #include "../platform/opengl/OpenGLVertexArray.h"
#endif

namespace Vanadium
{

Ref<VertexArray> VertexArrayFactory::create()
{
#if defined(VANADIUM_RENDERAPI_OPENGL)
    return MakeRef<OpenGLVertexArray>();
#else
    #error "Unsupported render api."
#endif
}

}