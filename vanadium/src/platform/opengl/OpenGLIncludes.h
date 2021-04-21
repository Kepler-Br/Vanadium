#ifndef VANADIUM_OPENGLINCLUDES_H
#define VANADIUM_OPENGLINCLUDES_H

#if defined(VANADIUM_PLATFORM_MACOS)
#define GL_SILENCE_DEPRECATION
#include <OpenGL/GL3.h>
#elif defined(VANADIUM_PLATFORM_LINUX)
#include <GL/gl.h>
#include <GL/glew.h>
#endif

#endif  // VANADIUM_OPENGLINCLUDES_H
