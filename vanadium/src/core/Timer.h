#ifndef VANADIUM_TIMER_H
#define VANADIUM_TIMER_H

#include <functional>

namespace Vanadium
{

class Timer
{
protected:
    std::function<void()> callback;
    bool isRunning = false;
    bool repeating = false;
    double secondsLeft = 0.0;

public:
    virtual ~Timer() = default;

    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void setRepeating(bool repeating) noexcept;
    virtual void setCallback(const std::function<void()> &callback) noexcept;
    virtual void setTimer(double seconds) noexcept;

    static Timer *create(const std::function<void()> &callback,
                         double seconds, bool repeating = false, bool startImmediately = false);

};

}
#endif //VANADIUM_TIMER_H
