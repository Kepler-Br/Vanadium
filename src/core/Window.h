#ifndef VANADIUM_WINDOW_H
#define VANADIUM_WINDOW_H

#include <string>
#include <functional>
#include "../event/Event.h"
#include <glm/vec2.hpp>

namespace Van
{

class Window
{
private:
    std::function<void(Event&)> eventCallback;

protected:
    std::string title;

public:
    virtual void setTitle(const std::string &title) noexcept { this->title = title; }
    virtual std::string getTitle() const noexcept { return this->title; }
    virtual uint32_t getWidth() const noexcept = 0;
    virtual uint32_t getHeight() const noexcept = 0;
    virtual void* getNative() const noexcept = 0;
    virtual void setVsync(bool isVsync) noexcept = 0;
    virtual void setEventCallback(const std::function<void(Event&)> &eventCallback)
    { this->eventCallback = eventCallback; }
    virtual void setDoubleBuffering(bool isDoubleBuffering) = 0;
    virtual void swapBuffering() = 0;

    static Window *create(const std::string &title, const glm::ivec2 &geometry);
    static Window *create(const std::string &title, uint32_t width, uint32_t height);
};

}
#endif //VANADIUM_WINDOW_H
