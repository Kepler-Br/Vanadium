#include "MainState.h"

#include <glm/gtc/type_ptr.hpp>

#include "../imgui/ImGuiBgfxImpl.h"
#include "backends/imgui_impl_sdl.h"

void MainState::setupEvents() {
  using namespace vanadium;

  this->_eventDispatcher->subscribe(
      Event::Type::MouseMove,
      [this](Event *event) { this->onMouseMove((MouseMoveEvent *)event); });
  this->_eventDispatcher->subscribe(
      Event::Type::WindowClose,
      [this](Event *event) { this->onWindowClose((WindowCloseEvent *)event); });
  this->_eventDispatcher->subscribe(
      Event::Type::KeyPressed,
      [this](Event *event) { this->onKeyPressed((KeyPressedEvent *)event); });
  this->_eventDispatcher->subscribe(
      Event::Type::WindowResized, [this](Event *event) {
        this->onWindowResize((WindowResizedEvent *)event);
      });
}

void MainState::onMouseMove(vanadium::MouseMoveEvent *event) {
  bool lmbPressed = this->_application->getEventProvider()->isMousePressed(
      vanadium::mouse::KeyCode::Left);

  if (lmbPressed && !ImGui::GetIO().WantCaptureMouse) {
    glm::vec2 delta = event->getDelta();

    glm::vec2 &angles = this->_model->getCameraAngleRef();
    const float radius = 1.0f;

    delta /= 100.0f;

    angles.x += delta.y;
    angles.y -= delta.x;
  }
}

void MainState::onWindowClose(vanadium::WindowCloseEvent *event) {
  this->_stateStack->requestPopAll();
}

void MainState::onWindowResize(vanadium::WindowResizedEvent *event) {
  bgfx::setViewRect(0, 0, 0, (uint16_t)event->getWidth(),
                    (uint16_t)event->getHeight());
  bgfx::reset((uint16_t)event->getWidth(), (uint16_t)event->getHeight());
}

void MainState::onKeyPressed(vanadium::KeyPressedEvent *event) {
  if (event->getKeyCode() == vanadium::keyboard::KeyCode::Escape) {
    this->_stateStack->requestPopAll();
  }
}

MainState::MainState() {
  this->_camera.lookAt(glm::vec3(10.0f), glm::vec3(0.0f),
                       glm::vec3(0.0f, 0.0f, 1.0f));
  this->_camera.setOrthographic(-400.0f, 400.0f, -300.0f, 300.0f, 100.0f,
                                301.0f);
}

MainState::~MainState() {}

void MainState::onAttach(vanadium::WeakRef<vanadium::Application> applicationWeak) {
  using namespace vanadium;

  this->_application = applicationWeak.lock();

  this->_model = MakeRef<Model>();
  this->_controller =
      MakeRef<Controller>(this->_model, this->_application->getEventProvider());
  this->_view = MakeRef<View>(this->_model);

  this->setupEvents();

  std::string vertexShaderPath =
      "resources/shaders/compiled/{}/vs_texturedQuad.bin";
  std::string fragmentShaderPath =
      "resources/shaders/compiled/{}/fs_mandelbulb.bin";

  std::string renderingBackendName;
  switch (auto type = bgfx::getRendererType()) {
    case bgfx::RendererType::OpenGLES:
      renderingBackendName = "essl";
      break;
    case bgfx::RendererType::OpenGL:
      renderingBackendName = "glsl";
      break;
    case bgfx::RendererType::Vulkan:
      renderingBackendName = "spirv";
      break;
    default:
      throw ExecutionInterrupted(fmt::format(
          "Not supported rendering type: {}.", bgfx::getRendererName(type)));
  }

  bgfx::ShaderHandle texturedQuadShader = ShaderFactory::loadShader(
      fmt::format(vertexShaderPath, renderingBackendName), "texturedQuad");
  bgfx::ShaderHandle mandelbulbShader = ShaderFactory::loadShader(
      fmt::format(fragmentShaderPath, renderingBackendName), "mandelbulb");

  if (!bgfx::isValid(texturedQuadShader) || !bgfx::isValid(mandelbulbShader)) {
    throw ExecutionInterrupted("Cannot load critical shaders.");
  }
  this->_shaderProgram =
      bgfx::createProgram(texturedQuadShader, mandelbulbShader, true);
  if (!bgfx::isValid(this->_shaderProgram)) {
    throw ExecutionInterrupted("Critical shader program creation failed.");
  }

  this->_screenPlane = MeshFactory::unitPlane(2.0f);
  if (!(*this->_screenPlane)) {
    throw ExecutionInterrupted("Mesh somewhat came up not valid.");
  }

  this->_uniformResolution =
      bgfx::createUniform("u_resolution", bgfx::UniformType::Vec4, 1);
  this->_uniformAuraColor =
      bgfx::createUniform("u_auraColor", bgfx::UniformType::Vec4, 1);
  this->_uniformCameraPosition =
      bgfx::createUniform("u_cameraPosition", bgfx::UniformType::Vec4, 1);
  this->_uniformFractalParameter =
      bgfx::createUniform("u_fractalParameter", bgfx::UniformType::Vec4, 1);
  this->_uniformInversedProjectionView = bgfx::createUniform(
      "u_inversedProjectionView", bgfx::UniformType::Mat4, 1);
  this->_uniformBailout = bgfx::createUniform(
      "u_bailout", bgfx::UniformType::Vec4, 1);
  this->_uniformIterations = bgfx::createUniform(
      "u_iterations", bgfx::UniformType::Vec4, 1);

  if (!bgfx::isValid(this->_uniformResolution) ||
      !bgfx::isValid(this->_uniformCameraPosition) ||
      !bgfx::isValid(this->_uniformFractalParameter) ||
      !bgfx::isValid(this->_uniformInversedProjectionView)) {
    throw ExecutionInterrupted("Uniform handle came up not valid.");
  }

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  io.IniFilename = nullptr;
  io.WantCaptureKeyboard = true;
  io.WantTextInput = true;

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  ImGuiBgfxImpl::init(255);
  //  ImGui_ImplSDL2_InitForOpenGL(
  //      (SDL_Window *)this->_application->getWindow()->getRaw(), nullptr);
  ImGui_ImplSDL2_InitForVulkan(
      (SDL_Window *)this->_application->getWindow()->getRaw());
}

