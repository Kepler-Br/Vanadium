#ifndef VANADIUM_DEFAULTWINDOW_H
#define VANADIUM_DEFAULTWINDOW_H

#include "../../core/Window.h"
#include <SDL2/SDL.h>

namespace Van
{

class DefaultWindow : public Window
{
public:
    DefaultWindow(const std::string &title, uint32_t width, uint32_t height)
    {
        this->title = title;
        this->width = width;
        this->height = height;
    }

    ~DefaultWindow()
    {

//        SDL_GL_DeleteContext(this->glContext);
//        SDL_DestroyWindow(this->window);
        SDL_Quit();
    }

    void setTitle(const std::string &title) noexcept override
    {

    }
    std::string getTitle() const noexcept override
    {
        return this->title;
    }
    // Geometry
    uint32_t getWidth() const noexcept override
    {
        return this->width;
    }
    uint32_t getHeight() const noexcept override
    {
        return this->height;
    }
    void setWidth(uint32_t width) noexcept override
    {

    }
    void setHeight(uint32_t width) noexcept override
    {

    }
    glm::ivec2 getGeometry() const noexcept override
    {
        return {this->width, this->height};
    }
    void setGeometry(const glm::ivec2 &geometry) noexcept override
    {

    }

    void* getNative() const noexcept override
    {

    }
    void setVsync(bool isVsync) noexcept override
    {

    }
    void setDoubleBuffering(bool isDoubleBuffering) override
    {

    }
    void swapBuffer() override
    {

    }
};

}

#endif //VANADIUM_DEFAULTWINDOW_H
