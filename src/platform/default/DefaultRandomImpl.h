#pragma once

#include <xoshiro-cpp/XoshiroCpp.hpp>

#include "core/interfaces/Random.h"

namespace vanadium {

class DefaultRandomImpl : public Random {
 private:
  XoshiroCpp::Xoshiro256PlusPlus _generator;

 public:
  DefaultRandomImpl();
  explicit DefaultRandomImpl(uint64_t seed);

  ~DefaultRandomImpl() override = default;

  void setSeed(uint64_t seed) override;

  int getInt() override;
  long getLong() override;
  bool getBool() override;

  float uniform() override;
  glm::vec2 uniformVec2() override;
  glm::vec3 uniformVec3() override;
  glm::vec4 uniformVec4() override;

  float range(float min, float max) override;
  int range(int min, int max) override;
  long range(long min, long max) override;
};

}  // namespace vanadium
