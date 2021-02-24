#include "CustomState.h"

void CustomState::onAttach(UserEndApplication *application, const std::string &name)
{
    this->application = application;
    this->eventProvider = application->getEventProvider();
    this->stateStack = application->getStateStack();
    this->name = name;
}

void CustomState::onDetach()
{

}

void CustomState::loadResources(const std::function<void()> &callback)
{

}

void CustomState::loadResources()
{

}

void CustomState::onTickStart()
{

}

void CustomState::onTickEnd()
{

}

void CustomState::update(double deltatime)
{

}

void CustomState::fixedUpdate(double deltatime)
{

}

void CustomState::preRender()
{

}

void CustomState::render()
{

}

void CustomState::postRender()
{

}

const std::string &CustomState::getName() const noexcept
{
    return this->name;
}

Ref<Framebuffer> CustomState::getTargetFramebuffer() const noexcept
{
    return nullptr;
}
