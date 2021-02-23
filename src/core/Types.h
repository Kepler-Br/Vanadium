#ifndef VANADIUM_TYPES_H
#define VANADIUM_TYPES_H

#include <memory>

#ifdef VANADIUM_RENDERAPI_OPENGL
#include "../platform/opengl/OpenGLIncludes.h"

using VNuint = GLuint;
using VNint = GLint;
using VNfloat = GLfloat;
using VNdouble = GLdouble;
#else
#error "Unsupported render api."
#endif
template<typename T>
using Ref = std::shared_ptr<T>;
template<typename T, typename ... Args>
constexpr Ref<T> MakeRef(Args&& ... args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}
#endif //VANADIUM_TYPES_H
