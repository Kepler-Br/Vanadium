#pragma once

#include "core/interfaces/Subsystem.h"
namespace vanadium {

class VfsSubsystem : public Subsystem {
 private:
  std::string _workingDirectory;

 public:
  explicit VfsSubsystem(std::string workingDirectory);

  void init() override;
  void shutdown() override;
};

}  // namespace vanadium
