#ifndef VANADIUM_DEFAULTEVENTPROVIDER_H
#define VANADIUM_DEFAULTEVENTPROVIDER_H

#include "../../core/EventProvider.h"
#include "../../core/Window.h"

namespace Vanadium
{

class DefaultEventProvider : public EventProvider
{
private:
    glm::ivec2 mouseDelta = {0, 0};
    glm::ivec2 mousePosition = {0, 0};

public:
    explicit DefaultEventProvider(Window *window):
        EventProvider(window)
    {

    }

    void update() noexcept override
    {

    }

    bool isKeyPressed(uint16_t keycode) const noexcept override
    {
        return false;
    }
    bool isKeyReleased(uint16_t keycode) const noexcept override
    {
        return false;
    }
    bool isKeyJustPressed(uint16_t keycode) const noexcept override
    {
        return false;
    }
    bool isKeyJustReleased(uint16_t keycode) const noexcept override
    {
        return false;
    }

    bool isMousePressed(uint16_t keycode) const noexcept override
    {
        return false;
    }
    bool isMouseReleased(uint16_t keycode) const noexcept override
    {
        return false;
    }
    bool isMouseJustPressed(uint16_t keycode) const noexcept override
    {
        return false;
    }
    bool isMouseJustReleased(uint16_t keycode) const noexcept override
    {
        return false;
    }

    glm::ivec2 getMouseDelta() const noexcept override
    {
        return this->mouseDelta;
    }
    glm::ivec2 getMousePosition() const noexcept override
    {
        return this->mousePosition;
    }
};

}

#endif //VANADIUM_DEFAULTEVENTPROVIDER_H
