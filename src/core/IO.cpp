#include "core/IO.h"

#include "core/Log.h"
#if defined(VANADIUM_PLATFORM_LINUX) | defined(VANADIUM_PLATFORM_MACOS) | \
    defined(VANADIUM_PLATFORM_WINDOWS)
#include "platform/default/DefaultIO.h"
using IOImpl = Vanadium::DefaultIO;
#endif

namespace Vanadium {

IO *IO::instance = nullptr;

IO *IO::getInstance() {
  if (IO::instance == nullptr) {
    IO::instance = new IOImpl();
  }
  return IO::instance;
}

}  // namespace Vanadium