#ifndef VANADIUM_DEFAULTWINDOW_H
#define VANADIUM_DEFAULTWINDOW_H

#include "../../core/Window.h"
#include <SDL2/SDL.h>

namespace Vanadium
{

struct Sdl2OpenGLNative
{
    SDL_GLContext glContext;
    SDL_Window *window;
};

class DefaultWindow : public Window
{
private:
    SDL_GLContext glContext = nullptr;
    SDL_Window *window = nullptr;
    void *native = nullptr;

    void init();
    void updateNativeStruct();
    void createWindow();

public:
    DefaultWindow(const std::string &title, uint32_t width, uint32_t height);

    ~DefaultWindow() override;

    void setTitle(const std::string &title) noexcept override;
    std::string getTitle() const noexcept override;
    // Geometry
    uint32_t getWidth() const noexcept override;
    uint32_t getHeight() const noexcept override;
    void setWidth(uint32_t width) noexcept override;
    void setHeight(uint32_t height) noexcept override;
    glm::ivec2 getGeometry() const noexcept override;
    void setGeometry(const glm::ivec2 &geometry) noexcept override;

    void* getNative() const noexcept override;
    void setVsync(bool isVsync) noexcept override;
    void setDoubleBuffering(bool isDoubleBuffering) override;
    void swapBuffer() override;

};

}

#endif //VANADIUM_DEFAULTWINDOW_H
