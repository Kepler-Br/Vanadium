#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

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

void lerpRef(float &from, float to, float t);
void lerpRef(glm::vec2 &from, const glm::vec2 &to, float t);
void lerpRef(glm::vec3 &from, const glm::vec3 &to, float t);
void lerpRef(glm::vec4 &from, const glm::vec4 &to, float t);

bool isEqual(float a, float b, float delta);
bool isEqual(const glm::vec2 &a, const glm::vec2 &b, float delta);
bool isEqual(const glm::vec3 &a, const glm::vec3 &b, float delta);
bool isEqual(const glm::vec4 &a, const glm::vec4 &b, float delta);

glm::vec3 sphericalToRectangular(const glm::vec2 &angles);
glm::vec3 sphericalToRectangular(const glm::vec2 &angles, float radius);
glm::vec2 rectangularToSpherical(const glm::vec3 &a);

}  // namespace vanadium::math
