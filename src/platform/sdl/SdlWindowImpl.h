#pragma once

#include "SdlIncludes.h"
#include "core/interfaces/Window.h"
#include "core/types/Reference.h"

struct SDL_SysWMinfo;

namespace vanadium {

class SdlWindowImpl : public Window {
 private:
  SDL_Window *_window = nullptr;
  UniqueRef<SDL_SysWMinfo> _wmi;

  std::string _title;
  WindowType _windowType;

  void init(const WindowProperties &properties);

 public:
  explicit SdlWindowImpl(const WindowProperties &properties);

  ~SdlWindowImpl() override;

  void setTitle(const std::string &newTitle) noexcept override;
  [[nodiscard]] const std::string &getTitle() const noexcept override;
  // Geometry
  void setWidth(unsigned int newWidth) noexcept override;
  void setHeight(unsigned int newHeight) noexcept override;
  [[nodiscard]] glm::ivec2 getGeometry() const noexcept override;
  void setGeometry(const glm::ivec2 &geometry) noexcept override;
  [[nodiscard]] float getAspect() const noexcept override;

  // Position.
  void setPositionX(int posX) noexcept override;
  void setPositionY(int posY) noexcept override;
  [[nodiscard]] glm::ivec2 getPosition() const noexcept override;
  void setPosition(const glm::ivec2 &position) override;

  void grabCursor(bool isCursorGrabbed) noexcept override;
  bool isCursorGrabbed() noexcept override;
  [[nodiscard]] void *getRaw() const noexcept override;
  void setDoubleBuffering(bool isDoubleBuffering) override;
  void setType(WindowType newType) noexcept override;
  [[nodiscard]] WindowType getType() const noexcept override;
  [[nodiscard]] bool isDoubleBuffering() const noexcept override;
  void swapBuffer() override;
  [[nodiscard]] void *getNativeDisplayType() const noexcept override;
  [[nodiscard]] void *getNativeWindowHandle() const noexcept override;
};

}  // namespace vanadium
