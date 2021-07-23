#ifndef VANADIUM_DEFAULTWINDOW_H
#define VANADIUM_DEFAULTWINDOW_H

#include "DefaultIncludes.h"
#include "core/Window.h"
#include "graphics/BgfxCallback.h"

struct SDL_SysWMinfo;

namespace vanadium {

class DefaultWindow : public Window {
 private:
  SDL_Window *_window = nullptr;
  SDL_SysWMinfo *_wmi;

  std::string _title;
  WindowType _windowType;

  void init(const WindowProperties &properties);
  void createWindow(const WindowProperties &properties);

 public:
  explicit DefaultWindow(const WindowProperties &properties);

  ~DefaultWindow() override;

  void setTitle(const std::string &newTitle) noexcept override;
  const std::string &getTitle() const noexcept override;
  // Geometry
  void setWidth(uint newWidth) noexcept override;
  void setHeight(uint newHeight) noexcept override;
  const glm::ivec2 getGeometry() const noexcept override;
  void setGeometry(const glm::ivec2 &geometry) noexcept override;
  float getAspect() const noexcept override;

  // Position.
  void setPositionX(int posX) noexcept override;
  void setPositionY(int posY) noexcept override;
  const glm::ivec2 getPosition() const noexcept override;
  void setPosition(const glm::ivec2 &position) override;

  void grabCursor(bool isCursorGrabbed) noexcept override;
  bool isCursorGrabbed() noexcept override;
  void *getRaw() const noexcept override;
  void setDoubleBuffering(bool isDoubleBuffering) override;
  void setType(WindowType newType) noexcept override;
  WindowType getType() const noexcept override;
  bool isDoubleBuffering() const noexcept override;
  void swapBuffer() override;
  void *getNativeDisplayType() const noexcept override;
  void *getNativeWindowHandle() const noexcept override;
};

}  // namespace vanadium

#endif  // VANADIUM_DEFAULTWINDOW_H
