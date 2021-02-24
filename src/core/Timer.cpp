#include "Timer.h"
#include "Log.h"

#ifdef VANADIUM_PLATFORM_LINUX
    #include "../platform/default/DefaultTimer.h"
#else
    #error "Not supported platform!"
#endif

namespace Vanadium
{

void Timer::setRepeating(bool repeating) noexcept
{
    this->repeating = repeating;
}

void Timer::setCallback(const std::function<void()> &callback) noexcept
{
    if (isRunning)
        return;
    this->callback = callback;
}

void Timer::setTimer(double seconds) noexcept
{
    if (isRunning)
        return;
    this->secondsLeft = seconds;
}

Timer *Timer::create(const std::function<void()> &callback, double seconds, bool repeating, bool startImmediately)
{
    Timer *timer;

    VAN_ENGINE_TRACE("Creating Timer.");
    #ifdef VANADIUM_PLATFORM_LINUX
        timer = new DefaultTimer(callback, seconds, repeating);
    #else
        #error "Not supported platform!"
    #endif
    return timer;
}

}