#ifndef VANADIUM_RANDOM_H
#define VANADIUM_RANDOM_H

#include "Types.h"

namespace XoshiroCpp {
class Xoshiro256PlusPlus;
}

namespace Vanadium {
class Random {
 private:
  static Random *instance;
  XoshiroCpp::Xoshiro256PlusPlus *generator;

  Random();

 public:
  static Random *getInstance();

  std::uint64_t getRaw();
  VNuint getUint();
  VNint getInt();
  VNfloat uniform();
  VNfloat radian();
  VNfloat range(VNfloat min, VNfloat max);
};
}  // namespace Vanadium

#endif  // VANADIUM_RANDOM_H
