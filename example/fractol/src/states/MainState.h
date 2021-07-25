#pragma once

#include "Vanadium.h"

class MainState : public vanadium::State {
 private:
  bgfx::ProgramHandle shaderProgram{bgfx::kInvalidHandle};
  bgfx::UniformHandle uniformTime;
  bgfx::UniformHandle uniformResolution;
  vanadium::Ref<vanadium::Mesh> screenPlane;

  bool showDebugStats = false;

  void setupEvents();

  void onMouseMove(vanadium::MouseMoveEvent *event);
  void onWindowClose(vanadium::WindowCloseEvent *event);
  void onWindowResize(vanadium::WindowResizedEvent *event);
  void onKeyPressed(vanadium::KeyPressedEvent *event);

 public:
  MainState();
  ~MainState() override;

  void onAttach(vanadium::UserEndApplication *application,
                const std::string &name) override;
  void onDetach() override;
  void onStateLostPriority() override;
  void onStateGainedPriority() override;
  void loadResources(const std::function<void()> &callback) override;
  void loadResources() override;
  void onTickStart() override;
  void onTickEnd() override;
  void update(double deltatime) override;
  void fixedUpdate(double deltatime) override;
  void preRender() override;
  void render() override;
  void postRender() override;
  [[nodiscard]] const std::string &getName() const noexcept override;
};
