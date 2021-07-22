#ifndef VANADIUM_DEFAULTWINDOW_H
#define VANADIUM_DEFAULTWINDOW_H

#include "BgfxCallback.h"
#include "DefaultIncludes.h"
#include "core/Window.h"

namespace vanadium {

class DefaultWindow : public Window {
 private:
  BgfxCallback bgfxCallback;
  SDL_Window *window = nullptr;

  std::string title;
  WindowType windowType;

  void init(const WindowProperties &properties);
  void createWindow(const WindowProperties &properties);
  void createContext(const WindowProperties &properties);

 public:
  explicit DefaultWindow(const WindowProperties &properties);

  ~DefaultWindow() override;

  void setTitle(const std::string &newTitle) noexcept override;
  std::string getTitle() noexcept override;
  // Geometry
  void setWidth(uint newWidth) noexcept override;
  void setHeight(uint newHeight) noexcept override;
  glm::ivec2 getGeometry() noexcept override;
  void setGeometry(const glm::ivec2 &geometry) noexcept override;
  float getAspect() noexcept override;

  // Position.
  void setPositionX(int posX) noexcept override;
  void setPositionY(int posY) noexcept override;
  glm::ivec2 getPosition() noexcept override;
  void setPosition(const glm::ivec2 &position) override;

  void grabCursor(bool isCursorGrabbed) noexcept override;
  bool isCursorGrabbed() noexcept override;
  void *getRaw() noexcept override;
  void setVsync(bool isVsync) noexcept override;
  void setDoubleBuffering(bool isDoubleBuffering) override;
  void setType(WindowType newType) noexcept override;
  WindowType getType() noexcept override;
  bool isDoubleBuffering() noexcept override;
  void swapBuffer() override;
};

}  // namespace vanadium

#endif  // VANADIUM_DEFAULTWINDOW_H
