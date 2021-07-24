#ifndef VANADIUM_SUBSYSTEM_VFSSUBSYSTEM_H
#define VANADIUM_SUBSYSTEM_VFSSUBSYSTEM_H

#include "core/interfaces/Subsystem.h"
namespace vanadium {

class VfsSubsystem : public Subsystem {
 protected:
  std::string _workingDirectory;

 public:
  explicit VfsSubsystem(std::string workingDirectory);

  void init() override;
  void shutdown() override;
};

}  // namespace vanadium

#endif  // VANADIUM_SUBSYSTEM_VFSSUBSYSTEM_H
