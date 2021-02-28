#include "Application.h"
#include "Exceptions.h"
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

    if (this->initializationInterrupted)
    {
        VAN_ENGINE_INFO("Initialization was interrupted. Application::run execution stopped.");
        return;
    }
    while (true)
    {
        if (this->stateStack->size() == 0)
            break;
        this->deltatime = this->frameTime->stop();
        this->frameTime->start();
        topState = this->stateStack->top();
        // Should I use dispatch() or just integrate it in update()?
        this->eventProvider->dispatch();
        this->eventProvider->update();
        topState->onTickStart();
        topState->update(this->deltatime);
        while (this->timeSinceLastFixedUpdate > this->fixedUpdateTime)
        {
            topState->fixedUpdate(this->fixedUpdateTime);
            this->timeSinceLastFixedUpdate -= this->fixedUpdateTime;
            this->fixedUpdateTicks++;
        }
        topState->preRender();
        topState->render();
        topState->postRender();
        topState->onTickEnd();
        this->stateStack->executeCommands();
        this->window->swapBuffer();
        this->ticksSinceStart++;
        this->secondsSinceStart += this->deltatime;
    }
}

void Application::stop() noexcept
{
    this->stateStack->requestPopAll();
}

void Application::init()
{
    try
    {
        if (this->specs.winSpecs.width == 0 || this->specs.winSpecs.height == 0)
            throw InitializationInterrupted("Window geometry is invalid!");
        this->preInit();
        this->window = Window::create(specs.winSpecs);
        this->eventProvider = EventProviderFactory::create(this->window);
        this->frameTime = Stopwatch::create();
        this->stateStack = new StateStack(this);
        this->postInit();
    }
    catch (const InitializationInterrupted &e)
    {
        VAN_ENGINE_INFO("Initialization was interrupted with message: {}", e.what());
        this->initializationInterrupted = true;
    }
}

double Application::getDeltatime() const noexcept
{
    return this->deltatime;
}

double Application::getFixedUpdateTime() const noexcept
{
    return this->fixedUpdateTime;
}

double Application::getSecondsSinceStart() const noexcept
{
    return this->secondsSinceStart;
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