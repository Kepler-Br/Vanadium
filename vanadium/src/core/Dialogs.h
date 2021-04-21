#ifndef VANADIUM_DIALOGS_H
#define VANADIUM_DIALOGS_H

#if defined(VANADIUM_PLATFORM_MACOS) || defined(VANADIUM_PLATFORM_LINUX)
#include "../platform/default/DefaultDialogs.h"
namespace Vanadium {
using Dialogs = Vanadium::DefaultDialogs;
}
#else
#error "Not supported platform!"
#endif

#endif  // VANADIUM_DIALOGS_H
