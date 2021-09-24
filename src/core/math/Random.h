#pragma once

#include <xoshiro-cpp/XoshiroCpp.hpp>

namespace vanadium {

class Random {
 private:
  XoshiroCpp::Xoshiro256PlusPlus _generator;

 public:
  Random();
  explicit Random(uint64_t seed);

  std::uint64_t getRaw();
  unsigned int getUint();
  int getInt();
  float uniform();
  float radian();
  float range(float min, float max);
};

}  // namespace vanadium
