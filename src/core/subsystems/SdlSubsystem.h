#pragma once

#include "core/interfaces/Subsystem.h"

namespace vanadium {

class SdlSubsystem : public Subsystem {
 public:
  SdlSubsystem();

  void init() override;
  void shutdown() override;
};

}  // namespace vanadium
