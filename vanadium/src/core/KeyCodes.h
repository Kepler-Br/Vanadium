#ifndef VANADIUM_KEYCODES_H
#define VANADIUM_KEYCODES_H

#if defined(VANADIUM_PLATFORM_LINUX) | defined(VANADIUM_PLATFORM_MACOS)
#include "../platform/default/DefaultKeyCodes.h"
#else
#error "Not a supported platform."
#endif

#endif  // VANADIUM_KEYCODES_H
