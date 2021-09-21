#pragma once

#include <string>
#include <vector>

namespace vanadium {

class EngineEndMainLoop;
class MainLoop;
class Window;
class ApplicationProperties;

class Application {
 public:
  virtual ~Application() = default;

  [[nodiscard]] virtual Ref<UserEndEventProvider> getEventProvider()
      const noexcept = 0;
  [[nodiscard]] virtual Ref<Window> getWindow() const noexcept = 0;
  [[nodiscard]] virtual Ref<UserEndStateStack> getStateStack()
      const noexcept = 0;
  [[nodiscard]] virtual Ref<MainLoop> getMainLoop() const noexcept = 0;
  virtual void stop() = 0;
  [[nodiscard]] virtual const std::vector<std::string> &getProgramArguments()
      const noexcept = 0;
};

class EngineEndApplication : public Application {
 public:
  ~EngineEndApplication() override = default;

  virtual void deinitialize() = 0;
  virtual void run() = 0;
  virtual void preInit() = 0;
  virtual void postInit() = 0;
  virtual void setProperties(const ApplicationProperties &properties) = 0;
};

}  // namespace vanadium
