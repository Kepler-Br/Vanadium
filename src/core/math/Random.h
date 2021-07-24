#ifndef VANADIUM_RANDOM_H
#define VANADIUM_RANDOM_H

#include "core/Types.h"

namespace XoshiroCpp {
class Xoshiro256PlusPlus;
}

namespace vanadium {

class Random {
 private:
  static Random *instance;
  XoshiroCpp::Xoshiro256PlusPlus *generator;

  Random();

 public:
  static Random *getInstance();

  std::uint64_t getRaw();
  uint getUint();
  int getInt();
  float uniform();
  float radian();
  float range(float min, float max);
};

}  // namespace vanadium

#endif  // VANADIUM_RANDOM_H
