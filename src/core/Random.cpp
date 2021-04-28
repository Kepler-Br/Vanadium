#include "vanadium/core/Random.h"

#include <xoshiro-cpp/XoshiroCpp.hpp>

#include "vanadium/core/Math.h"

namespace Vanadium {

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

VNuint Random::getUint() { return (VNuint)(*this->generator)(); }

VNint Random::getInt() { return (VNint)(*this->generator)(); }

VNfloat Random::uniform() {
  const std::uint64_t generated = (*this->generator)();
  return (VNfloat)XoshiroCpp::DoubleFromBits(generated);
}

VNfloat Random::radian() {
  constexpr VNfloat piTimesTwo = M_PI * 2.0f;

  return this->range(0.0f, piTimesTwo);
}

VNfloat Random::range(VNfloat min, VNfloat max) {
  const VNfloat uniform = this->uniform();

  return uniform * (max - min) + min;
}

}  // namespace Vanadium
