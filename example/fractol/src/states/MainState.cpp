#include "MainState.h"

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

void MainState::onMouseMove(vanadium::MouseMoveEvent *event) {}

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

MainState::MainState() {}

MainState::~MainState() {}

void MainState::onAttach(vanadium::UserEndApplication *application,
                         const std::string &name) {
  using namespace vanadium;

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
  this->shaderProgram =
      bgfx::createProgram(texturedQuadShader, mandelbulbShader, true);
  if (!bgfx::isValid(this->shaderProgram)) {
    throw ExecutionInterrupted("Critical shader program creation failed.");
  }

  this->screenPlane = MeshFactory::unitPlane(2.0f);
  if (!(*this->screenPlane)) {
    throw ExecutionInterrupted("Mesh somewhat came up not valid.");
  }

  this->uniformTime = bgfx::createUniform("u_time", bgfx::UniformType::Vec4, 1);
  this->uniformResolution =
      bgfx::createUniform("u_resolution", bgfx::UniformType::Vec4, 1);
  if (!bgfx::isValid(this->uniformTime) ||
      !bgfx::isValid(this->uniformResolution)) {
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
  bgfx::destroy(this->shaderProgram);
  bgfx::destroy(this->uniformTime);
  bgfx::destroy(this->uniformResolution);

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
    this->showDebugStats = !this->showDebugStats;
    bgfx::setDebug(this->showDebugStats ? BGFX_DEBUG_STATS : BGFX_DEBUG_NONE);
  }
}

void MainState::fixedUpdate(double deltatime) {}

void MainState::preRender() {}

void MainState::render() {
  const glm::vec4 programTime{
      (float)this->_application->getSecondsSinceStart()};
  const glm::vec4 resolution{(float)this->_window->getGeometry().x,
                             (float)this->_window->getGeometry().y, 0.0f, 0.0f};
  bgfx::touch(0);
  this->screenPlane->bind(0);
  //  bgfx::setState(BGFX_STATE_DEFAULT);
  bgfx::setUniform(this->uniformTime, glm::value_ptr(programTime), 1);
  bgfx::setUniform(this->uniformResolution, glm::value_ptr(resolution), 1);
  bgfx::submit(0, this->shaderProgram);

  ImGuiBgfxImpl::newFrame();
  ImGui_ImplSDL2_NewFrame(
      (SDL_Window *)this->_application->getWindow()->getRaw());

  ImGui::NewFrame();
  ImGui::ShowDemoWindow();  // your drawing here
  ImGui::Render();
  ImGuiBgfxImpl::renderDrawLists(ImGui::GetDrawData());

  bgfx::frame();
}
void MainState::postRender() {}

const std::string &MainState::getName() const noexcept { return this->_name; }
