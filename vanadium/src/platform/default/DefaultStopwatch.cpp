#include "DefaultStopwatch.h"

#include <SDL.h>

namespace Vanadium
{

void DefaultStopwatch::start() noexcept
{
    this->isRunning = true;
    this->startTime = SDL_GetTicks();
}

double DefaultStopwatch::end() noexcept
{
    if (this->isRunning)
    {
        this->isRunning = false;
        result = (double)(SDL_GetTicks() - this->startTime)/1000.0;
        return result;
    }
    else
        return 0.0;
}

double DefaultStopwatch::get() const noexcept
{
    return result;
}

}
