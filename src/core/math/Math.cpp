#include "Math.h"

namespace vanadium::math {

float lerpDelta(float from, float to, float t, float delta) {
  if (!isEqual(from, to, delta)) {
    return lerp(from, to, t);
  }
  return from;
}

glm::vec2 lerpDelta(const glm::vec2 &from, const glm::vec2 &to, float t,
                    float delta) {
  if (!isEqual(from, to, delta)) {
    return lerp(from, to, t);
  }
  return from;
}

glm::vec3 lerpDelta(const glm::vec3 &from, const glm::vec3 &to, float t,
                    float delta) {
  if (!isEqual(from, to, delta)) {
    return lerp(from, to, t);
  }
  return from;
}

glm::vec4 lerpDelta(const glm::vec4 &from, const glm::vec4 &to, float t,
                    float delta) {
  if (!isEqual(from, to, delta)) {
    return lerp(from, to, t);
  }
  return from;
}

float lerp(float from, float to, float t) { return from - ((from - to) * t); }

glm::vec2 lerp(const glm::vec2 &from, const glm::vec2 &to, float t) {
  return {
      from.x - ((from.x - to.x) * t),
      from.y - ((from.y - to.y) * t),
  };
}

glm::vec3 lerp(const glm::vec3 &from, const glm::vec3 &to, float t) {
  return {
      from.x - ((from.x - to.x) * t),
      from.y - ((from.y - to.y) * t),
      from.z - ((from.z - to.z) * t),
  };
}

glm::vec4 lerp(const glm::vec4 &from, const glm::vec4 &to, float t) {
  return {
      from.x - ((from.x - to.x) * t),
      from.y - ((from.y - to.y) * t),
      from.z - ((from.z - to.z) * t),
      from.w - ((from.w - to.w) * t),
  };
}

bool isEqual(float a, float b, float delta) {
  float currentDelta = glm::abs(glm::abs(a) - glm::abs(b));
  if (glm::abs(currentDelta) > delta) {
    return false;
  }
  return true;
}

bool isEqual(const glm::vec2 &a, const glm::vec2 &b, float delta) {
  if (isEqual(a.x, b.x, delta) && isEqual(a.y, b.y, delta)) {
    return true;
  }
  return false;
}

bool isEqual(const glm::vec3 &a, const glm::vec3 &b, float delta) {
  if (isEqual(a.x, b.x, delta) && isEqual(a.y, b.y, delta) &&
      isEqual(a.z, b.z, delta)) {
    return true;
  }
  return false;
}

bool isEqual(const glm::vec4 &a, const glm::vec4 &b, float delta) {
  if (isEqual(a.x, b.x, delta) && isEqual(a.y, b.y, delta) &&
      isEqual(a.z, b.z, delta) && isEqual(a.w, b.w, delta)) {
    return true;
  }
  return false;
}

}  // namespace vanadium::math
