#pragma once

#include <functional>
#include <string>

#include "core/Types.h"

namespace vanadium {

class UserEndApplication;
class EventDispatcher;
class UserEndStateStack;
class UserEndEventProvider;
class Framebuffer;
class Application;
class Window;

class State {
 protected:
  UserEndApplication *_application = nullptr;
  Ref<UserEndEventProvider> _eventProvider = nullptr;
  Ref<EventDispatcher> _eventDispatcher = nullptr;
  Ref<UserEndStateStack> _stateStack = nullptr;
  Ref<Window> _window;
  std::string _name;

  virtual void onAttach(UserEndApplication *application,
                        const std::string &name) = 0;
  virtual void onDetach() = 0;
  // onStateLostPriority and onStateGainedPriority is for case when state was
  // moved from first place in the state queue.
  virtual void onStateLostPriority() = 0;
  virtual void onStateGainedPriority() = 0;

 public:
  // NOT SUPPOSED TO BE USED BY USER!
  void _onAttach(UserEndApplication *application, const std::string &name);
  void _onDetach();
  void _onStateLostPriority();
  void _onStateGainedPriority();

  State() = default;
  virtual ~State() = default;
  virtual void loadResources(const std::function<void()> &callback) = 0;
  virtual void loadResources() = 0;
  virtual void onTickStart() = 0;
  virtual void onTickEnd() = 0;
  virtual void update(double deltatime) = 0;
  virtual void fixedUpdate(double deltatime) = 0;
  virtual void preRender() = 0;
  virtual void render() = 0;
  virtual void postRender() = 0;

  [[nodiscard]] virtual const std::string &getName() const noexcept {
    return this->_name;
  };
};

}  // namespace vanadium
