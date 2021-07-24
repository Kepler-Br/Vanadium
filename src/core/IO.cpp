#include "core/IO.h"

#include "core/Log.h"
#if defined(VANADIUM_PLATFORM_LINUX) | defined(VANADIUM_PLATFORM_MACOS) | \
    defined(VANADIUM_PLATFORM_WINDOWS)
#include "platform/default/DefaultIO.h"
using IOImpl = vanadium::DefaultIO;
#endif

namespace vanadium {

Ref<IO> IO::create() { return MakeRef<IOImpl>(); }

}  // namespace vanadium
