#pragma once

#include <glm/vec2.hpp>
#include <optional>
#include <string>

namespace vanadium {

#pragma push_macro("None")
#undef None
enum class WindowType { None = 0, Fullscreen, Resizable, Borderless, Normal };
#pragma pop_macro("None")

enum class WindowState { Normal, Minimized, Maximized };

class WindowProperties {
 protected:
  glm::ivec2 _geometry = glm::ivec2(800, 600);
  std::optional<glm::ivec2> _position;
  std::string _title = "Vanadium:: window";
  WindowState _state = WindowState::Normal;
  WindowType _type = WindowType::Normal;
  bool _vsync = true;

 public:
  WindowProperties() = default;

  // Setters.
  WindowProperties &withGeometry(const glm::ivec2 &geometry) noexcept;
  WindowProperties &withTitle(const std::string &title) noexcept;
  WindowProperties &withState(WindowState state) noexcept;
  WindowProperties &withType(WindowType type) noexcept;
  WindowProperties &withPosition(const glm::ivec2 &position) noexcept;
  WindowProperties &withVSync(bool vsync) noexcept;

  // Getters.
  [[nodiscard]] glm::ivec2 getGeometry() const noexcept;
  [[nodiscard]] std::optional<glm::ivec2> getPosition() const noexcept;
  [[nodiscard]] std::string getTitle() const noexcept;
  [[nodiscard]] WindowState getState() const noexcept;
  [[nodiscard]] WindowType getType() const noexcept;
  [[nodiscard]] bool getVSync() const noexcept;
};

}  // namespace vanadium
