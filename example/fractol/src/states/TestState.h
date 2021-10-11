#pragma once

#include <vanadium/core/interfaces/Application.h>
#include <vanadium/core/interfaces/constructed/EventDispatcher.h>
#include <vanadium/core/interfaces/constructed/Logger.h>
#include <vanadium/core/interfaces/FactoryContainer.h>
#include <vanadium/core/interfaces/State.h>

#include <string>

class TestState : public vanadium::State {
 private:
  const std::string _name = "TestState";

  vanadium::Application *_application;
  vanadium::Ref<vanadium::EventDispatcher> _eventDispatcher;
  vanadium::Ref<vanadium::FactoryContainer> _factoryContainer;
  vanadium::Ref<vanadium::Logger> _logger;

 public:
  void onAttach(vanadium::Application *application) override;
  void onDetach() override;
  void onStateLostPriority() override;
  void onStateGainedPriority() override;
  void loadResources(const std::function<void()>& callback) override;
  void loadResources() override;
  void onTickStart() override;
  void onTickEnd() override;
  void update(float deltaTime) override;
  void fixedUpdate(float deltaTime) override;
  void preRender() override;
  void render() override;
  void postRender() override;
  [[nodiscard]] const std::string& getName() const noexcept override;
  [[nodiscard]] const vanadium::Ref<vanadium::EventDispatcher> getEventDispatcher()
      const noexcept override;
};
