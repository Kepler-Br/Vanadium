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
    this->window->grabCursor(true);
    this->framebuffer = FramebufferFactory::create({this->window->getWidth(), this->window->getHeight(),
                                                    Framebuffer::AttachmentSpecification({Framebuffer::TextureFormat::Depth,
                                                                                                         Framebuffer::TextureFormat::RGBA8,}),
                                                    },
                                                   Texture::Filtering::Linear);

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
    this->framebufferShader = ShaderFactory::create("shaders/framebufferblur.xml", "FramebufferShader");
    if (!this->framebufferShader || !*this->framebufferShader)
    {
        std::stringstream msg;
        throw ExecutionInterrupted(
                dynamic_cast<std::stringstream&>
                (msg << "Shader not loaded: " << "shaders/framebuffer.xml").str()
        );
    }
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
//    std::string source = IO::getInstance()->readAsString("./resources/svgs/teapot.svg");
//    std::string source = IO::getInstance()->readAsString("./resources/svgs/yume nikki.svg");
    std::string source = IO::getInstance()->readAsString("./resources/svgs/helloworld.svg");
    Svg::Document *document = Svg::Parser::parse(source);
    std::vector<VNfloat> rasterizedPath = Svg::Rasterizer::rasterize2D(document, 500);
//    VAN_USER_INFO("Total paths in layer({}): {}", document->getLayers()[0]->getName(), document->getLayers()[0]->getTotalPaths());
    Tools::Vertices::flip2D(rasterizedPath, false, true);
    Tools::Vertices::center2D(rasterizedPath);
    Tools::Vertices::normalize2D(rasterizedPath);
//    Svg::Rasterizer::normalize2DDimensions(rasterizedPathStrip, document->getDimensions());
    VAN_USER_CRITICAL("Времени просрано на растеризацию SVG: {}", stopwatch->stop());
    stopwatch->start();
//    std::vector<VNfloat> triangulated = triangulate(rasterizedPathStrip);
    std::vector<VNuint> triangulatedIndices = Tools::Vertices::triangulate(rasterizedPath);
    VAN_USER_CRITICAL("Времени просрано на триангуляцию {} точек SVG: {}", rasterizedPath.size()/2, stopwatch->stop());
    this->svgPath = MeshFactory::fromVertices(rasterizedPath.data(), rasterizedPath.size());
    this->svgPathTriangulated = MeshFactory::fromVerticesIndices(rasterizedPath.data(), rasterizedPath.size(), triangulatedIndices.data(), triangulatedIndices.size());

    this->lineShader = ShaderFactory::create("shaders/line.xml", "Line shader");
    delete document;
    delete stopwatch;
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
    if (this->application->getTicksSinceStart() % 50 == 0)
    {
        VAN_USER_INFO("FPS: {}", 1.0/this->application->getDeltatime());
    }
//    this->framebuffer->bind();
//    this->shader->bind();
//    this->shader->setGlobalMat4("model", glm::mat4(1.0f));
//    this->shader->setGlobalMat4("VP", this->camera->getVP());
//    this->texture->bind(0);
//    this->mesh->bind();
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glDrawElements(GL_TRIANGLES, this->mesh->getVertexArray()->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);


//    this->framebuffer->bind();
//    this->lineShader->bind();
//    this->svgPath->bind();
//    glDrawElements(GL_LINES, this->svgPath->getVertexArray()->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
//    this->framebuffer->unbind();


//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // we're not using the stencil buffer now
//    glDisable(GL_DEPTH_TEST);
//    this->framebufferShader->bind();
//    RenderApi::instance()->setViewport(0, 0, this->window->getWidth(), this->window->getHeight());
//    GLuint framebufferTexture = ((OpenGLFramebuffer *)this->framebuffer.get())->getColorAttachment(0);
//    this->screenPlane->bind();
//    this->framebufferShader->setGlobalFloat2("screenResolution", this->window->getGeometry());
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, framebufferTexture);
//    glDrawElements(GL_TRIANGLES, this->screenPlane->getVertexArray()->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
//    glBindTexture(GL_TEXTURE_2D, 0);
//    glEnable(GL_DEPTH_TEST);

    this->lineShader->bind();
    glDisable(GL_DEPTH_TEST);

    this->lineShader->setGlobalFloat3("clientColor", glm::vec3(0.5f));
    this->svgPathTriangulated->bind();
    glDrawElements(GL_TRIANGLES, this->svgPathTriangulated->getVertexArray()->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);

    this->lineShader->setGlobalFloat3("clientColor", glm::vec3(1.0f, 0.0f, 1.0f));
    this->svgPath->bind();
    glDrawElements(GL_LINES, this->svgPath->getVertexArray()->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);

    glEnable(GL_DEPTH_TEST);



}



void CustomState::postRender()
{
//    static bool show_demo_window = true;
//    static bool show_another_window = false;
//    static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
//
//    ImGui_ImplOpenGL3_NewFrame();
//    ImGui_ImplSDL2_NewFrame((SDL_Window *)this->window->getRaw());
//    ImGui::NewFrame();
//
//    if (show_demo_window)
//        ImGui::ShowDemoWindow(&show_demo_window);
//    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
//    {
//        static float f = 0.0f;
//        static int counter = 0;
//
//        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
//
//        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
//        ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
//        ImGui::Checkbox("Another Window", &show_another_window);
//
//        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
//        ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
//
//        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
//            counter++;
//        ImGui::SameLine();
//        ImGui::Text("counter = %d", counter);
//
//        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
//        ImGui::End();
//    }
//
//    // 3. Show another simple window.
//    if (show_another_window)
//    {
//        ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
//        ImGui::Text("Hello from another window!");
//        if (ImGui::Button("Close Me"))
//            show_another_window = false;
//        ImGui::End();
//    }
//
//
//    ImGui::Render();
//    glViewport(0, 0, this->window->getWidth(), this->window->getHeight());
//    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

const std::string &CustomState::getName() const noexcept
{
    return this->name;
}

