#include "State.h"

#include "Application.h"
#include "../event/EventDispatcher.h"

namespace Vanadium
{
void State::_onAttach(UserEndApplication *application, const std::string &name)
{
    this->application = application;
    this->eventProvider = application->getEventProvider();
    this->stateStack = application->getStateStack();
    this->window = application->getWindow();
    this->eventDispatcher = new EventDispatcher;
    this->name = name;
    this->eventProvider->setEventCallback(
            [this](Event *event) { this->eventDispatcher->dispatch(event); }
    );
    this->onAttach(application, name);
}

void State::_onDetach()
{
    this->onDetach();
}

void State::_onStateLostPriority()
{
    this->eventProvider->setEventCallback(nullptr);
    this->onStateLostPriority();
}

void State::_onStateGainedPriority()
{
    this->eventProvider->setEventCallback(
            [this](Event *event) { this->eventDispatcher->dispatch(event); }
    );
    this->onStateGainedPriority();
}

}


