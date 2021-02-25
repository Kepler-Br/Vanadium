#ifndef VANADIUM_DEFAULTEVENTPROVIDER_H
#define VANADIUM_DEFAULTEVENTPROVIDER_H

#include "../../core/EventProvider.h"
#include "../../core/Window.h"
#warning "DefaultEventProvider is not implemented."

namespace Vanadium
{

class DefaultEventProvider : public EventProvider
{
private:
    glm::ivec2 mouseDelta = {0, 0};
    glm::ivec2 mousePosition = {0, 0};

public:
    explicit DefaultEventProvider(Window *window);

    void update() noexcept override;

    bool isKeyPressed(uint16_t keycode) const noexcept override;
    bool isKeyReleased(uint16_t keycode) const noexcept override;
    bool isKeyJustPressed(uint16_t keycode) const noexcept override;
    bool isKeyJustReleased(uint16_t keycode) const noexcept override;

    bool isMousePressed(uint16_t keycode) const noexcept override;
    bool isMouseReleased(uint16_t keycode) const noexcept override;
    bool isMouseJustPressed(uint16_t keycode) const noexcept override;
    bool isMouseJustReleased(uint16_t keycode) const noexcept override;

    glm::ivec2 getMouseDelta() const noexcept override;
    glm::ivec2 getMousePosition() const noexcept override;
};

}

#endif //VANADIUM_DEFAULTEVENTPROVIDER_H
