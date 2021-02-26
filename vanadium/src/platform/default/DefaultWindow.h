#ifndef VANADIUM_DEFAULTWINDOW_H
#define VANADIUM_DEFAULTWINDOW_H

#include "../../core/Window.h"
#include "DefaultIncludes.h"

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
    DefaultWindow::Specification specification;
    SDL_GLContext glContext = nullptr;
    SDL_Window *window = nullptr;
    void *native = nullptr;

    void init();
    void updateNativeStruct();
    void createWindow();
    void createContext();

public:
    explicit DefaultWindow(Window::Specification spec);

    ~DefaultWindow() override;

    void setTitle(const std::string &title) noexcept override;
    std::string getTitle() const noexcept override;
    // Geometry
    VNsize getWidth() const noexcept override;
    VNsize getHeight() const noexcept override;
    void setWidth(VNsize width) noexcept override;
    void setHeight(VNsize height) noexcept override;
    glm::ivec2 getGeometry() const noexcept override;
    void setGeometry(const glm::ivec2 &geometry) noexcept override;

    void* getNative() const noexcept override;
    void setVsync(bool isVsync) noexcept override;
    void setDoubleBuffering(bool isDoubleBuffering) override;
    void swapBuffer() override;

};

}

#endif //VANADIUM_DEFAULTWINDOW_H
