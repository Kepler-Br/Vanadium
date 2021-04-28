#ifndef VANADIUM_DIALOGS_H
#define VANADIUM_DIALOGS_H

#if defined(VANADIUM_PLATFORM_MACOS) || defined(VANADIUM_PLATFORM_LINUX) || \
    defined(VANADIUM_PLATFORM_WINDOWS)
#include "../platform/default/DefaultDialogs.h"
namespace Vanadium {
using Dialogs = Vanadium::DefaultDialogs;
}
#endif

#endif  // VANADIUM_DIALOGS_H
