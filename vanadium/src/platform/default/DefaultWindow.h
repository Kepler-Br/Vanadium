#ifndef VANADIUM_DEFAULTWINDOW_H
#define VANADIUM_DEFAULTWINDOW_H

#include "../../core/Window.h"
#include "DefaultIncludes.h"

namespace Vanadium
{

class DefaultWindow : public Window
{
private:
    mutable DefaultWindow::Specification specification;
    SDL_GLContext glContext = nullptr;
    SDL_Window *window = nullptr;
    int positionX;
    int positionY;

    void init();
    void createWindow();
    void createContext();
    void updateWindowGeometryInformation();

public:
    explicit DefaultWindow(Window::Specification spec);

    ~DefaultWindow() override;

    void setTitle(const std::string &title) noexcept override;
    std::string getTitle() noexcept override;
    // Geometry
    VNsize getWidth() noexcept override;
    VNsize getHeight() noexcept override;
    void setWidth(VNsize width) noexcept override;
    void setHeight(VNsize height) noexcept override;
    glm::ivec2 getGeometry() noexcept override;
    void setGeometry(const glm::ivec2 &geometry) noexcept override;
    VNint getPositionX() noexcept override;
    VNint getPositionY() noexcept override;
    void setPositionX(VNint posX) noexcept override;
    void setPositionY(VNint posY) noexcept override;
    glm::ivec2 getPosition() noexcept override;
    void setPosition(const glm::ivec2 &position) override;
    void grabCursor(bool isCursorGrabbed) noexcept override;

    void* getRaw() noexcept override;
    void setVsync(bool isVsync) noexcept override;
    void setDoubleBuffering(bool isDoubleBuffering) override;
    bool isDoubleBuffering() noexcept override;
    void setFullScreen(bool isFullScreen) override;
    bool isFullScreen() noexcept override;
    void setResizable(bool isResizable) override;
    bool isResizable() noexcept override;
    void setBorderless(bool isBorderless) override;
    bool isBorderless() noexcept override;
    void swapBuffer() override;

};

}

#endif //VANADIUM_DEFAULTWINDOW_H
