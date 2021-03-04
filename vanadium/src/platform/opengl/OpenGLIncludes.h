#ifndef VANADIUM_OPENGLINCLUDES_H
#define VANADIUM_OPENGLINCLUDES_H

#if defined(VANADIUM_PLATFORM_MACOS)
    #define GL_SILENCE_DEPRECATION
    #include <OpenGL/GL3.h>
#elif defined(VANADIUM_PLATFORM_LINUX)
    #include <GL/glew.h>
    #include <GL/gl.h>
#endif

#endif //VANADIUM_OPENGLINCLUDES_H
