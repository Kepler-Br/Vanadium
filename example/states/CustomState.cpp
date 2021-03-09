#include "CustomState.h"
#define EVENT_SUBSCRIBE(memberFunction, eventType) [this](Event *event){ memberFunction((eventType *)event); }
// Todo: remove this:
#include "../../vanadium/src/platform/opengl/OpenGLFramebuffer.h"


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
//    this->window->setGeometry({event->getWidth(), event->getHeight()});
//    this->camera->setPerspective(glm::radians(75.0f), this->window->getAspect(), 0.001f, 10.0f);
//    this->framebuffer->resize(event->getWidth(), event->getHeight());
    this->glow->getFramebuffer()->resize(event->getWidth(), event->getHeight());
    glm::vec2 orthoDims = {this->window->getWidth(), this->window->getHeight()};
    orthoDims = {orthoDims.x > orthoDims.y ? 1.0f : orthoDims.x / orthoDims.y,
                 orthoDims.y > orthoDims.x ? 1.0f : orthoDims.y / orthoDims.x};
    this->camera->setOrthographic(-orthoDims.x/2.0f, orthoDims.x/2.0f, -orthoDims.y/2.0f, orthoDims.y/2.0f, 0.1f, 10.0f);
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
    this->framebufferForGui = FramebufferFactory::create({800, 600,
                                                          Framebuffer::AttachmentSpecification({Framebuffer::TextureFormat::Depth,
                                                                                                Framebuffer::TextureFormat::RGBA8,
                                                                                               }), 1, Texture::Filtering::Linear});
    if (this->framebufferForGui == nullptr || !(*this->framebufferForGui))
    {
        std::stringstream msg;
        throw ExecutionInterrupted(
                dynamic_cast<std::stringstream&>
                (msg << "Framebuffer foils.").str()
        );
    }
    this->gui = MakeRef<Gui>(this->framebufferForGui, this->application);
    Gui::Model *model = this->gui->getModel();

    this->camera = MakeRef<Camera>();

    this->texture = TextureFactory::create("textures/tex.png");
    if (!this->texture || !*this->texture)
    {
        std::stringstream msg;
        throw ExecutionInterrupted(
                dynamic_cast<std::stringstream&>
                (msg << "Texture not loaded: " << "textures/tex.png").str()
        );
    }



    Stopwatch *stopwatch = Stopwatch::create();
    stopwatch->start();

    std::string source = IO::getInstance()->readAsString("./resources/svgs/helloworld.svg");
    Ref<Svg::Document> document = Svg::Parser::parse(source);
    this->firstFrame = Svg::Rasterizer::rasterize2D(document.get(), model->quality);
    Tools::Vertices2D::flip2D(this->firstFrame, false, true);
    Tools::Vertices2D::center2D(this->firstFrame);
    Tools::Vertices2D::normalize2DDimensions(this->firstFrame, document->getDimensions());

    source = IO::getInstance()->readAsString("./resources/svgs/helloworld2.svg");
    document = Svg::Parser::parse(source);
    this->lastFrame = Svg::Rasterizer::rasterize2D(document.get(), model->quality);
    Tools::Vertices2D::flip2D(this->lastFrame, false, true);
    Tools::Vertices2D::center2D(this->lastFrame);
    Tools::Vertices2D::normalize2DDimensions(this->lastFrame, document->getDimensions());

    Tools::Vertices2D::interpolate(this->firstFrame, this->lastFrame, this->interpolatedFrame, model->interpolation);
    this->pathInterpolated = MeshFactory::fromVertices(this->interpolatedFrame.data(), this->interpolatedFrame.size());

    std::vector<VNuint> triangulatedIndices = Tools::Vertices2D::triangulate(interpolatedFrame);
    this->svgPathTriangulated = MeshFactory::fromVerticesIndices(interpolatedFrame.data(), interpolatedFrame.size(), triangulatedIndices.data(), triangulatedIndices.size());



    this->lineShader = ShaderFactory::create("shaders/line.xml", "Line shader");
    delete stopwatch;
    Ref<Shader> glowShader = ShaderFactory::create("shaders/blur.xml", "Blur shader");
    Ref<Shader> fastGlowShader = ShaderFactory::create("shaders/fastBlur.xml", "Fast blur shader");
    this->glow = PostprocessingFactory::create(glowShader, this->window->getWidth(), this->window->getHeight());
    this->fastGlow = PostprocessingFactory::create(fastGlowShader, this->window->getWidth(), this->window->getHeight());
    glm::vec2 orthoDims = {this->window->getWidth(), this->window->getHeight()};
    orthoDims = {orthoDims.x > orthoDims.y ? 1.0f : orthoDims.x / orthoDims.y,
                 orthoDims.y > orthoDims.x ? 1.0f : orthoDims.y / orthoDims.x};
    this->camera->setOrthographic(-orthoDims.x/2.0f, orthoDims.x/2.0f, -orthoDims.y/2.0f, orthoDims.y/2.0f, 0.1f, 10.0f);




}

