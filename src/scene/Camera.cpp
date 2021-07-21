#include "scene/Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Vanadium {

void Camera::setPerspective(float fov, float aspect, float zNear,
                            float zFar) noexcept {
  this->shouldUpdateVP = true;
  this->projection = glm::perspective(fov, aspect, zNear, zFar);
}

void Camera::setOrthographic(float left, float right, float bottom,
                             float top, float zNear,
                             float zFar) noexcept {
  this->shouldUpdateVP = true;
  this->projection = glm::ortho(left, right, bottom, top, zNear, zFar);
}

void Camera::setProjection(const glm::mat4 &matrix) noexcept {
  this->shouldUpdateVP = true;
  this->projection = matrix;
}

void Camera::setView(const glm::mat4 &matrix) noexcept {
  this->shouldUpdateVP = true;
  this->view = matrix;
}

glm::mat4 Camera::getVP() noexcept {
  if (this->shouldUpdateVP) {
    this->shouldUpdateVP = false;
    this->VP = this->projection * this->view;
  }
  return this->VP;
}

const glm::mat4 &Camera::getProjection() noexcept { return this->projection; }

const glm::mat4 &Camera::getView() noexcept { return this->view; }

void Camera::lookAt(const glm::vec3 &eye, const glm::vec3 &center,
                    const glm::vec3 &up) noexcept {
  this->shouldUpdateVP = true;
  this->view = glm::lookAt(eye, center, up);
}

glm::vec3 Camera::getUp() noexcept {
  return glm::vec3(-this->view[0][1], -this->view[1][1], -this->view[2][1]);
}

glm::vec3 Camera::getRight() noexcept {
  return glm::vec3(-this->view[0][0], -this->view[1][0], -this->view[2][0]);
}

glm::vec3 Camera::getForward() noexcept {
  return glm::vec3(this->view[0][2], this->view[1][2], this->view[2][2]);
}

}  // namespace Vanadium