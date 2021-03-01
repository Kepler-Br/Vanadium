#ifndef VANADIUM_APPLICATION_H
#define VANADIUM_APPLICATION_H

#include <glm/vec2.hpp>

#include <string>

#include "EventProvider.h"
#include "StateStack.h"
#include "Stopwatch.h"
#include "Window.h"
#include "Types.h"

namespace Vanadium
{

class UserEndApplication
{
public:
    virtual double getDeltatime() const noexcept = 0;
    virtual double getFixedUpdateTime() const noexcept = 0;
    virtual double getSecondsSinceStart() const noexcept = 0;
    virtual UserEndEventProvider *getEventProvider() const noexcept = 0;
    virtual Window *getWindow() const noexcept = 0;
    virtual VNsize getTicksSinceStart() const noexcept = 0;
    virtual VNsize getFixedUpdateTicks() const noexcept = 0;
    virtual UserEndStateStack *getStateStack() const noexcept = 0;
    virtual void stop() noexcept = 0;
    virtual const std::vector<std::string> &getProgramArguments() const noexcept = 0;

};

class Application: public UserEndApplication
{
public:
    struct Specification
    {
        Window::Specification winSpecs;
        int argc = 0;
        char **argv = nullptr;
    };

protected:
    EventProvider *eventProvider;
    StateStack *stateStack;
    Stopwatch *frameTime;
    Window *window;

    std::vector<std::string> programArguments;

    VNsize ticksSinceStart = 0;
    VNsize fixedUpdateTicks = 0;
    double deltatime = 1.0;
    const double fixedUpdateTime = 0.1;
    double timeSinceLastFixedUpdate = 0.0;
    double secondsSinceStart = 0.0;
    bool initializationInterrupted = false;
    Application::Specification specs;

    virtual void tick();
public:
    Application(const Application::Specification &specs);
    virtual ~Application();

    void run();
    void stop() noexcept override;
    void init();

    double getDeltatime() const noexcept override;
    double getFixedUpdateTime() const noexcept override;
    double getSecondsSinceStart() const noexcept override;
    VNsize getTicksSinceStart() const noexcept override;
    VNsize getFixedUpdateTicks() const noexcept override;
    Window *getWindow() const noexcept override;
    UserEndEventProvider *getEventProvider() const noexcept override;
    UserEndStateStack *getStateStack() const noexcept override;
    const std::vector<std::string> &getProgramArguments() const noexcept override;
    virtual void preInit()
    {}
    virtual void postInit()
    {}

    template<class T, typename... Args>
    void pushState(const std::string &name, Args&&... _args)
    {
        this->stateStack->push(new T(std::forward<Args>(_args)...), name);
    }
};

}
#endif //VANADIUM_APPLICATION_H
