#pragma once

#include <cstdint>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace vanadium {

class Random {
 public:
  virtual ~Random() = default;

  virtual void setSeed(uint64_t seed) = 0;

  virtual int getInt() = 0;
  virtual long getLong() = 0;
  virtual bool getBool() = 0;

  virtual float uniform() = 0;
  virtual glm::vec2 uniformVec2() = 0;
  virtual glm::vec3 uniformVec3() = 0;
  virtual glm::vec4 uniformVec4() = 0;

  virtual float range(float min, float max) = 0;
  virtual int range(int min, int max) = 0;
  virtual long range(long min, long max) = 0;
};

}  // namespace vanadium
