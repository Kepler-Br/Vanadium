#pragma once

#include "core/interfaces/Subsystem.h"
#include "core/types/Reference.h"

namespace vanadium {

class EngineEndApplication;

class ApplicationInitHook {
 public:
  virtual ~ApplicationInitHook() = default;

  /**
   * Will run before application initialization.
   * @param application pointer to hooked application class.
   * @throws InitializationInterrupted if something gone wrong inside overridden
   * method.
   */
  virtual void preInit(EngineEndApplication *application) {
    // noop.
  }
  /**
   * Will run after application initialization.
   * @param application pointer to hooked application class.
   * @throws InitializationInterrupted if something gone wrong inside overridden
   * method.
   */
  virtual void afterInit(EngineEndApplication *application) {
    // noop.
  }

  /**
   * Will run before subsystem initialization stage.
   * @param application pointer to hooked application class.
   * @param stage number of subsystem initialization stage.
   * @throws InitializationInterrupted if something gone wrong inside overridden
   * method.
   */
  virtual void preSubsystemStage(EngineEndApplication *application,
                                 std::size_t stage) {
    // noop.
  }
  /**
   * Will run after subsystem initialization stage.
   * @param application pointer to hooked application class.
   * @param stage number of subsystem initialization stage.
   * @throws InitializationInterrupted if something gone wrong inside overridden
   * method.
   */
  virtual void afterSubsystemStage(EngineEndApplication *application,
                                   std::size_t stage) {
    // noop.
  }

  /**
   * Will run before subsystem initialization.
   * @param application pointer to hooked application class.
   * @param subsystem subsystem that would be initialized.
   * @throws InitializationInterrupted if something gone wrong inside overridden
   * method.
   */
  virtual void preSubsystemInit(EngineEndApplication *application,
                                const Ref<Subsystem> &subsystem) {
    // noop.
  }
  /**
   * Will run after subsystem initialization.
   * @param application pointer to hooked application class.
   * @param subsystem subsystem that just initialized.
   * @throws InitializationInterrupted if something gone wrong inside overridden
   * method.
   */
  virtual void afterSubsystemInit(EngineEndApplication *application,
                                  const Ref<Subsystem> &subsystem) {
    // noop.
  }
};

}  // namespace vanadium
