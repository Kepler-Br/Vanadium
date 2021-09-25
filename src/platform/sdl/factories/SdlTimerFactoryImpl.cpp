#include "SdlTimerFactoryImpl.h"

#include "platform/sdl/SdlTimerImpl.h"

namespace vanadium {

Ref<Timer> SdlTimerFactoryImpl::construct() {
  return MakeRef<SdlTimerImpl>();
}

Ref<Timer> SdlTimerFactoryImpl::construct(
    std::function<void(float)> callback, float seconds,
    bool repeating, bool startImmediately) {
  Ref<SdlTimerImpl> timer =
      MakeRef<SdlTimerImpl>(std::move(callback), seconds, repeating);

  if (startImmediately) {
    timer->start();
  }

  return timer;
}

}  // namespace vanadium
