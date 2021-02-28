#ifndef VANADIUM_WINDOW_H
#define VANADIUM_WINDOW_H

#include <string>
#include "../event/Event.h"
#include "Types.h"
#include <glm/vec2.hpp>

namespace Vanadium
{

class Window
{
public:
    struct Specification
    {
        Specification(VNsize width, VNsize height):
        width(width),
        height(height)
        {}
        Specification() = default;

        VNsize width = 0, height = 0;
        std::string title = "Vanadium SDL2";
        bool vSync = true;
        bool doubleBuffering = true;
        bool resizable = false;
        bool borderless = false;
        bool fullscreen = false;
        bool invisible = false;
    };

public:
    virtual ~Window() = default;

    virtual void setTitle(const std::string &title) noexcept = 0;
    virtual std::string getTitle() noexcept = 0;
    // Geometry.
    virtual VNsize getWidth() noexcept = 0;
    virtual VNsize getHeight() noexcept = 0;
    virtual void setWidth(VNsize width) noexcept = 0;
    virtual void setHeight(VNsize width) noexcept = 0;
    virtual glm::ivec2 getGeometry() noexcept = 0;
    virtual void setGeometry(const glm::ivec2 &geometry) noexcept = 0;
    // Position.
    virtual VNint getPositionX() noexcept = 0;
    virtual VNint getPositionY() noexcept = 0;
    virtual void setPositionX(VNint posX) noexcept = 0;
    virtual void setPositionY(VNint posY) noexcept = 0;
    virtual glm::ivec2 getPosition() noexcept = 0;
    virtual void setPosition(const glm::ivec2 &position) = 0;

    virtual void grabCursor(bool isCursorGrabbed) noexcept = 0;
    virtual void* getNative() noexcept = 0;
    virtual void setVsync(bool isVsync) noexcept = 0;
    virtual void setDoubleBuffering(bool isDoubleBuffering) = 0;
    virtual bool isDoubleBuffering() noexcept = 0;
    virtual void setFullScreen(bool isFullScreen) = 0;
    virtual bool isFullScreen() noexcept = 0;
    virtual void setResizable(bool isResizable) = 0;
    virtual bool isResizable() noexcept = 0;
    virtual void setBorderless(bool isBorderless) = 0;
    virtual bool isBorderless() noexcept = 0;
    virtual void swapBuffer() = 0;
    static Window *create(const Window::Specification &spec);
};

}
#endif //VANADIUM_WINDOW_H
