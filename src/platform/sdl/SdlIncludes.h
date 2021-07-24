#ifndef VANADIUM_PLATFORM_SDLINCLUDES_H
#define VANADIUM_PLATFORM_SDLINCLUDES_H

#if __has_include(<SDL.h>)
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#endif  // VANADIUM_PLATFORM_SDLINCLUDES_H
