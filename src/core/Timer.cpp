#include "Timer.h"

#ifdef VANADIUM_PLATFORM_LINUX
    #include "../platform/default/DefaultTimer.h"
#endif
#ifdef VANADIUM_PLATFORM_WINDOWS
    #include "../platform/windows/WindowsTimer.h"
#endif
#ifdef VANADIUM_PLATFORM_MACOS
    #include "../platform/macos/MacOSTimer.h"
#endif

namespace Van
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

    #ifdef VANADIUM_PLATFORM_LINUX
        timer = new DefaultTimer(callback, seconds, repeating);
    #elif defined(VANADIUM_PLATFORM_WINDOWS)
        timer = new WindowsTimer(callback, seconds, repeating);
    #elif defined(VANADIUM_PLATFORM_MACOS)
        timer = new MacOSTimer(callback, seconds, repeating);
    #else
        #error "Not supported platform!"
    #endif
    return timer;
}

}