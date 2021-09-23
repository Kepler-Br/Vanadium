#pragma once

#include <string>
#include <utility>

namespace vanadium {

class EngineEndApplication;

class Subsystem {
 public:
  virtual ~Subsystem() = default;

  virtual void initialize(EngineEndApplication &application) = 0;
  virtual void deinitialize() = 0;

  [[nodiscard]] virtual const std::string &getName() const noexcept = 0;

  /**
   * Determines in what stage subsystem should be initialized.
   * There are 3 stages for now:
   * 0 - Usually logging subsystem.
   * 1 - Most basic subsystems should be initialized here. Ex: SDL, VFS.;
   * 2 - Everything else. Ex: BGFX.
   * After 1 stage, such fields as Window should be initialized in Application.
   * @return number of initialization stage.
   */
  [[nodiscard]] virtual std::size_t getInitializationStage() const noexcept = 0;

  [[nodiscard]] virtual bool isInitialized() const noexcept = 0;
};

}  // namespace vanadium
