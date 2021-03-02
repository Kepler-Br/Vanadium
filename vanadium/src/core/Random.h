#ifndef VANADIUM_RANDOM_H
#define VANADIUM_RANDOM_H

#if defined(VANADIUM_PLATFORM_LINUX) || defined(VANADIUM_PLATFORM_LINUX)
#include "../platform/default/DefaultRandom.h"
#else
#error "Not a supported platform."
#endif

#endif //VANADIUM_RANDOM_H
