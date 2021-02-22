#ifndef VANADIUM_WINDOW_H
#define VANADIUM_WINDOW_H

#include <string>
#include "../event/Event.h"
#include <glm/vec2.hpp>

namespace Van
{

class Window
{
protected:
    std::string title;
    uint32_t width;
    uint32_t height;

public:
    virtual ~Window() = default;

    virtual void setTitle(const std::string &title) noexcept { this->title = title; }
    virtual std::string getTitle() const noexcept { return this->title; }
    // Geometry
    virtual uint32_t getWidth() const noexcept { return this->width; }
    virtual uint32_t getHeight() const noexcept { return this->height; }
    virtual void setWidth(uint32_t width) noexcept = 0;
    virtual void setHeight(uint32_t width) noexcept = 0;
    virtual glm::ivec2 getGeometry() const noexcept { return {this->width, this->height}; }
    virtual void setGeometry(const glm::ivec2 &geometry) noexcept = 0;

    virtual void* getNative() const noexcept = 0;
    virtual void setVsync(bool isVsync) noexcept = 0;
    virtual void setDoubleBuffering(bool isDoubleBuffering) = 0;
    virtual void swapBuffer() = 0;

    static Window *create(const std::string &title, const glm::ivec2 &geometry);
    static Window *create(const std::string &title, uint32_t width, uint32_t height);
};

}
#endif //VANADIUM_WINDOW_H
