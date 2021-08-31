#include "Model.h"

#include <core/math/Math.h>

Model::Model() {
  auto lerpFloatPtr = [](float &from, const float &to, float step) {
    vanadium::math::lerpRef(from, to, step);
  };
  auto lerpVec2Ptr =
      static_cast<void (*)(glm::vec2 &, const glm::vec2 &, float)>(
          vanadium::math::lerpRef);
  auto lerpVec4Ptr =
      static_cast<void (*)(glm::vec4 &, const glm::vec4 &, float)>(
          vanadium::math::lerpRef);

  this->_fractalParameter =
      vanadium::MakeRef<Lerpable<float>>(0.0f, 18.0f, lerpFloatPtr);
  this->_radius = vanadium::MakeRef<Lerpable<float>>(1.5f, 18.0f, lerpFloatPtr);
  this->_bailout = vanadium::MakeRef<Lerpable<float>>(2.0f, 18.0f, lerpFloatPtr);
  this->_iterations = vanadium::MakeRef<Lerpable<float>>(10.0f, 18.0f, lerpFloatPtr);
  this->_auraColor = vanadium::MakeRef<Lerpable<glm::vec4>>(
      glm::vec4(0.1f, 0.0f, 0.02f, 1.0f), 18.0f, lerpVec4Ptr);
  this->_cameraAngle = vanadium::MakeRef<Lerpable<glm::vec2>>(
      glm::vec2(-0.950f, 2.420f), 18.0f, lerpVec2Ptr);
}

void Model::update(double deltatime) {
  auto floatDeltatime = (float)deltatime;

  this->_fractalParameter->update(floatDeltatime);
  this->_radius->update(floatDeltatime);
  this->_auraColor->update(floatDeltatime);
  this->_cameraAngle->update(floatDeltatime);
  this->_bailout->update(floatDeltatime);
  this->_iterations->update(floatDeltatime);
}

float &Model::getFractalParameterRef() {
  return this->_fractalParameter->getValue();
}

float Model::getLerpedFractalParameterRef() const {
  return this->_fractalParameter->getLerped();
}

void Model::setFractalParameter(float parameter) {
  this->_fractalParameter->setValue(parameter);
}

float &Model::getRadiusRef() { return this->_radius->getValue(); }

float Model::getLerpedRadius() const { return this->_radius->getLerped(); }

void Model::setRadius(float radius) { this->_radius->setValue(radius); }

glm::vec4 &Model::getAuraColorRef() { return this->_auraColor->getValue(); }

glm::vec4 Model::getLerpedAuraColor() const {
  return this->_auraColor->getLerped();
}

void Model::setAuraColor(const glm::vec4 &color) {
  this->_auraColor->setValue(color);
}

glm::vec2 &Model::getCameraAngleRef() { return this->_cameraAngle->getValue(); }

glm::vec2 Model::getLerpedCameraAngle() const {
  return this->_cameraAngle->getLerped();
}

void Model::setCameraAngle(const glm::vec2 &angle) {
  this->_cameraAngle->setValue(angle);
}
float &Model::getBailoutRef() { return this->_bailout->getValue(); }
float Model::getLerpedBailout() const { return this->_bailout->getLerped(); }
void Model::setBailout(const float value) { this->_bailout->setValue(value); }

float &Model::getIterationsRef() { return this->_iterations->getValue(); }
float Model::getLerpedIterations() const { return this->_iterations->getLerped(); }
void Model::setIterations(const float value) { this->_iterations->setValue(value); }
