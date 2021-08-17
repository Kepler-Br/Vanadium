#pragma once

#if defined(VANADIUM_PLATFORM_MACOS) || defined(VANADIUM_PLATFORM_LINUX) || \
    defined(VANADIUM_PLATFORM_WINDOWS)
#include "platform/sdl/SdlDialogs.h"

namespace vanadium {
using Dialogs = vanadium::SdlDialogs;
}

#endif
