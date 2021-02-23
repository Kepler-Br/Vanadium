#ifndef VANADIUM_OPENGLCALL_H
#define VANADIUM_OPENGLCALL_H

#include <string>
#include <iostream>

#include "OpenGLIncludes.h"
#include "../../core/Log.h"

namespace Vanadium
{

class OpenGLError
{
public:
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
};

}

#define glCall(x) x; \
    { \
        GLenum error = glGetError(); \
        if (error != GL_NO_ERROR) \
            VAN_ENGINE_ERROR("Error calling {}. Reason: {}", #x, OpenGLError::toString(error)); \
    }

#define glCallThrow(x, throwClass, message) x; \
    { \
        GLenum error = glGetError(); \
        if (error != GL_NO_ERROR) \
        { \
            VAN_ENGINE_ERROR("Error calling {}. Reason: {}", #x, OpenGLError::toString(error)); \
            throw throwClass(message); \
        } \
    }

#endif //VANADIUM_OPENGLCALL_H
