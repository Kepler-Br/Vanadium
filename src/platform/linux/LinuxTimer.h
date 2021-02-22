#ifndef VANADIUM_LINUXTIMER_H
#define VANADIUM_LINUXTIMER_H

#include <functional>

#include "../../core/Timer.h"

namespace Van
{

class LinuxTimer: public Timer
{
public:
    LinuxTimer(const std::function<void()> &callback, double seconds, bool repeating)
    {
        this->callback = callback;
        this->secondsLeft = seconds;
        this->repeating = repeating;
    }

    void start()
    {
        if (this->isRunning)
            return;
    }

    void stop()
    {
        if (!this->isRunning)
            return;
    }
};

}

#endif //VANADIUM_LINUXTIMER_H
