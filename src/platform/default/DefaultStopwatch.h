#ifndef VANADIUM_DEFAULTSTOPWATCH_H
#define VANADIUM_DEFAULTSTOPWATCH_H

#include "../../core/Stopwatch.h"
#include <cstdint>
#warning "DefaultStopwatch is not implemented."

namespace Vanadium
{

class DefaultStopwatch : public Stopwatch
{
private:
    uint32_t startTime = 0;
    double result = 0.0;

public:
    DefaultStopwatch() = default;

    void start() noexcept override;
    double end() noexcept override;
    double get() const noexcept override;
};

}

#endif //VANADIUM_DEFAULTSTOPWATCH_H
