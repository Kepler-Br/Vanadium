#pragma once

#include <functional>

#include "core/types/Reference.h"

namespace vanadium {

class EventDispatcher;
class Application;

class State {
 public:
  virtual ~State() = default;

  /**
   * Called when a state has been placed in the state queue.
   * @param application Reference to main application.
   */
  virtual void onAttach(WeakRef<Application> application) = 0;
  /**
   * Called when state leaves the state queue.
   */
  virtual void onDetach() = 0;
  /**
   * Called when this state goes down from the first place in the state queue.
   * The state will not receive any events after this method was called.
   */
  virtual void onStateLostPriority() = 0;
  /**
   * Called when this state moves to the top in the state queue.
   * The state will receive events after this method was called.
   */
  virtual void onStateGainedPriority() = 0;
  /**
   * Load state resources here.
   * Supposed to be <strong>asynchronous</strong>.
   */
  virtual void loadResources(const std::function<void()> &callback) = 0;
  /**
   * Load state resources here.
   * Supposed to be <strong>synchronous</strong>.
   */
  virtual void loadResources() = 0;

  /**
   * On mainloop's new tick iteration.
   */
  virtual void onTickStart() = 0;
  /**
   * On mainloop's tick iteration end.
   * Called after update, fixedUpdate, preRender, render, postRender.
   */
  virtual void onTickEnd() = 0;
  /**
   * Called every frame before fixedUpdate, preRender, render, postRender.
   * @param deltaTime Time passed since last frame in seconds.
   */
  virtual void update(float deltaTime) = 0;
  /**
   * Called every fixed amount of time before preRender, render, postRender.
   * @param deltaTime Fixed time in seconds.
   */
  virtual void fixedUpdate(float deltaTime) = 0;
  /**
   * Before render happens.
   */
  virtual void preRender() = 0;
  /**
   * Rendering should happen here.
   */
  virtual void render() = 0;
  /**
   * After render happens.
   */
  virtual void postRender() = 0;

  /**
   * @return State name.
   */
  [[nodiscard]] virtual const std::string &getName() const noexcept = 0;

  /**
   * @return Reference to state's event dispatcher.
   * Used by Application for reassigning EventDispatcher to EventProvider
   * when state gains priority.
   */
  [[nodiscard]] virtual const Ref<EventDispatcher> getEventDispatcher()
      const noexcept = 0;
};

}  // namespace vanadium
