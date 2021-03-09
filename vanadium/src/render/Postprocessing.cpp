#include "Postprocessing.h"
#include "Shader.h"
#if defined(VANADIUM_RENDERAPI_OPENGL)
#include "../platform/opengl/OpenGLPostprocessing.h"
using PostprocessingImpl = Vanadium::OpenGLPostprocessing;
#endif

namespace Vanadium
{

Ref<Postprocessing> PostprocessingFactory::create()
{

}

Ref<Postprocessing> PostprocessingFactory::create(Ref<Shader> shader)
{

}

}