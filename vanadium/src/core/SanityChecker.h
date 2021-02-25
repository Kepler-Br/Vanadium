#ifndef VANADIUM_SANITYCHECKER_H
#define VANADIUM_SANITYCHECKER_H

#ifdef VANADIUM_PLATFORM_LINUX
#else
    #error "Not a supported platform."
#endif

#if defined(VANADIUM_RENDERAPI_OPENGL)
#else
    #error "Unsupported render API. Consider using flag VANADIUM_RENDERAPI_OPENGL."
#endif

#endif //VANADIUM_SANITYCHECKER_H
