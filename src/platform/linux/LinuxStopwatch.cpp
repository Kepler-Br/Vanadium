#include "LinuxStopwatch.h"

#include <SDL2/SDL.h>

namespace Van
{

void LinuxStopwatch::start() noexcept
{
    this->isRunning = true;
    this->startTime = SDL_GetTicks();
}

double LinuxStopwatch::end() noexcept
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

double LinuxStopwatch::get() const noexcept
{
    return result;
}

}