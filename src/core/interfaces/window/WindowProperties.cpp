#include "WindowProperties.h"

namespace vanadium {

WindowProperties& WindowProperties::withGeometry(
    const glm::ivec2& geometry) noexcept {
  this->_geometry = geometry;

  return *this;
}
WindowProperties& WindowProperties::withTitle(
    const std::string& title) noexcept {
  this->_title = title;

  return *this;
}
WindowProperties& WindowProperties::withState(WindowState state) noexcept {
  this->_state = state;

  return *this;
}
WindowProperties& WindowProperties::withType(WindowType type) noexcept {
  this->_type = type;

  return *this;
}
WindowProperties& WindowProperties::withPosition(
    const glm::ivec2& position) noexcept {
  this->_position = position;

  return *this;
}
WindowProperties& WindowProperties::withVSync(bool vsync) noexcept {
  this->_vsync = vsync;

  return *this;
}
glm::ivec2 WindowProperties::getGeometry() const noexcept { return this->_geometry; }
std::optional<glm::ivec2> WindowProperties::getPosition() const noexcept {
  return this->_position;
}
std::string WindowProperties::getTitle() const noexcept { return this->_title; }
WindowState WindowProperties::getState() const noexcept { return this->_state; }
WindowType WindowProperties::getType() const noexcept { return this->_type; }
bool WindowProperties::getVSync() const noexcept { return this->_vsync; }
}
