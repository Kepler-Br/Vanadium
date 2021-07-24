#ifndef VANADIUM_MATH_H
#define VANADIUM_MATH_H

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "core/Types.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace vanadium::math {

float lerpDelta(float from, float to, float t, float delta);
glm::vec2 lerpDelta(const glm::vec2 &from, const glm::vec2 &to, float t,
                    float delta);
glm::vec3 lerpDelta(const glm::vec3 &from, const glm::vec3 &to, float t,
                    float delta);
glm::vec4 lerpDelta(const glm::vec4 &from, const glm::vec4 &to, float t,
                    float delta);

float lerp(float from, float to, float t);
glm::vec2 lerp(const glm::vec2 &from, const glm::vec2 &to, float t);
glm::vec3 lerp(const glm::vec3 &from, const glm::vec3 &to, float t);
glm::vec4 lerp(const glm::vec4 &from, const glm::vec4 &to, float t);

bool isEqual(float a, float b, float delta);
bool isEqual(const glm::vec2 &a, const glm::vec2 &b, float delta);
bool isEqual(const glm::vec3 &a, const glm::vec3 &b, float delta);
bool isEqual(const glm::vec4 &a, const glm::vec4 &b, float delta);

}  // namespace vanadium::math

#endif  // VANADIUM_MATH_H
