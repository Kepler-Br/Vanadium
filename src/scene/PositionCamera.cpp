#include "scene/PositionCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Vanadium {

PositionCamera::PositionCamera(const glm::vec3 &eye, const glm::vec3 &center,
                               const glm::vec3 &up)
    : eye(eye), center(center), up(up) {
  this->shouldUpdateVP = true;
  this->view = glm::lookAt(this->eye, this->center, this->up);
}

void PositionCamera::lookAt(const glm::vec3 &eye, const glm::vec3 &center,
                            const glm::vec3 &up) noexcept {
  this->shouldUpdateVP = true;
  this->eye = eye;
  this->center = center;
  this->up = up;
  this->view = glm::lookAt(this->eye, this->center, this->up);
}

void PositionCamera::addLookAt(const glm::vec3 &eye, const glm::vec3 &center,
                               const glm::vec3 &up) noexcept {
  this->shouldUpdateVP = true;
  this->eye += eye;
  this->center += center;
  this->up += up;
  this->view = glm::lookAt(this->eye, this->center, this->up);
}

void PositionCamera::addPosition(const glm::vec3 &position) {
  this->eye += position;
  this->center += position;
  this->lookAt(this->eye, this->center, this->up);
}

void PositionCamera::setPosition(const glm::vec3 &position) {
  this->eye = position;
  this->lookAt(this->eye, this->center, this->up);
}

const glm::vec3 &PositionCamera::getPosition() { return this->eye; }

const glm::vec3 &PositionCamera::getCenter() { return this->center; }

void PositionCamera::setCenter(const glm::vec3 &newCenter) {
  this->center = newCenter;
  this->lookAt(this->eye, this->center, this->up);
}

void PositionCamera::addCenter(const glm::vec3 &newCenter) {
  this->center += newCenter;
  this->lookAt(this->eye, this->center, this->up);
}

const glm::vec3 &PositionCamera::getWorldUp() { return this->up; }

}  // namespace Vanadium