#ifndef VANADIUM_KEYCODES_H
#define VANADIUM_KEYCODES_H

#ifdef VANADIUM_PLATFORM_LINUX
    #include "../platform/default/DefaultKeyCodes.h"
#else
    #error "Not supported platform."
#endif

#endif //VANADIUM_KEYCODES_H
