#pragma once

#include <core/Types.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "../Lerpable.h"

class Model {
 private:
  vanadium::Ref<Lerpable<float>> _fractalParameter;
  vanadium::Ref<Lerpable<float>> _radius;
  vanadium::Ref<Lerpable<float>> _bailout;
  vanadium::Ref<Lerpable<float>> _iterations;
  vanadium::Ref<Lerpable<glm::vec4>> _auraColor;
  vanadium::Ref<Lerpable<glm::vec2>> _cameraAngle;

 public:
  Model();

  void update(double deltatime);

  float &getFractalParameterRef();
  [[nodiscard]] float getLerpedFractalParameterRef() const;
  void setFractalParameter(float parameter);

  float &getRadiusRef();
  [[nodiscard]] float getLerpedRadius() const;
  void setRadius(float radius);

  glm::vec4 &getAuraColorRef();
  [[nodiscard]] glm::vec4 getLerpedAuraColor() const;
  void setAuraColor(const glm::vec4 &color);

  glm::vec2 &getCameraAngleRef();
  [[nodiscard]] glm::vec2 getLerpedCameraAngle() const;
  void setCameraAngle(const glm::vec2 &angle);

  float &getBailoutRef();
  [[nodiscard]] float getLerpedBailout() const;
  void setBailout(const float value);

  float &getIterationsRef();
  [[nodiscard]] float getLerpedIterations() const;
  void setIterations(const float value);
};