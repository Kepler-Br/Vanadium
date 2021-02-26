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

static_assert(sizeof(size_t) == 8, "size_t is not 8 bytes! We need it to be 8 bytes to support string hashing.");

#endif //VANADIUM_SANITYCHECKER_H