#include "core/IO.h"

#include "core/Log.h"
#if defined(VANADIUM_PLATFORM_LINUX) | defined(VANADIUM_PLATFORM_MACOS)
#include "platform/default/DefaultIO.h"
using IOImpl = Vanadium::DefaultIO;
#endif

namespace Vanadium {

IO *IO::instance = nullptr;

IO *IO::getInstance() {
  if (IO::instance == nullptr) IO::instance = IO::create();
  return IO::instance;
}

IO *IO::create() {
  IO::instance = new IOImpl();
  return IO::instance;
}

}  // namespace Vanadium