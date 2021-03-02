#ifndef VANADIUM_OPENGLINCLUDES_H
#define VANADIUM_OPENGLINCLUDES_H

#ifdef __APPLE__
//    #warning "OpenGL implementation is deprecated on newer MacOS versions."
    #define GL_SILENCE_DEPRECATION
    #include <OpenGL/GL3.h>
#else
    #include <GL/glew.h>
    #include <GL/gl.h>
#endif

#endif //VANADIUM_OPENGLINCLUDES_H
