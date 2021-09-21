#pragma once

#include <functional>
#include <string>

#include "core/Types.h"

namespace vanadium {

class UserEndApplication;
class EventDispatcher;
class UserEndStateStack;
class UserEndEventProvider;
class Application;
class Window;

class State {
 protected:
  WeakRef<Application> _application;
  WeakRef<UserEndEventProvider> _eventProvider;
  WeakRef<EventDispatcher> _eventDispatcher;
  WeakRef<UserEndStateStack> _stateStack;
  WeakRef<Window> _window;

  virtual void onAttach(Ref<Application> application) = 0;
  virtual void onDetach() = 0;
  // onStateLostPriority and onStateGainedPriority is for case when state was
  // moved from first place in the state queue.
  virtual void onStateLostPriority() = 0;
  virtual void onStateGainedPriority() = 0;

 public:
  // NOT SUPPOSED TO BE USED BY USER!
  void _onAttach(WeakRef<Application> application);
  void _onDetach();
  void _onStateLostPriority();
  void _onStateGainedPriority();

  State() = default;
  virtual ~State() = default;
  virtual void loadResources(const std::function<void()> &callback) = 0;
  virtual void loadResources() = 0;
  virtual void onTickStart() = 0;
  virtual void onTickEnd() = 0;
  virtual void update(float deltatime) = 0;
  virtual void fixedUpdate(float deltatime) = 0;
  virtual void preRender() = 0;
  virtual void render() = 0;
  virtual void postRender() = 0;

  [[nodiscard]] virtual const std::string &getName() const noexcept = 0;
};

}  // namespace vanadium
