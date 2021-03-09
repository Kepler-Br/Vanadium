#include "CustomState.h"
#define EVENT_SUBSCRIBE(memberFunction, eventType) [this](Event *event){ memberFunction((eventType *)event); }
// Todo: remove this:
#include "../../vanadium/src/platform/opengl/OpenGLFramebuffer.h"
#include "../../vanadium/src/platform/default/DefaultWindow.h"

#include <imgui.h>
#include "imgui_opengl3.h"
#include "imgui_sdl.h"

void CustomState::setUpEvents() noexcept
{
    this->eventDispatcher->subscribe(
            Event::Type::KeyPressed,
            EVENT_SUBSCRIBE(this->onKeyPressed, KeyPressedEvent)
    );
    this->eventDispatcher->subscribe(
            Event::Type::KeyReleased,
            [this](Event *event){ this->onKeyReleased((KeyReleasedEvent *)event); }
    );
    this->eventDispatcher->subscribe(
            Event::Type::WindowClose,
            [this](Event *event){ this->onWindowClose((WindowCloseEvent *)event); }
    );
    this->eventDispatcher->subscribe(
            Event::Type::MouseMove,
            [this](Event *event){ this->onMouseMove((MouseMoveEvent *)event); }
    );
    this->eventDispatcher->subscribe(
            Event::Type::WindowSizeChanged,
            [this](Event *event){ this->onWindowResized((WindowSizeChangedEvent *)event); }
    );
    this->eventDispatcher->subscribe(
            Event::Type::MouseScroll,
            [this](Event *event){ this->onMouseScroll((MouseScrollEvent *)event); }
    );
}

void CustomState::onKeyPressed(KeyPressedEvent *event) noexcept
{
//    VAN_USER_INFO("Key pressed: {}", event->toString());
}

void CustomState::onKeyReleased(KeyReleasedEvent *event) noexcept
{
//    VAN_USER_INFO("Key released: {}", event->toString());
}

void CustomState::onWindowClose(WindowCloseEvent *event) noexcept
{
    VAN_USER_INFO(event->toString());
    this->stateStack->requestPopAll();
}

void CustomState::onWindowResized(WindowSizeChangedEvent *event) noexcept
{
    RenderApi::instance()->setViewport(0, 0, event->getWidth(), event->getHeight());
    this->window->setGeometry({event->getWidth(), event->getHeight()});
    this->camera->setPerspective(glm::radians(75.0f), this->window->getAspect(), 0.001f, 10.0f);
    this->framebuffer->resize(event->getWidth(), event->getHeight());
}

void CustomState::onMouseMove(MouseMoveEvent *event) noexcept
{
//    VAN_USER_INFO(event->toString());
    if (this->window->isCursorGrabbed())
    {
        glm::mat4 view = this->camera->getView();
        glm::vec2 delta = event->getDelta();
        view = glm::rotate(view, delta.x * (VNfloat) this->application->getDeltatime(), this->camera->getUp());
        view = glm::rotate(view, delta.y * (VNfloat) this->application->getDeltatime(), this->camera->getRight());

        this->camera->setView(view);
    }
}

void CustomState::onMouseScroll(MouseScrollEvent *event) noexcept
{
//    VAN_USER_INFO(event->toString());
}

