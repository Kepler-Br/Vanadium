#pragma once

#include "core/Log.h"
#include "core/interfaces/Subsystem.h"

namespace vanadium {

class LoggingSubsystem : public Subsystem {
 private:
  std::string _name;
  std::size_t _initializationStage;
  bool _initialized = false;

 public:
  /**
   * Defaults name to logging and initializationStage to 0.
   */
  LoggingSubsystem();
  LoggingSubsystem(std::string name, std::size_t initializationStage);

  void initialize(EngineEndApplication &application) override;
  void deinitialize() override;

  [[nodiscard]] const std::string &getName() const noexcept override;

  [[nodiscard]] std::size_t getInitializationStage() const noexcept override;

  [[nodiscard]] bool isInitialized() const noexcept override;
};

}  // namespace vanadium
