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
protected:
    std::string title;
    VNsize width;
    VNsize height;

public:
    virtual ~Window() = default;

    virtual void setTitle(const std::string &title) noexcept = 0;
    virtual std::string getTitle() const noexcept = 0;
    // Geometry
    virtual VNsize getWidth() const noexcept = 0;
    virtual VNsize getHeight() const noexcept = 0;
    virtual void setWidth(VNsize width) noexcept = 0;
    virtual void setHeight(VNsize width) noexcept = 0;
    virtual glm::ivec2 getGeometry() const noexcept = 0;
    virtual void setGeometry(const glm::ivec2 &geometry) noexcept = 0;

    virtual void* getNative() const noexcept = 0;
    virtual void setVsync(bool isVsync) noexcept = 0;
    virtual void setDoubleBuffering(bool isDoubleBuffering) = 0;
    virtual void swapBuffer() = 0;

};

class WindowFactory
{
public:
    static Window *create(const std::string &title, const glm::ivec2 &geometry);
    static Window *create(const std::string &title, uint32_t width, uint32_t height);
};

}
#endif //VANADIUM_WINDOW_H
