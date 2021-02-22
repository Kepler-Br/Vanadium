#ifndef VANADIUM_EVENTPROVIDER_H
#define VANADIUM_EVENTPROVIDER_H

#include <functional>
#include "../event/Event.h"

#include "Window.h"

namespace Van
{

class UserEndEventProvider
{
public:
    virtual bool isKeyPressed(uint16_t keycode) const noexcept = 0;
    virtual bool isKeyReleased(uint16_t keycode) const noexcept = 0;
    virtual bool isKeyJustPressed(uint16_t keycode) const noexcept = 0;
    virtual bool isKeyJustReleased(uint16_t keycode) const noexcept = 0;
    virtual bool isMousePressed(uint16_t keycode) const noexcept = 0;
    virtual bool isMouseReleased(uint16_t keycode) const noexcept = 0;
    virtual bool isMouseJustPressed(uint16_t keycode) const noexcept = 0;
    virtual bool isMouseJustReleased(uint16_t keycode) const noexcept = 0;
    virtual glm::ivec2 getMouseDelta() const noexcept = 0;
    virtual glm::ivec2 getMousePosition() const noexcept = 0;
};

class EventProvider: public UserEndEventProvider
{
protected:
    using EventCallback = std::function<void(Event &)>;

    Window *window;
    EventCallback eventCallback;
    bool dispatchEventsImmediately = true;

public:
    explicit EventProvider(Window *window):
            window(window)
    {}
    virtual ~EventProvider() = default;

    virtual Window *getWindow() const noexcept { return this->window; };
    virtual void update() noexcept = 0;
    virtual void setDispatchImmediately(bool isDispatchingImmediately) noexcept
    { this->dispatchEventsImmediately = isDispatchingImmediately; }
    virtual void setEventCallback(const EventCallback &eventCallback) noexcept
    { this->eventCallback = eventCallback; }

    static EventProvider *create(Window *window);

};

}
#endif //VANADIUM_EVENTPROVIDER_H
