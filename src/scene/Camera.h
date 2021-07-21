#ifndef VANADIUM_CAMERA_H
#define VANADIUM_CAMERA_H

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include "../core/Types.h"

namespace Vanadium {

class Camera {
 protected:
  glm::mat4 projection = glm::mat4(1.0f);
  glm::mat4 view = glm::mat4(1.0f);
  glm::mat4 VP = glm::mat4(1.0f);
  bool shouldUpdateVP = true;

 public:
  Camera() = default;
  virtual ~Camera() = default;

  virtual void setPerspective(float fov, float aspect, float zNear,
                              float zFar) noexcept;
  virtual void setOrthographic(float left, float right, float bottom,
                               float top, float zNear,
                               float zFar) noexcept;
  virtual void setProjection(const glm::mat4 &matrix) noexcept;
  virtual void setView(const glm::mat4 &matrix) noexcept;
  virtual glm::mat4 getVP() noexcept;
  virtual const glm::mat4 &getProjection() noexcept;
  virtual const glm::mat4 &getView() noexcept;
  virtual void lookAt(const glm::vec3 &eye, const glm::vec3 &center,
                      const glm::vec3 &up) noexcept;
  virtual glm::vec3 getUp() noexcept;
  virtual glm::vec3 getRight() noexcept;
  virtual glm::vec3 getForward() noexcept;
};

}  // namespace Vanadium
#endif  // VANADIUM_CAMERA_H
