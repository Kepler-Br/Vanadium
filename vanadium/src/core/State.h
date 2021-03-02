#ifndef VANADIUM_STATE_H
#define VANADIUM_STATE_H

#include <functional>
#include <string>
#include "Types.h"

namespace Vanadium
{

class UserEndApplication;
class EventDispatcher;
class UserEndStateStack;
class UserEndEventProvider;
class Framebuffer;
class Application;
class Window;

class State
{
protected:
    UserEndApplication *application = nullptr;
    UserEndEventProvider *eventProvider = nullptr;
    EventDispatcher *eventDispatcher = nullptr;
    UserEndStateStack *stateStack = nullptr;
    Window *window = nullptr;
    std::string name;

    virtual void onAttach(UserEndApplication *application, const std::string &name) = 0;
    virtual void onDetach() = 0;
    // Todo: think about another name.
    // onStateLostPriority and onStateGainedPriority is for case when state was moved from first place in the state queue.
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
    // Todo: use this functions while loading resources. It is now called only OnAttach method.
    virtual void loadResources(const std::function<void ()> &callback) = 0;
    virtual void loadResources() = 0;
    virtual void onTickStart() = 0;
    virtual void onTickEnd() = 0;
    virtual void update(double deltatime) = 0;
    virtual void fixedUpdate(double deltatime) = 0;
    virtual void preRender() = 0;
    virtual void render() = 0;
    virtual void postRender() = 0;
//    virtual Ref<Framebuffer> getTargetFramebuffer() const noexcept = 0;

    [[nodiscard]]
    virtual const std::string &getName() const noexcept = 0;

};

}

#endif //VANADIUM_STATE_H
