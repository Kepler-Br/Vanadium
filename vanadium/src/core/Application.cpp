#include "Application.h"
#include "Exceptions.h"
#include "Dialogs.h"
#include "Log.h"

namespace Vanadium
{

void Application::tick()
{
    State *topState;

    this->deltatime = this->frameTime->stop();
    this->frameTime->start();
    topState = this->stateStack->top();
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

Application::Application(const Application::Specification &specs)
{
    Log::init();
    VAN_ENGINE_INFO("Initializing Application.");
    this->specs = specs;
    if (this->specs.argv != nullptr)
    {
        this->programArguments.reserve(specs.argc);
        for (int i = 0; i < specs.argc; i++)
        {
            this->programArguments.emplace_back(specs.argv[i]);
        }
    }
}

Application::~Application()
{
    VAN_ENGINE_INFO("Destroying Application.");
    delete this->eventProvider;
    delete this->window;
    delete this->stateStack;
    delete this->frameTime;
}

void Application::run()
{
    if (this->initializationInterrupted)
    {
        VAN_ENGINE_INFO("Initialization was interrupted. Application::run execution stopped.");
        return;
    }
    while (true)
    {
        if (this->stateStack->size() == 0)
            break;
        try
        {
            this->tick();
        }
        catch (const std::runtime_error &e)
        {
            VAN_ENGINE_CRITICAL("Execution interrupted with message: {}", e.what());
            bool result = Dialogs::show("In state error", std::string("Execution interrupted with message: ") + e.what(), Dialogs::Type::Error);
            if (!result)
                VAN_ENGINE_ERROR("Dialog show error: {}", SDL_GetError());
            this->stateStack->popAll();
        }
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
        bool result = Dialogs::show("In state error", std::string("Execution interrupted with message: ") + e.what(), Dialogs::Type::Error);
        if (!result)
            VAN_ENGINE_ERROR("Dialog show error: {}", SDL_GetError());
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