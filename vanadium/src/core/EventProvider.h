#ifndef VANADIUM_EVENTPROVIDER_H
#define VANADIUM_EVENTPROVIDER_H

#include <functional>
#include "../event/Event.h"

#include "Window.h"
#include "KeyCodes.h"

namespace Vanadium
{

class UserEndEventProvider
{
    using EventCallback = std::function<void(Event *)>;

public:
    virtual bool isKeyPressed(Keyboard::KeyCode keycode) const noexcept = 0;
    virtual bool isKeyReleased(Keyboard::KeyCode keycode) const noexcept = 0;
    virtual bool isKeyJustPressed(Keyboard::KeyCode keycode) const noexcept = 0;
    virtual bool isKeyJustReleased(Keyboard::KeyCode keycode) const noexcept = 0;
    virtual bool isMousePressed(Mouse::KeyCode keycode) const noexcept = 0;
    virtual bool isMouseReleased(Mouse::KeyCode keycode) const noexcept = 0;
    virtual bool isMouseJustPressed(Mouse::KeyCode keycode) const noexcept = 0;
    virtual bool isMouseJustReleased(Mouse::KeyCode keycode) const noexcept = 0;
    virtual glm::ivec2 getMouseDelta() const noexcept = 0;
    virtual glm::ivec2 getMousePosition() const noexcept = 0;
    virtual void setEventCallback(EventCallback eventCallback) noexcept = 0;
};

class EventProvider: public UserEndEventProvider
{
protected:
    using EventCallback = std::function<void(Event *)>;

    Window *window;
    EventCallback eventCallback;
//    bool dispatchEventsImmediately = true;

public:
    explicit EventProvider(Window *window):
            window(window)
    {}
    virtual ~EventProvider() = default;

    virtual void update() noexcept = 0;
    virtual void dispatch() noexcept = 0;
//    virtual void setDispatchImmediately(bool isDispatchingImmediately) noexcept
//    { this->dispatchEventsImmediately = isDispatchingImmediately; }
    void setEventCallback(EventCallback eventCallback) noexcept override
    { this->eventCallback = eventCallback; }

};

class EventProviderFactory
{
public:
    static EventProvider *create(Window *window);
};

}
#endif //VANADIUM_EVENTPROVIDER_H
