#include "State.h"

#include "Application.h"
#include "event/EventDispatcher.h"

namespace vanadium {

void State::_onAttach(UserEndApplication *application,
                      const std::string &name) {
  this->_application = application;
  this->_eventProvider = application->getEventProvider();
  this->_stateStack = application->getStateStack();
  this->_window = application->getWindow();
  this->_eventDispatcher = MakeRef<EventDispatcher>();
  this->_name = name;
  this->_eventProvider->setEventCallback(
      [this](Event *event) { this->_eventDispatcher->dispatch(event); });
  this->onAttach(application, name);
}

void State::_onDetach() { this->onDetach(); }

void State::_onStateLostPriority() {
  this->_eventProvider->setEventCallback(nullptr);
  this->onStateLostPriority();
}

void State::_onStateGainedPriority() {
  this->_eventProvider->setEventCallback(
      [this](Event *event) { this->_eventDispatcher->dispatch(event); });
  this->onStateGainedPriority();
}

}  // namespace vanadium
