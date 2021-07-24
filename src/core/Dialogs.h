#ifndef VANADIUM_DIALOGS_H
#define VANADIUM_DIALOGS_H

#if defined(VANADIUM_PLATFORM_MACOS) || defined(VANADIUM_PLATFORM_LINUX) || \
    defined(VANADIUM_PLATFORM_WINDOWS)
#include "../platform/default/DefaultDialogs.h"
namespace vanadium {
using Dialogs = vanadium::DefaultDialogs;
}
#endif

#endif  // VANADIUM_DIALOGS_H
