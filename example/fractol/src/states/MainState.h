#pragma once

#include <bgfx/bgfx.h>
#include <vanadium/core/interfaces/State.h>
#include <vanadium/scene/Mesh.h>
#include <vanadium/scene/PositionCamera.h>
#include <vanadium/event/MouseEvent.h>
#include <vanadium/event/WindowEvent.h>
#include <vanadium/event/KeyEvent.h>

#include "gui/Controller.h"
#include "gui/Model.h"
#include "gui/View.h"

class MainState : public vanadium::State {
 private:
  vanadium::PositionCamera _camera;
  vanadium::Ref<vanadium::Mesh> _screenPlane;

  bgfx::ProgramHandle _shaderProgram{bgfx::kInvalidHandle};

  bgfx::UniformHandle _uniformResolution{bgfx::kInvalidHandle};
  bgfx::UniformHandle _uniformAuraColor{bgfx::kInvalidHandle};
  bgfx::UniformHandle _uniformFractalParameter{bgfx::kInvalidHandle};
  bgfx::UniformHandle _uniformInversedProjectionView{bgfx::kInvalidHandle};
  bgfx::UniformHandle _uniformCameraPosition{bgfx::kInvalidHandle};
  bgfx::UniformHandle _uniformIterations{bgfx::kInvalidHandle};
  bgfx::UniformHandle _uniformBailout{bgfx::kInvalidHandle};

  vanadium::Ref<Model> _model;
  vanadium::Ref<Controller> _controller;
  vanadium::Ref<View> _view;
  vanadium::Ref<vanadium::Application> _application;

  bool _showDebugStats = false;

  void setupEvents();

  void onMouseMove(vanadium::MouseMoveEvent *event);
  void onWindowClose(vanadium::WindowCloseEvent *event);
  void onWindowResize(vanadium::WindowResizedEvent *event);
  void onKeyPressed(vanadium::KeyPressedEvent *event);

 public:
  MainState();
  ~MainState() override;

  void onAttach(vanadium::WeakRef<vanadium::Application> applicationWeak) override;
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
