#include "DefaultRandomImpl.h"

#include <ctime>

namespace vanadium {

DefaultRandomImpl::DefaultRandomImpl() {
  using namespace XoshiroCpp;

  const std::uint64_t seed = std::time(nullptr);

  this->_generator = Xoshiro256PlusPlus(seed);
}

DefaultRandomImpl::DefaultRandomImpl(uint64_t seed)
    : _generator(XoshiroCpp::Xoshiro256PlusPlus(seed)) {}

void DefaultRandomImpl::setSeed(uint64_t seed) {
  this->_generator = XoshiroCpp::Xoshiro256PlusPlus(seed);
}

int DefaultRandomImpl::getInt() { return (int)this->_generator(); }

long DefaultRandomImpl::getLong() { return (long)this->_generator(); }

bool DefaultRandomImpl::getBool() { return this->_generator() & 0x1; }

float DefaultRandomImpl::uniform() {
  const std::uint64_t generated = this->_generator();

  return XoshiroCpp::FloatFromBits((uint32_t)generated);
}

glm::vec2 DefaultRandomImpl::uniformVec2() {
  using namespace XoshiroCpp;

  return {FloatFromBits((uint32_t)this->_generator()),   // x
          FloatFromBits((uint32_t)this->_generator())};  // y
}

glm::vec3 DefaultRandomImpl::uniformVec3() {
  using namespace XoshiroCpp;

  return {FloatFromBits((uint32_t)this->_generator()),   // x
          FloatFromBits((uint32_t)this->_generator()),   // y
          FloatFromBits((uint32_t)this->_generator())};  // z
}

glm::vec4 DefaultRandomImpl::uniformVec4() {
  using namespace XoshiroCpp;

  return {FloatFromBits((uint32_t)this->_generator()),   // x
          FloatFromBits((uint32_t)this->_generator()),   // y
          FloatFromBits((uint32_t)this->_generator()),   // y
          FloatFromBits((uint32_t)this->_generator())};  // w
}

float DefaultRandomImpl::range(float min, float max) {
  using namespace XoshiroCpp;

  const float uniform = FloatFromBits((uint32_t)this->_generator());

  return uniform * (max - min) + min;
}

int DefaultRandomImpl::range(int min, int max) {
  using namespace XoshiroCpp;

  const int value = (int)this->_generator();

  return min + value % ((max + 1) - min);
}

long DefaultRandomImpl::range(long min, long max) {
  using namespace XoshiroCpp;

  const long value = (long)this->_generator();

  return min + value % ((max + 1) - min);
}

}  // namespace vanadium
