#include "TestState.h"

#include <vanadium/core/interfaces/constructed/factories/EventDispatcherFactory.h>
#include <vanadium/core/interfaces/constructed/factories/LoggerFactory.h>

void TestState::onAttach(vanadium::Application* application) {
  using namespace vanadium;

  this->_application = application;

  this->_factoryContainer = this->_application->getFactoryContainer();

  this->_eventDispatcher = this->_factoryContainer->construct<EventDispatcherFactory>();
  this->_logger = this->_factoryContainer->construct<LoggerFactory>("TestState");

  this->_logger->trace("onAttach");
}

void TestState::onDetach() {}
void TestState::onStateLostPriority() {}
void TestState::onStateGainedPriority() {}
void TestState::loadResources(const std::function<void()>& callback) {}
void TestState::loadResources() {}
void TestState::onTickStart() {}
void TestState::onTickEnd() {}
void TestState::update(float deltaTime) {}
void TestState::fixedUpdate(float deltaTime) {}
void TestState::preRender() {}
void TestState::render() {}
void TestState::postRender() {}

const std::string& TestState::getName() const noexcept { return this->_name; }

const vanadium::Ref<vanadium::EventDispatcher> TestState::getEventDispatcher()
    const noexcept {
  return this->_eventDispatcher;
}
