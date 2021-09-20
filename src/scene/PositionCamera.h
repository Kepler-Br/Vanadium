#pragma once

#include "Camera.h"

namespace vanadium {

class PositionCamera : public Camera {
 protected:
  glm::vec3 _eye{};
  glm::vec3 _center{};
  glm::vec3 _up{};

 public:
  PositionCamera() = default;
  PositionCamera(const glm::vec3 &eye, const glm::vec3 &center,
                 const glm::vec3 &up);
  ~PositionCamera() override = default;

  void lookAt(const glm::vec3 &eye, const glm::vec3 &center,
              const glm::vec3 &up) noexcept override;
  void addLookAt(const glm::vec3 &eye, const glm::vec3 &center,
                 const glm::vec3 &up) noexcept;
  void addPosition(const glm::vec3 &position);
  void setPosition(const glm::vec3 &position);
  const glm::vec3 &getPosition();
  const glm::vec3 &getCenter();
  void setCenter(const glm::vec3 &newCenter);
  void addCenter(const glm::vec3 &newCenter);
  const glm::vec3 &getWorldUp();
};

}  // namespace vanadium
