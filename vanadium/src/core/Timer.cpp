#include "Timer.h"
#include "Log.h"

#if defined(VANADIUM_PLATFORM_LINUX) | defined(VANADIUM_PLATFORM_MACOS)
    #include "../platform/default/DefaultTimer.h"
    using TimerImpl = Vanadium::DefaultTimer;
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

#warning "Timer is not using startImmediately."
Timer *Timer::create(const std::function<void()> &callback, double seconds, bool repeating, bool startImmediately)
{
    Timer *timer;

    VAN_ENGINE_TRACE("Creating Timer.");
    timer = new TimerImpl(callback, seconds, repeating);
    return timer;
}

}