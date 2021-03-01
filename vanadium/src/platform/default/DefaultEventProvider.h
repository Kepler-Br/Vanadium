#ifndef VANADIUM_DEFAULTEVENTPROVIDER_H
#define VANADIUM_DEFAULTEVENTPROVIDER_H

#include <vector>

#include "../../core/EventProvider.h"
//#include "../../core/Window.h"


namespace Vanadium
{
class Window;
class Event;

// Todo: implement dispatch immediately.
class DefaultEventProvider : public EventProvider
{
private:
    glm::ivec2 mouseDelta = {0, 0};
    glm::ivec2 mousePrevPosition = {0, 0};
    glm::ivec2 mousePosition = {0, 0};
    uint32_t mouseButtonMask;
    uint32_t prevMouseButtonMask;

    uint8_t *previousKeyState;
    const uint8_t *currentKeyState;

    std::vector<Event *> eventQueue;

public:
    explicit DefaultEventProvider(Window *window);
    ~DefaultEventProvider();

    void update() noexcept override;
    void dispatch() noexcept override;

    bool isKeyPressed(Keyboard::KeyCode keycode) const noexcept override;
    bool isKeyReleased(Keyboard::KeyCode keycode) const noexcept override;
    bool isKeyJustPressed(Keyboard::KeyCode keycode) const noexcept override;
    bool isKeyJustReleased(Keyboard::KeyCode keycode) const noexcept override;

    bool isMousePressed(Mouse::KeyCode keycode) const noexcept override;
    bool isMouseReleased(Mouse::KeyCode keycode) const noexcept override;
    bool isMouseJustPressed(Mouse::KeyCode keycode) const noexcept override;
    bool isMouseJustReleased(Mouse::KeyCode keycode) const noexcept override;

    glm::ivec2 getMouseDelta() const noexcept override;
    glm::ivec2 getMousePosition() const noexcept override;
};

}

#endif //VANADIUM_DEFAULTEVENTPROVIDER_H
