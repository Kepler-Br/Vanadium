#include "DefaultEventProvider.h"

namespace Vanadium
{


DefaultEventProvider::DefaultEventProvider(Window *window) :
        EventProvider(window)
{

}

void DefaultEventProvider::update() noexcept
{

}

bool DefaultEventProvider::isKeyPressed(uint16_t keycode) const noexcept
{
    return false;
}

bool DefaultEventProvider::isKeyReleased(uint16_t keycode) const noexcept
{
    return false;
}

bool DefaultEventProvider::isKeyJustPressed(uint16_t keycode) const noexcept
{
    return false;
}

bool DefaultEventProvider::isKeyJustReleased(uint16_t keycode) const noexcept
{
    return false;
}

bool DefaultEventProvider::isMousePressed(uint16_t keycode) const noexcept
{
    return false;
}

bool DefaultEventProvider::isMouseReleased(uint16_t keycode) const noexcept
{
    return false;
}

bool DefaultEventProvider::isMouseJustPressed(uint16_t keycode) const noexcept
{
    return false;
}

bool DefaultEventProvider::isMouseJustReleased(uint16_t keycode) const noexcept
{
    return false;
}

glm::ivec2 DefaultEventProvider::getMouseDelta() const noexcept
{
    return this->mouseDelta;
}

glm::ivec2 DefaultEventProvider::getMousePosition() const noexcept
{
    return this->mousePosition;
}
}