void CustomState::onDetach()
{

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
//    if (this->guiModel.hueScrolling)
//    {
//        this->guiModel.glowHue += deltatime/10.0f;
//        this->guiModel.glowHue = this->guiModel.glowHue > 1.0f ? 0.0f : this->guiModel.glowHue;
//    }
}

void CustomState::preRender()
{
    RenderApi::instance()->clear();
}

void CustomState::render()
{
    Gui::Model *model = this->gui->getModel();
    if (true)
    {
        static double averageFps = 0.0f;
        averageFps += 1.0/this->application->getDeltatime();
        if (this->application->getFixedUpdateTicks() % 60 == 0)
        {
            VAN_USER_INFO("FPS: {}", averageFps/60.0);
            averageFps = 0.0;
        }
    }
    if (glm::abs(glm::abs(this->currentInterpolation) - glm::abs(model->interpolation)) > 0.01f)
    {
        this->currentInterpolation = Math::lerp(this->currentInterpolation, model->interpolation, glm::clamp(this->application->getDeltatime() * model->deltaSpeed, 0.0, 1.0));
        this->deltaUpdated = true;
        if (model->immediateInterpolation)
            this->currentInterpolation = model->interpolation;
    }
    if (this->deltaUpdated &&
       (this->application->getTicksSinceStart() % model->skipSteps == 0 || !model->skipInterpolationFrames))
    {
       this->deltaUpdated = false;
        Tools::Vertices2D::interpolate(this->firstFrame, this->lastFrame, this->interpolatedFrame, this->currentInterpolation);
        this->pathInterpolated = MeshFactory::fromVertices(this->interpolatedFrame.data(), this->interpolatedFrame.size());
        std::vector<VNuint> triangulatedIndices = Tools::Vertices2D::triangulate(this->interpolatedFrame);
        this->svgPathTriangulated = MeshFactory::fromVerticesIndices(this->interpolatedFrame.data(), this->interpolatedFrame.size(), triangulatedIndices.data(), triangulatedIndices.size());
    }


    if (model->qualityUpdated())
    {
//        printf("Quality changed\n");
        std::string source = IO::getInstance()->readAsString("./resources/svgs/helloworld.svg");
        Ref<Svg::Document> document = Svg::Parser::parse(source);
        this->firstFrame = Svg::Rasterizer::rasterize2D(document.get(), model->quality);
        Tools::Vertices2D::flip2D(this->firstFrame, false, true);
        Tools::Vertices2D::center2D(this->firstFrame);
        Tools::Vertices2D::normalize2DDimensions(this->firstFrame, document->getDimensions());

        source = IO::getInstance()->readAsString("./resources/svgs/helloworld2.svg");
        document = Svg::Parser::parse(source);
        this->lastFrame = Svg::Rasterizer::rasterize2D(document.get(), model->quality);
        Tools::Vertices2D::flip2D(this->lastFrame, false, true);
        Tools::Vertices2D::center2D(this->lastFrame);
        Tools::Vertices2D::normalize2DDimensions(this->lastFrame, document->getDimensions());

        Tools::Vertices2D::interpolate(this->firstFrame, this->lastFrame, this->interpolatedFrame, this->currentInterpolation);
        this->pathInterpolated = MeshFactory::fromVertices(this->interpolatedFrame.data(), this->interpolatedFrame.size());

        std::vector<VNuint> triangulatedIndices = Tools::Vertices2D::triangulate(this->interpolatedFrame);
        this->svgPathTriangulated = MeshFactory::fromVerticesIndices(interpolatedFrame.data(), interpolatedFrame.size(), triangulatedIndices.data(), triangulatedIndices.size());
    }

    Ref<Postprocessing> gl;
    if (model->isFastBlur)
        gl = this->fastGlow;
    else
        gl = this->glow;

    glDisable(GL_DEPTH_TEST);

    gl->bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    this->lineShader->bind();
    this->svgPathTriangulated->bind();
    this->lineShader->setGlobalFloat3("clientColor", glm::vec3(1.0f, 0.0f, 0.0f));
    this->lineShader->setGlobalMat4("proj", this->camera->getProjection());
    glDrawElements(GL_TRIANGLES, this->svgPathTriangulated->getVertexArray()->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
    this->svgPathTriangulated->unbind();

    glPointSize(8.0f);
    this->lineShader->setGlobalFloat3("clientColor", glm::vec3(1.0f, 0.0f, 1.0f));
    this->svgPathTriangulated->bind();
    glDrawElements(GL_POINTS, this->svgPathTriangulated->getVertexArray()->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
    this->svgPathTriangulated->unbind();
    gl->unbind();

    Ref<Shader> glowShader = gl->getShader();
    gl->bindShader();
    glowShader->setGlobalFloat2("screenResolution", this->window->getGeometry());
    glowShader->setGlobalFloat("power", model->glowPower);
    glowShader->setGlobalFloat("blurHue", model->glowHue);
    gl->draw();



//    this->lineShader->bind();
//    this->lineShader->setGlobalFloat3("clientColor", this->guiModel.fillColor);
//    this->svgPathTriangulated->bind();
//    glDrawElements(GL_TRIANGLES, this->svgPathTriangulated->getVertexArray()->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);

    this->lineShader->bind();
    this->lineShader->setGlobalMat4("proj", this->camera->getProjection());
    this->svgPathTriangulated->bind();
    this->lineShader->setGlobalFloat3("clientColor", glm::vec3(model->fillColor));
    glDrawElements(GL_TRIANGLES, this->svgPathTriangulated->getVertexArray()->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
    this->svgPathTriangulated->unbind();


    this->lineShader->setGlobalFloat3("clientColor", model->borderColor);
//    this->pathInterpolated->bind();
//    glDrawElements(GL_POINTS, this->pathInterpolated->getVertexArray()->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);

    glDrawElements(GL_LINES, this->pathInterpolated->getVertexArray()->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
    this->pathInterpolated->unbind();




    glm::vec2 orthoDims = {windowViewportSize.x > windowViewportSize.y ? 1.0f : windowViewportSize.x / windowViewportSize.y,
                 windowViewportSize.y > windowViewportSize.x ? 1.0f : windowViewportSize.y / windowViewportSize.x};
    glm::mat4 ortho = glm::ortho(-orthoDims.x/2.0f, orthoDims.x/2.0f, -orthoDims.y/2.0f, orthoDims.y/2.0f, 0.1f, 10.0f);
    this->framebufferForGui->resize(this->windowViewportSize.x, this->windowViewportSize.y);
    this->framebufferForGui->bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    this->svgPathTriangulated->bind();
    this->lineShader->setGlobalMat4("proj", ortho);
    this->lineShader->setGlobalFloat3("clientColor", glm::vec3(1.0f));
    glDrawElements(GL_TRIANGLES, this->svgPathTriangulated->getVertexArray()->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
    this->svgPathTriangulated->unbind();
    this->framebufferForGui->unbind();
    glEnable(GL_DEPTH_TEST);

    this->gui->render();
}



void CustomState::postRender()
{

}

const std::string &CustomState::getName() const noexcept
{
    return this->name;
}

