#include "Application.h"
#include "Log.h"

namespace Vanadium
{

Application::Application(const std::string &title, uint32_t width, uint32_t height)
{
    Log::init();

    this->window = WindowFactory::create(title, width, height);
    this->eventProvider = EventProviderFactory::create(this->window);
    this->frameTime = Stopwatch::create();
    this->stateStack = new StateStack(this);
}

Application::Application(const std::string &title, const glm::ivec2 &windowGeometry)
{
    this->window = WindowFactory::create(title, windowGeometry);
    this->eventProvider = EventProviderFactory::create(this->window);
    this->frameTime = Stopwatch::create();
    this->stateStack = new StateStack(this);
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
    State *state;

    while (true)
    {
        if (this->stateStack->size() == 0)
            break;
        this->deltatime = this->frameTime->get();
        this->frameTime->start();
        state = this->stateStack->top();
        this->eventProvider->update();
        state->onTickStart();
        state->update(this->deltatime);
        while (this->timeSinceLastFixedUpdate > this->fixedUpdateTime)
        {
            state->fixedUpdate(this->fixedUpdateTime);
            this->timeSinceLastFixedUpdate -= this->fixedUpdateTime;
        }
        state->preRender();
        state->render();
        state->postRender();
        state->onTickEnd();
        this->stateStack->executeCommands();
        this->frameTime->end();
    }
}


void Application::stop() noexcept
{
    this->stateStack->requestPopAll();
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

void Application::forcePushState(State *state, const std::string &name) noexcept
{
    this->stateStack->push(state, name);
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