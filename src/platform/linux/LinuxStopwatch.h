#ifndef VANADIUM_LINUXSTOPWATCH_H
#define VANADIUM_LINUXSTOPWATCH_H

#include "../../core/Stopwatch.h"

namespace Van
{

class LinuxStopwatch : public Stopwatch
{
private:
    uint32_t startTime = 0;
    double result = 0.0;

public:
    LinuxStopwatch() = default;

    void start() noexcept override;
    double end() noexcept override;
    double get() const noexcept override;
};

}

#endif //VANADIUM_LINUXSTOPWATCH_H
