#ifndef VANADIUM_APPLICATION_H
#define VANADIUM_APPLICATION_H

#include <glm/vec2.hpp>
#include <string>

#include "Window.h"
#include "StateStack.h"
#include "EventProvider.h"
#include "Timer.h"

namespace Van
{

class UserEndApplication
{
public:
    virtual double getDeltatime() const noexcept = 0;
    virtual double getFixedUpdateTime() const noexcept = 0;
    virtual UserEndEventProvider *getEventProvider() const noexcept = 0;
    virtual Window *getWindow() const noexcept = 0;
    virtual size_t getTicksSinceStart() const noexcept = 0;
    virtual size_t getFixedUpdateTicks() const noexcept = 0;

};

class Application: public UserEndApplication
{
private:
    Window *window;
    EventProvider *eventProvider;
    StateStack *stateStack;
    Timer *frameTime;

    size_t ticksSinceStart = 0;
    size_t fixedUpdateTicks = 0;
    double deltatime = 1.0;
    const double fixedUpdateTime = 0.5;
    double timeSinceLastFixedUpdate = 0.0;
    bool isRunning = false;

public:
    Application(const std::string &title, const glm::ivec2 &windowGeometry)
    {
        this->window = Window::create(title, windowGeometry);
        this->eventProvider = EventProvider::create(this->window);
        this->stateStack = new StateStack;
        this->frameTime = Timer::create();
    }
    ~Application()
    {
        delete this->eventProvider;
        delete this->window;
        delete this->stateStack;
        delete this->frameTime;
    }

    void run()
    {
        this->isRunning = true;
        while (this->isRunning)
        {

        }
    }

    double getDeltatime() const noexcept override
    {
        return this->deltatime;
    }
    double getFixedUpdateTime() const noexcept override
    {
        return this->fixedUpdateTime;
    }
    Window *getWindow() const noexcept override
    {
        return this->window;
    }
    size_t getTicksSinceStart() const noexcept override
    {
        return this->ticksSinceStart;
    }
    size_t getFixedUpdateTicks() const noexcept override
    {
        return this->fixedUpdateTicks;
    }
    UserEndEventProvider *getEventProvider() const noexcept override
    {
        return this->eventProvider;
    }
};

}
#endif //VANADIUM_APPLICATION_H