void CustomState::onAttach(UserEndApplication *application, const std::string &name)
{
    // Todo: think about event setup boilerplate.
    this->setUpEvents();

    this->mesh = MeshFactory::unitCube();
    this->camera = MakeRef<Camera>();

    auto from = glm::vec3(1.0f);
    auto to = glm::vec3(1.0f-0.1f);
    this->camera->lookAt(from, to, glm::vec3(0.0f, 1.0f, 0.0f));
    this->camera->setPerspective(glm::radians(75.0f), this->window->getAspect(), 0.001f, 50.0f);
//    this->window->grabCursor(true);
    this->framebuffer = FramebufferFactory::create({this->window->getWidth(), this->window->getHeight(),
                                                    Framebuffer::AttachmentSpecification({Framebuffer::TextureFormat::Depth,
                                                                                                         Framebuffer::TextureFormat::RGBA8,
                                                            }), 1, Texture::Filtering::Linear}
                                                           );

    this->screenPlane = MeshFactory::unitPlane(2.0f);
    if (!this->framebuffer || !*this->framebuffer)
    {
        std::stringstream msg;
        throw ExecutionInterrupted(
                dynamic_cast<std::stringstream&>
                (msg << "Framebuffer error.").str()
        );
    }
    this->shader = ShaderFactory::create("shaders/plain.xml", "Plain");
    if (!this->shader || !*this->shader)
    {
        std::stringstream msg;
        throw ExecutionInterrupted(
                dynamic_cast<std::stringstream&>
                (msg << "Shader not loaded: " << "shaders/shader.xml").str()
                );
    }
//    this->framebufferShader = ShaderFactory::create("shaders/framebufferblur.xml", "FramebufferShader");
//    if (!this->framebufferShader || !*this->framebufferShader)
//    {
//        std::stringstream msg;
//        throw ExecutionInterrupted(
//                dynamic_cast<std::stringstream&>
//                (msg << "Shader not loaded: " << "shaders/framebuffer.xml").str()
//        );
//    }
    this->texture = TextureFactory::create("textures/tex.png");
    if (!this->texture || !*this->texture)
    {
        std::stringstream msg;
        throw ExecutionInterrupted(
                dynamic_cast<std::stringstream&>
                (msg << "Texture not loaded: " << "textures/tex.png").str()
        );
    }


    const char* glsl_version = "#version 150";
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL((SDL_Window *)this->window->getRaw(), ((DefaultWindow *)this->window)->getContext());
    ImGui_ImplOpenGL3_Init(glsl_version);
    Stopwatch *stopwatch = Stopwatch::create();
    stopwatch->start();
//    std::string source = IO::getInstance()->readAsString("./resources/svgs/1296432.svg");
//    std::string source = IO::getInstance()->readAsString("./resources/svgs/37046.svg");
//    std::string source = IO::getInstance()->readAsString("./resources/svgs/Muffet.svg");
//    std::string source = IO::getInstance()->readAsString("./resources/svgs/OBEYSUDO.svg");
//    std::string source = IO::getInstance()->readAsString("./resources/svgs/teapot2.svg");
//    std::string source = IO::getInstance()->readAsString("./resources/svgs/yume nikki.svg");
//    std::string source = IO::getInstance()->readAsString("./resources/svgs/helloworld.svg");
//    Svg::Document *document = Svg::Parser::parse(source);
//    std::vector<VNfloat> rasterizedPath = Svg::Rasterizer::rasterize2D(document, 5);
//    Tools::Vertices2D::flip2D(rasterizedPath, false, true);
//    Tools::Vertices2D::center2D(rasterizedPath);
//    Tools::Vertices2D::normalize2D(rasterizedPath);
//    Tools::Vertices2D::normalize2DDimensions(rasterizedPath, document->getDimensions());
//    VAN_USER_CRITICAL("Времени просрано на растеризацию SVG: {}", stopwatch->stop());
//    stopwatch->start();
//    std::vector<VNuint> triangulatedIndices = Tools::Vertices2D::triangulate(rasterizedPath);
//    VAN_USER_CRITICAL("Времени просрано на триангуляцию {} точек SVG: {}", rasterizedPath.size()/2, stopwatch->stop());
//    this->svgPath = MeshFactory::fromVertices(rasterizedPath.data(), rasterizedPath.size());
//    this->svgPathTriangulated = MeshFactory::fromVerticesIndices(rasterizedPath.data(), rasterizedPath.size(), triangulatedIndices.data(), triangulatedIndices.size());


    std::string source = IO::getInstance()->readAsString("./resources/svgs/helloworld.svg");
    Svg::Document *document = Svg::Parser::parse(source);
    this->firstFrame = Svg::Rasterizer::rasterize2D(document, 10);
    Tools::Vertices2D::flip2D(this->firstFrame, false, true);
    Tools::Vertices2D::center2D(this->firstFrame);
    Tools::Vertices2D::normalize2DDimensions(this->firstFrame, document->getDimensions());
    delete document;

    source = IO::getInstance()->readAsString("./resources/svgs/helloworld2.svg");
    document = Svg::Parser::parse(source);
    this->lastFrame = Svg::Rasterizer::rasterize2D(document, 10);
    Tools::Vertices2D::flip2D(this->lastFrame, false, true);
    Tools::Vertices2D::center2D(this->lastFrame);
    Tools::Vertices2D::normalize2DDimensions(this->lastFrame, document->getDimensions());
    delete document;

    Tools::Vertices2D::interpolate(this->firstFrame, this->lastFrame, this->interpolatedFrame, 0.0f);
    this->pathInterpolated = MeshFactory::fromVertices(this->interpolatedFrame.data(), this->interpolatedFrame.size());

    std::vector<VNuint> triangulatedIndices = Tools::Vertices2D::triangulate(interpolatedFrame);
    this->svgPathTriangulated = MeshFactory::fromVerticesIndices(interpolatedFrame.data(), interpolatedFrame.size(), triangulatedIndices.data(), triangulatedIndices.size());



    this->lineShader = ShaderFactory::create("shaders/line.xml", "Line shader");
    this->blurShader = ShaderFactory::create("shaders/blur.xml", "Blur shader");
    delete stopwatch;
    Ref<Shader> glowShader = ShaderFactory::create("shaders/blur.xml", "Blur shader");
    this->glow = PostprocessingFactory::create(glowShader, this->window->getWidth(), this->window->getHeight());
}

