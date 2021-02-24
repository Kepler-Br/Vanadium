#ifndef VANADIUM_DEFAULTTIMER_H
#define VANADIUM_DEFAULTTIMER_H

#include <functional>

#include "../../core/Timer.h"
#warning "DefaultStopwatch is not implemented."

namespace Vanadium
{

class DefaultTimer: public Timer
{
public:
    DefaultTimer(const std::function<void()> &callback, double seconds, bool repeating)
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
        this->isRunning = false;
    }
};

}

#endif //VANADIUM_DEFAULTTIMER_H
