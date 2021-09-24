#include "Random.h"

#include <ctime>

#include "core/math/Math.h"

namespace vanadium {

Random::Random() {
  using namespace XoshiroCpp;

  const std::uint64_t seed = std::time(nullptr);

  this->_generator = Xoshiro256PlusPlus(seed);
}

Random::Random(uint64_t seed)
    : _generator(XoshiroCpp::Xoshiro256PlusPlus(seed)) {}

std::uint64_t Random::getRaw() { return this->_generator(); }

unsigned int Random::getUint() { return (unsigned int)this->_generator(); }

int Random::getInt() { return (int)this->_generator(); }

float Random::uniform() {
  const std::uint64_t generated = this->_generator();
  return (float)XoshiroCpp::DoubleFromBits(generated);
}

float Random::radian() {
  constexpr float piTimesTwo = (float)M_PI * 2.0f;

  return this->range(0.0f, piTimesTwo);
}

float Random::range(float min, float max) {
  const float uniform = this->uniform();

  return uniform * (max - min) + min;
}

}  // namespace vanadium
