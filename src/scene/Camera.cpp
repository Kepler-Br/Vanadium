#include "scene/Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace vanadium {

void Camera::setPerspective(float fov, float aspect, float zNear,
                            float zFar) noexcept {
  this->_shouldUpdateVP = true;
  this->_projection = glm::perspective(fov, aspect, zNear, zFar);
}

void Camera::setOrthographic(float left, float right, float bottom, float top,
                             float zNear, float zFar) noexcept {
  this->_shouldUpdateVP = true;
  this->_projection = glm::ortho(left, right, bottom, top, zNear, zFar);
}

void Camera::setProjection(const glm::mat4 &matrix) noexcept {
  this->_shouldUpdateVP = true;
  this->_projection = matrix;
}

void Camera::setView(const glm::mat4 &matrix) noexcept {
  this->_shouldUpdateVP = true;
  this->_view = matrix;
}

glm::mat4 Camera::getVP() noexcept {
  if (this->_shouldUpdateVP) {
    this->_shouldUpdateVP = false;
    this->_vp = this->_projection * this->_view;
  }
  return this->_vp;
}

const glm::mat4 &Camera::getProjection() noexcept { return this->_projection; }

const glm::mat4 &Camera::getView() noexcept { return this->_view; }

void Camera::lookAt(const glm::vec3 &eye, const glm::vec3 &center,
                    const glm::vec3 &up) noexcept {
  this->_shouldUpdateVP = true;
  this->_view = glm::lookAt(eye, center, up);
}

glm::vec3 Camera::getUp() noexcept {
  return {-this->_view[0][1], -this->_view[1][1], -this->_view[2][1]};
}

glm::vec3 Camera::getRight() noexcept {
  return {-this->_view[0][0], -this->_view[1][0], -this->_view[2][0]};
}

glm::vec3 Camera::getForward() noexcept {
  return {this->_view[0][2], this->_view[1][2], this->_view[2][2]};
}

}  // namespace vanadium