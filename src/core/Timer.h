#ifndef VANADIUM_TIMER_H
#define VANADIUM_TIMER_H

namespace Van
{

class Timer
{
public:
    virtual ~Timer() = default;

    virtual void start() noexcept = 0;
    virtual void end() noexcept = 0;
    virtual uint32_t get() noexcept = 0;

    static Timer *create();
};

}

#endif //VANADIUM_TIMER_H
