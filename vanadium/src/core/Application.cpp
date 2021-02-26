#include "Application.h"
#include "Log.h"

namespace Vanadium
{

Application::Application(const Application::Specification &specs)
{
    Log::init();
    this->specs = specs;
    this->programArguments.reserve(specs.argc);
    for (int i = 0; i < specs.argc; i++)
    {
        this->programArguments.emplace_back(specs.argv[i]);
    }
}

Application::~Application()
{
    delete this->eventProvider;
    delete this->window;
    delete this->stateStack;
    delete this->frameTime;
}

void Application::run()
{
    State *topState;

    while (true)
    {
        if (this->stateStack->size() == 0)
            break;
        this->deltatime = this->frameTime->get();
        this->frameTime->start();
        topState = this->stateStack->top();
        this->eventProvider->update();
        topState->onTickStart();
        topState->update(this->deltatime);
        while (this->timeSinceLastFixedUpdate > this->fixedUpdateTime)
        {
            topState->fixedUpdate(this->fixedUpdateTime);
            this->timeSinceLastFixedUpdate -= this->fixedUpdateTime;
        }
        topState->preRender();
        topState->render();
        topState->postRender();
        topState->onTickEnd();
        this->stateStack->executeCommands();
        this->frameTime->end();
    }
}

void Application::stop() noexcept
{
    this->stateStack->requestPopAll();
}

void Application::init()
{
    this->preInit();
    this->window = WindowFactory::create(specs.winSpecs);
    this->eventProvider = EventProviderFactory::create(this->window);
    this->frameTime = Stopwatch::create();
    this->stateStack = new StateStack(this);
    this->postInit();
}

double Application::getDeltatime() const noexcept
{
    return this->deltatime;
}

double Application::getFixedUpdateTime() const noexcept
{
    return this->fixedUpdateTime;
}

Window *Application::getWindow() const noexcept
{
    return this->window;
}

VNsize Application::getTicksSinceStart() const noexcept
{
    return this->ticksSinceStart;
}

VNsize Application::getFixedUpdateTicks() const noexcept
{
    return this->fixedUpdateTicks;
}

const std::vector<std::string> &Application::getProgramArguments() const noexcept
{
    return this->programArguments;
}

UserEndEventProvider *Application::getEventProvider() const noexcept
{
    return this->eventProvider;
}

UserEndStateStack *Application::getStateStack() const noexcept
{
    return this->stateStack;
}

}