void CustomState::onDetach()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void CustomState::onStateLostPriority()
{
    VAN_USER_INFO("{} lost priority on state queue!", this->getName());
}

void CustomState::onStateGainedPriority()
{
    VAN_USER_INFO("{} lost priority on state queue!", this->getName());
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
    if (this->eventProvider->isKeyJustPressed(Keyboard::KeyCode::F))
    {
        this->window->setFullScreen(!this->window->isFullScreen());
    }
    if (this->eventProvider->isKeyJustPressed(Keyboard::KeyCode::Escape))
    {
        this->stateStack->requestPopAll();
    }
    if (this->eventProvider->isKeyPressed(Keyboard::KeyCode::W))
    {
        auto cameraView = this->camera->getView();
        cameraView = glm::translate(cameraView, this->camera->getUp()*(float)deltatime);
        this->camera->setView(cameraView);
    }
    if (this->eventProvider->isKeyJustPressed(Keyboard::KeyCode::Q))
    {
        this->window->grabCursor(!this->window->isCursorGrabbed());
    }
}

void CustomState::fixedUpdate(double deltatime)
{

}

void CustomState::preRender()
{
    RenderApi::instance()->clear();
}

void CustomState::render()
{
    if (this->application->getFixedUpdateTicks() % 300 == 0)
    {
        VAN_USER_INFO("FPS: {}", 1.0/this->application->getDeltatime());
    }

    if (this->guiModel.interpolationUpdated())
    {
        Tools::Vertices2D::interpolate(this->firstFrame, this->lastFrame, this->interpolatedFrame, this->guiModel.interpolation);
        this->pathInterpolated = MeshFactory::fromVertices(this->interpolatedFrame.data(), this->interpolatedFrame.size());
        std::vector<VNuint> triangulatedIndices = Tools::Vertices2D::triangulate(this->interpolatedFrame);
        this->svgPathTriangulated = MeshFactory::fromVerticesIndices(this->interpolatedFrame.data(), this->interpolatedFrame.size(), triangulatedIndices.data(), triangulatedIndices.size());
    }
//    if (this->guiModel.qualityUpdated())
//    {
//        std::string source = IO::getInstance()->readAsString("./resources/svgs/helloworld.svg");
//        Svg::Document *document = Svg::Parser::parse(source);
//        this->firstFrame = Svg::Rasterizer::rasterize2D(document, this->guiModel.quality);
//        Tools::Vertices2D::flip2D(this->firstFrame, false, true);
//        Tools::Vertices2D::center2D(this->firstFrame);
//        Tools::Vertices2D::normalize2DDimensions(this->firstFrame, document->getDimensions());
//        delete document;
//
//        source = IO::getInstance()->readAsString("./resources/svgs/helloworld2.svg");
//        document = Svg::Parser::parse(source);
//        this->lastFrame = Svg::Rasterizer::rasterize2D(document, this->guiModel.quality);
////        Tools::Vertices2D::flip2D(this->lastFrame, false, true);
//        Tools::Vertices2D::center2D(this->lastFrame);
//        Tools::Vertices2D::normalize2DDimensions(this->lastFrame, document->getDimensions());
//        delete document;
//
//        Tools::Vertices2D::interpolate(this->firstFrame, this->lastFrame, this->interpolatedFrame, this->guiModel.interpolation);
//        this->pathInterpolated = MeshFactory::fromVertices(this->interpolatedFrame.data(), this->interpolatedFrame.size());
//
//        std::vector<VNuint> triangulatedIndices = Tools::Vertices2D::triangulate(interpolatedFrame);
//        this->svgPathTriangulated = MeshFactory::fromVerticesIndices(interpolatedFrame.data(), interpolatedFrame.size(), triangulatedIndices.data(), triangulatedIndices.size());
//
//    }

    glDisable(GL_DEPTH_TEST);

    this->glow->bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    this->lineShader->bind();
    this->svgPathTriangulated->bind();
    this->lineShader->setGlobalFloat3("clientColor", glm::vec3(1.0f));
    glDrawElements(GL_TRIANGLES, this->svgPathTriangulated->getVertexArray()->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
    this->svgPathTriangulated->unbind();
    this->glow->unbind();


    this->glow->bindShader();
    Ref<Shader> glowShader = this->glow->getShader();
    glowShader->setGlobalFloat2("screenResolution", this->window->getGeometry());
    glowShader->setGlobalFloat("power", this->guiModel.glowPower);
    glowShader->setGlobalFloat("blurHue", this->guiModel.glowHue);
    this->glow->draw();



//    this->lineShader->bind();
//    this->lineShader->setGlobalFloat3("clientColor", this->guiModel.fillColor);
//    this->svgPathTriangulated->bind();
//    glDrawElements(GL_TRIANGLES, this->svgPathTriangulated->getVertexArray()->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);

    this->lineShader->bind();

    this->svgPathTriangulated->bind();
    this->lineShader->setGlobalFloat3("clientColor", glm::vec3(this->guiModel.fillColor));
    glDrawElements(GL_TRIANGLES, this->svgPathTriangulated->getVertexArray()->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
    this->svgPathTriangulated->unbind();

//    this->lineShader->setGlobalFloat3("clientColor", this->guiModel.borderColor);
//    this->pathInterpolated->bind();
//    glDrawElements(GL_LINES, this->pathInterpolated->getVertexArray()->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
//    this->pathInterpolated->unbind();

    glEnable(GL_DEPTH_TEST);



}



void CustomState::postRender()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame((SDL_Window *)this->window->getRaw());
    ImGui::NewFrame();
    {
        ImGui::Begin("SVG model parameters");
        ImGui::ColorEdit3("Border color", &this->guiModel.borderColor.x);
        ImGui::ColorEdit3("Fill color", &this->guiModel.fillColor.x);
        ImGui::SliderFloat("Glow hue", &this->guiModel.glowHue, 0.0f, 1.0f);
        ImGui::SliderFloat("Changing speed", &this->guiModel.deltaSpeed, 0.0f, 1.0f);
        ImGui::SliderFloat("Interpolation", &this->guiModel.interpolation, 0.0f, 1.0f);
        ImGui::SliderFloat("Glow power", &this->guiModel.glowPower, 0.0f, 2.0f);
        ImGui::SliderInt("Model quality", &this->guiModel.quality, 0, 50);
        ImGui::End();
    }

    ImGui::Render();
    glViewport(0, 0, this->window->getWidth(), this->window->getHeight());
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

const std::string &CustomState::getName() const noexcept
{
    return this->name;
}

