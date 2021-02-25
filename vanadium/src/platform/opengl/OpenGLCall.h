#ifndef VANADIUM_OPENGLCALL_H
#define VANADIUM_OPENGLCALL_H

#include <string>
#include <iostream>

#include "OpenGLIncludes.h"
#include "../../core/Log.h"

namespace Vanadium
{

namespace OpenGLError
{

static std::string toString(GLenum errorCode)
{
    switch (errorCode) {
        case GL_NO_ERROR:
            return "GL_NO_ERROR";
        case GL_INVALID_ENUM:
            return "GL_INVALID_ENUM";
        case GL_INVALID_VALUE:
            return "GL_INVALID_VALUE";
        case GL_INVALID_OPERATION:
            return "GL_INVALID_OPERATION";
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            return "GL_INVALID_FRAMEBUFFER_OPERATION";
        case GL_OUT_OF_MEMORY:
            return "GL_OUT_OF_MEMORY";
        case GL_STACK_UNDERFLOW:
            return "GL_STACK_UNDERFLOW";
        case GL_STACK_OVERFLOW:
            return "GL_STACK_OVERFLOW";
        default:
            return "INVALID ERROR CODE";
    }
}

}

}

#define glFlushErrors while (glGetError() != GL_NO_ERROR);

#define glCall(x) glFlushErrors \
    x; \
    { \
        GLenum error; \
        while ((error = glGetError()) != GL_NO_ERROR) \
            VAN_ENGINE_ERROR("Error calling \"{}\" in file \"{}\", on line \"{}\". Reason: \"{}\"", #x, __FILE__, __LINE__, OpenGLError::toString(error)); \
    }

#define glCallThrow(x, throwClass, message) glFlushErrors \
    x; \
    { \
        GLenum error = glGetError(); \
        if (error != GL_NO_ERROR) \
        { \
            VAN_ENGINE_ERROR("Error calling \"{}\" in file \"{}\", on line \"{}\". Reason: \"{}\"", #x, __FILE__, __LINE__, OpenGLError::toString(error)); \
            throw throwClass(message); \
        } \
    }

#endif //VANADIUM_OPENGLCALL_H
