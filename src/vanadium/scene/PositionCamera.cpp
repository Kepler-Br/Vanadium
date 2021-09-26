#include "vanadium/scene/PositionCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace vanadium {

PositionCamera::PositionCamera(const glm::vec3 &eye, const glm::vec3 &center,
                               const glm::vec3 &up)
    : _eye(eye), _center(center), _up(up) {
  this->_shouldUpdateVP = true;
  this->_view = glm::lookAt(this->_eye, this->_center, this->_up);
}

void PositionCamera::lookAt(const glm::vec3 &eye, const glm::vec3 &center,
                            const glm::vec3 &up) noexcept {
  this->_shouldUpdateVP = true;
  this->_eye = eye;
  this->_center = center;
  this->_up = up;
  this->_view = glm::lookAt(this->_eye, this->_center, this->_up);
}

void PositionCamera::addLookAt(const glm::vec3 &eye, const glm::vec3 &center,
                               const glm::vec3 &up) noexcept {
  this->_shouldUpdateVP = true;
  this->_eye += eye;
  this->_center += center;
  this->_up += up;
  this->_view = glm::lookAt(this->_eye, this->_center, this->_up);
}

void PositionCamera::addPosition(const glm::vec3 &position) {
  this->_eye += position;
  this->_center += position;
  this->lookAt(this->_eye, this->_center, this->_up);
}

void PositionCamera::setPosition(const glm::vec3 &position) {
  this->_eye = position;
  this->lookAt(this->_eye, this->_center, this->_up);
}

const glm::vec3 &PositionCamera::getPosition() { return this->_eye; }

const glm::vec3 &PositionCamera::getCenter() { return this->_center; }

void PositionCamera::setCenter(const glm::vec3 &newCenter) {
  this->_center = newCenter;
  this->lookAt(this->_eye, this->_center, this->_up);
}

void PositionCamera::addCenter(const glm::vec3 &newCenter) {
  this->_center += newCenter;
  this->lookAt(this->_eye, this->_center, this->_up);
}

const glm::vec3 &PositionCamera::getWorldUp() { return this->_up; }

}  // namespace vanadium