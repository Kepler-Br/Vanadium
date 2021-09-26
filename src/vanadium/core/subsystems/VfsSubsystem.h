#pragma once

#include "vanadium/core/interfaces/Subsystem.h"

namespace vanadium {

class VfsSubsystem : public Subsystem {
 private:
  std::string _name;
  std::size_t _initializationStage;
  bool _initialized = false;

 public:
  /**
   * Defaults name to vfs and initializationStage to 1.
   */
  VfsSubsystem();
  VfsSubsystem(std::string name, std::size_t initializationStage);

  void initialize(EngineEndApplication *application) override;
  void deinitialize() override;

  [[nodiscard]] const std::string &getName() const noexcept override;

  [[nodiscard]] std::size_t getInitializationStage() const noexcept override;

  [[nodiscard]] bool isInitialized() const noexcept override;
};

}  // namespace vanadium
