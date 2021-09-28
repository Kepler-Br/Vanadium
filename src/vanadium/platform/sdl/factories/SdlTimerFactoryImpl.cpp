#include "SdlTimerFactoryImpl.h"

#include "vanadium/platform/sdl/SdlTimerImpl.h"

namespace vanadium {

const std::string SdlTimerFactoryImpl::_implName = "SdlTimerFactoryImpl";

Ref<Timer> SdlTimerFactoryImpl::construct() { return MakeRef<SdlTimerImpl>(); }

Ref<Timer> SdlTimerFactoryImpl::construct(std::function<void(float)> callback,
                                          float seconds, bool repeating,
                                          bool startImmediately) {
  Ref<SdlTimerImpl> timer =
      MakeRef<SdlTimerImpl>(std::move(callback), seconds, repeating);

  if (startImmediately) {
    timer->start();
  }

  return timer;
}

const std::string &SdlTimerFactoryImpl::getImplName() const noexcept {
  return SdlTimerFactoryImpl::_implName;
}

}  // namespace vanadium
