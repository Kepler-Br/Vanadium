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

private:
    EventProvider *eventProvider;
    StateStack *stateStack;
    Stopwatch *frameTime;
    Window *window;

    std::vector<std::string> programArguments;

    VNsize ticksSinceStart = 0;
    VNsize fixedUpdateTicks = 0;
    double deltatime = 1.0;
    const double fixedUpdateTime = 0.5;
    double timeSinceLastFixedUpdate = 0.0;

public:
    Application(const Application::Specification &specs);
    ~Application();

    void run();
    void stop() noexcept override;

    double getDeltatime() const noexcept override;
    double getFixedUpdateTime() const noexcept override;
    VNsize getTicksSinceStart() const noexcept override;
    VNsize getFixedUpdateTicks() const noexcept override;
    Window *getWindow() const noexcept override;
    UserEndEventProvider *getEventProvider() const noexcept override;
    UserEndStateStack *getStateStack() const noexcept override;
    const std::vector<std::string> &getProgramArguments() const noexcept override;

    // Todo: Think about different name.
    template<class T>
    void forcePushArgumentlessState(const std::string &name)
    {
        this->stateStack->push(new T, name);
    }
    // Todo: Think about different name.
    void forcePushState(State *state, const std::string &name) noexcept;

};

}
#endif //VANADIUM_APPLICATION_H
