#ifndef VANADIUM_MATH_H
#define VANADIUM_MATH_H

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "Types.h"

namespace Vanadium {

namespace Math {

VNfloat lerpDelta(VNfloat from, VNfloat to, VNfloat t, VNfloat delta);
glm::vec2 lerpDelta(const glm::vec2 &from, const glm::vec2 &to, VNfloat t,
                    VNfloat delta);
glm::vec3 lerpDelta(const glm::vec3 &from, const glm::vec3 &to, VNfloat t,
                    VNfloat delta);
glm::vec4 lerpDelta(const glm::vec4 &from, const glm::vec4 &to, VNfloat t,
                    VNfloat delta);

VNfloat lerp(VNfloat from, VNfloat to, VNfloat t);
glm::vec2 lerp(const glm::vec2 &from, const glm::vec2 &to, VNfloat t);
glm::vec3 lerp(const glm::vec3 &from, const glm::vec3 &to, VNfloat t);
glm::vec4 lerp(const glm::vec4 &from, const glm::vec4 &to, VNfloat t);

bool isEqual(VNfloat a, VNfloat b, VNfloat delta);
bool isEqual(const glm::vec2 &a, const glm::vec2 &b, VNfloat delta);
bool isEqual(const glm::vec3 &a, const glm::vec3 &b, VNfloat delta);
bool isEqual(const glm::vec4 &a, const glm::vec4 &b, VNfloat delta);

}  // namespace Math

}  // namespace Vanadium

#endif  // VANADIUM_MATH_H
