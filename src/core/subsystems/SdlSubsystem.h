#ifndef VANADIUM_SUBSYSTEM_SDLSUBSYSTEM_H
#define VANADIUM_SUBSYSTEM_SDLSUBSYSTEM_H

#include "core/interfaces/Subsystem.h"

namespace vanadium {

class SdlSubsystem : public Subsystem {
 public:
  SdlSubsystem();

  void init() override;
  void shutdown() override;
};

}  // namespace vanadium

#endif  // VANADIUM_SUBSYSTEM_SDLSUBSYSTEM_H
