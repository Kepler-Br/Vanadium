#include "Application.h"

namespace Van
{

Application::Application(const std::string &title, uint32_t width, uint32_t height)
{
    this->window = Window::create(title, width, height);
    this->eventProvider = EventProvider::create(this->window);
    this->stateStack = new StateStack;
    this->frameTime = Timer::create();
}

Application::Application(const std::string &title, const glm::ivec2 &windowGeometry)
{
    this->window = Window::create(title, windowGeometry);
    this->eventProvider = EventProvider::create(this->window);
    this->stateStack = new StateStack;
    this->frameTime = Timer::create();
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

    this->isRunning = true;
    while (this->isRunning)
    {
        if (this->stateStack->size() == 0)
        {
            this->isRunning = false;
            break;
        }
        this->frameTime->start();
        this->deltatime = this->frameTime->get();
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
        this->frameTime->end();
        this->executeStateCommands();
    }
}

void Application::executeStateCommands()
{

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

size_t Application::getTicksSinceStart() const noexcept
{
    return this->ticksSinceStart;
}

size_t Application::getFixedUpdateTicks() const noexcept
{
    return this->fixedUpdateTicks;
}

UserEndEventProvider *Application::getEventProvider() const noexcept
{
    return this->eventProvider;
}

}