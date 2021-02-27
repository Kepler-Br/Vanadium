#ifndef VANADIUM_HASHABLE_H
#define VANADIUM_HASHABLE_H

#include "../Types.h"

namespace Vanadium
{

class Hashable
{
public:
    virtual VNsize hashCode() const noexcept = 0;
};

}

#endif //VANADIUM_HASHABLE_H
