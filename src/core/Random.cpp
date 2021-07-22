#include "core/Random.h"

#include <xoshiro-cpp/XoshiroCpp.hpp>

namespace vanadium {

Random* Random::instance = nullptr;

Random::Random() {
  using namespace XoshiroCpp;

  const std::uint64_t seed = time(nullptr);

  Random::generator = new Xoshiro256PlusPlus(seed);
}

Random* Random::getInstance() {
  if (instance == nullptr) {
    Random::instance = new Random();
  }

  return Random::instance;
}

std::uint64_t Random::getRaw() { return (*this->generator)(); }

uint Random::getUint() { return (uint)(*this->generator)(); }

int Random::getInt() { return (int)(*this->generator)(); }

float Random::uniform() {
  const std::uint64_t generated = (*this->generator)();
  return (float)XoshiroCpp::DoubleFromBits(generated);
}

float Random::radian() {
  constexpr float piTimesTwo = M_PI * 2.0f;

  return this->range(0.0f, piTimesTwo);
}

float Random::range(float min, float max) {
  const float uniform = this->uniform();

  return uniform * (max - min) + min;
}

}  // namespace Vanadium
