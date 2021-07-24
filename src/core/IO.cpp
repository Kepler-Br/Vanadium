#include "core/IO.h"

#include "core/Log.h"
#if defined(VANADIUM_PLATFORM_LINUX) | defined(VANADIUM_PLATFORM_MACOS) | \
    defined(VANADIUM_PLATFORM_WINDOWS)
#include "platform/default/DefaultIO.h"
using IOImpl = vanadium::DefaultIO;
#endif

namespace vanadium {

IO *IO::_instance = nullptr;

IO *IO::getInstance() {
  if (IO::_instance == nullptr) {
    IO::_instance = new IOImpl();
  }
  return IO::_instance;
}

}  // namespace vanadium