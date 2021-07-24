#include "Random.h"

#include <xoshiro-cpp/XoshiroCpp.hpp>

namespace vanadium {

Random* Random::_instance = nullptr;

Random::Random() {
  using namespace XoshiroCpp;

  const std::uint64_t seed = time(nullptr);

  Random::_generator = new Xoshiro256PlusPlus(seed);
}

Random* Random::getInstance() {
  if (_instance == nullptr) {
    Random::_instance = new Random();
  }

  return Random::_instance;
}

std::uint64_t Random::getRaw() { return (*this->_generator)(); }

uint Random::getUint() { return (uint)(*this->_generator)(); }

int Random::getInt() { return (int)(*this->_generator)(); }

float Random::uniform() {
  const std::uint64_t generated = (*this->_generator)();
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

}  // namespace vanadium