void MainState::onDetach() {
  bgfx::destroy(this->_shaderProgram);

  bgfx::destroy(this->_uniformResolution);
  bgfx::destroy(this->_uniformCameraPosition);
  bgfx::destroy(this->_uniformFractalParameter);
  bgfx::destroy(this->_uniformInversedProjectionView);
  bgfx::destroy(this->_uniformAuraColor);
  bgfx::destroy(this->_uniformBailout);
  bgfx::destroy(this->_uniformIterations);

  ImGui_ImplSDL2_Shutdown();
  ImGuiBgfxImpl::shutdown();
  ImGui::DestroyContext();
}

void MainState::onStateLostPriority() {}

void MainState::onStateGainedPriority() { this->setupEvents(); }

void MainState::loadResources(const std::function<void()> &callback) {}

void MainState::loadResources() {}

void MainState::onTickStart() {}

void MainState::onTickEnd() {}

void MainState::update(double deltatime) {
  if (this->_eventProvider->isKeyJustPressed(vanadium::keyboard::KeyCode::F1)) {
    this->_showDebugStats = !this->_showDebugStats;
    bgfx::setDebug(this->_showDebugStats ? BGFX_DEBUG_STATS : BGFX_DEBUG_NONE);
  }

  this->_controller->update(deltatime);

  glm::vec3 pos = vanadium::math::sphericalToRectangular(
      this->_model->getLerpedCameraAngle(), this->_model->getLerpedRadius());
  this->_camera.setPosition(pos);
}

void MainState::fixedUpdate(double deltatime) {}

void MainState::preRender() {}

void MainState::render() {
  //  vanadium::Random random(this->_application->getTicksSinceStart());
  //  this->_camera.setPosition(glm::vec3{random.uniform(), random.uniform(),
  //  random.uniform()}*1.0f+0.4f);
  //  this->_camera.setCenter(glm::vec3{random.uniform(), random.uniform(),
  //  random.uniform()}*20.0f);

  bgfx::touch(0);
  this->_screenPlane->bind(0);

  //  bgfx::setState(BGFX_STATE_DEFAULT);
  const glm::vec4 resolution{(float)this->_window->getGeometry().x,
                             (float)this->_window->getGeometry().y, 0.0f, 0.0f};
  const glm::vec4 fractalParameter{1.0f};
  const glm::vec4 iterations{this->_model->getLerpedIterations()};
  const glm::vec4 bailout{this->_model->getLerpedBailout()};
  const glm::vec4 cameraPosition{this->_camera.getPosition().x,
                                 this->_camera.getPosition().y,
                                 this->_camera.getPosition().z, 1.0f};
  const glm::mat4 inversedPV =
      glm::inverse(this->_camera.getProjection() * this->_camera.getView());

  bgfx::setUniform(this->_uniformResolution, glm::value_ptr(resolution), 1);
  bgfx::setUniform(this->_uniformAuraColor,
                   glm::value_ptr(this->_model->getLerpedAuraColor()), 1);
  bgfx::setUniform(this->_uniformFractalParameter,
                   glm::value_ptr(fractalParameter), 1);
  bgfx::setUniform(this->_uniformInversedProjectionView,
                   glm::value_ptr(inversedPV), 1);
  bgfx::setUniform(this->_uniformCameraPosition, glm::value_ptr(cameraPosition),
                   1);
  bgfx::setUniform(this->_uniformIterations, glm::value_ptr(iterations),
                   1);
  bgfx::setUniform(this->_uniformBailout, glm::value_ptr(bailout),
                   1);

  bgfx::submit(0, this->_shaderProgram);

  ImGuiBgfxImpl::newFrame();
  ImGui_ImplSDL2_NewFrame(
      (SDL_Window *)this->_application->getWindow()->getRaw());

  ImGui::NewFrame();
  this->_view->draw();
  ImGui::Render();
  ImGuiBgfxImpl::renderDrawLists(ImGui::GetDrawData());

  bgfx::frame();
}
void MainState::postRender() {}

const std::string &MainState::getName() const noexcept { return this->_name; }
