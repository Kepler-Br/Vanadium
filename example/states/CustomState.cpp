#include "CustomState.h"
#define EVENT_SUBSCRIBE(memberFunction, eventType) [this](Event *event){ memberFunction((eventType *)event); }
// Todo: remove this:
#include "../../vanadium/src/platform/opengl/OpenGLFramebuffer.h"
#include "Gui.h"

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
    this->gui->processEvent(event);
}

void CustomState::onKeyReleased(KeyReleasedEvent *event) noexcept
{
//    VAN_USER_INFO("Key released: {}", event->toString());
    this->gui->processEvent(event);
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
//    if (this->window->isCursorGrabbed())
//    {
//        glm::mat4 view = this->camera->getView();
//        glm::vec2 delta = event->getDelta();
//        view = glm::rotate(view, delta.x * (VNfloat) this->application->getDeltatime(), this->camera->getUp());
//        view = glm::rotate(view, delta.y * (VNfloat) this->application->getDeltatime(), this->camera->getRight());
//
//        this->camera->setView(view);
//    }
    this->gui->processEvent(event);
}

void CustomState::onMouseScroll(MouseScrollEvent *event) noexcept
{
//    VAN_USER_INFO(event->toString());
    this->gui->processEvent(event);
}

void CustomState::initSvgModelContainer() noexcept
{
    bool succ;

    // Open documents.
    succ = this->svgModelContainer.openDocument("./resources/svgs/helloworld.svg");
    if (!succ)
    {
        std::stringstream msg;
        throw ExecutionInterrupted(
                this->svgModelContainer.getErrorString()
        );
    }
    succ = this->svgModelContainer.openDocument("./resources/svgs/helloworld2.svg");
    if (!succ)
    {
        std::stringstream msg;
        throw ExecutionInterrupted(
                this->svgModelContainer.getErrorString()
        );
    }
    succ = this->svgModelContainer.openDocument("./resources/svgs/helloworld3.svg");
    if (!succ)
    {
        std::stringstream msg;
        throw ExecutionInterrupted(
                this->svgModelContainer.getErrorString()
        );
    }

    // Create models.
    std::string newModelName = "Test model 1";
    succ = this->svgModelContainer.createModel(newModelName);
    if (!succ)
    {
        std::stringstream msg;
        throw ExecutionInterrupted(
                this->svgModelContainer.getErrorString()
        );
    }

    // Add groups to models.
    std::string newGroupName = "Test group 1";
    succ = this->svgModelContainer.addGroupToModel(newModelName, newGroupName);
    if(!succ)
    {
        std::stringstream msg;
        throw ExecutionInterrupted(
                this->svgModelContainer.getErrorString()
        );
    }

    // Add keyed elements to groups.
    SvgModelContainer::Model *model = this->svgModelContainer.getModelByName(newModelName);
    VNuint groupsTotal = model->groups.size();
    SvgModelContainer::Group &group = model->groups[groupsTotal - 1];
    succ = this->svgModelContainer.addKeyedElementToGroup(newModelName, "New keyed element", groupsTotal - 1);
    if(!succ)
    {
        std::stringstream msg;
        throw ExecutionInterrupted(
                this->svgModelContainer.getErrorString()
        );
    }

    // Add elements to keyed elements.
    VNuint keyedElementsTotal = group.keyedElements.size();
    succ = this->svgModelContainer.addElementToKeyedElement(newModelName, "New element", "./resources/svgs/helloworld.svg", "layer1", groupsTotal - 1, keyedElementsTotal - 1);
    if(!succ)
    {
        std::stringstream msg;
        throw ExecutionInterrupted(
                this->svgModelContainer.getErrorString()
        );
    }
    succ = this->svgModelContainer.addElementToKeyedElement(newModelName, "New element2", "./resources/svgs/helloworld2.svg", "layer1", groupsTotal - 1, keyedElementsTotal - 1);
    if(!succ)
    {
        std::stringstream msg;
        throw ExecutionInterrupted(
                this->svgModelContainer.getErrorString()
        );
    }
    this->svgModelContainer.update(1.0f);
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
    this->framebufferForLayerPreview = FramebufferFactory::create({800, 600,
                                                          Framebuffer::AttachmentSpecification({Framebuffer::TextureFormat::Depth,
                                                                                                Framebuffer::TextureFormat::RGBA8,
                                                                                               }), 1, Texture::Filtering::Linear});
    if (this->framebufferForLayerPreview == nullptr || !(*this->framebufferForLayerPreview))
    {
        std::stringstream msg;
        throw ExecutionInterrupted(
                dynamic_cast<std::stringstream&>
                (msg << "Framebuffer foils.").str()
        );
    }
    this->gui = MakeRef<Gui>(this->framebufferForGui, this->framebufferForLayerPreview, this->application, this);

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

    this->lineShader = ShaderFactory::create("shaders/line.xml", "Line shader");

    Ref<Shader> glowShader = ShaderFactory::create("shaders/blur.xml", "Blur shader");
    Ref<Shader> fastGlowShader = ShaderFactory::create("shaders/fastBlur.xml", "Fast blur shader");
    this->glow = PostprocessingFactory::create(glowShader, this->window->getWidth(), this->window->getHeight());
    this->fastGlow = PostprocessingFactory::create(fastGlowShader, this->window->getWidth(), this->window->getHeight());
    glm::vec2 orthoDims = {this->window->getWidth(), this->window->getHeight()};
    orthoDims = {orthoDims.x > orthoDims.y ? 1.0f : orthoDims.x / orthoDims.y,
                 orthoDims.y > orthoDims.x ? 1.0f : orthoDims.y / orthoDims.x};
    this->camera->setOrthographic(-orthoDims.x/2.0f, orthoDims.x/2.0f, -orthoDims.y/2.0f, orthoDims.y/2.0f, 0.1f, 2.0f);





    Stopwatch *stopwatch = Stopwatch::create();
    stopwatch->start();

//    bool succ;
//    succ = this->svgModelContainer.openDocument("./resources/svgs/helloworld.svg");
//    if (!succ)
//    {
//        std::stringstream msg;
//        throw ExecutionInterrupted(
//                dynamic_cast<std::stringstream&>
//                (msg << "./resources/svgs/helloworld.svg is bad").str()
//        );
//    }
//
//    std::string documentPath = "./resources/svgs/other/body-ready.svg";
//    succ = this->svgModelContainer.openDocument(documentPath);
//    if (!succ)
//    {
//        std::stringstream msg;
//        throw ExecutionInterrupted(
//                dynamic_cast<std::stringstream&>
//                (msg << "./resources/svgs/helloworld2.svg is bad").str()
//        );
//    }
//    std::string titsModelName = this->svgModelContainer.createModel();
//    if(!this->svgModelContainer.addElementToModel(titsModelName, documentPath, "BellySmall", true))
//    {
//        std::stringstream msg;
//        throw ExecutionInterrupted(
//                dynamic_cast<std::stringstream&>
//                (msg << "./resources/svgs/helloworld2.svg layer1 is bad").str()
//        );
//    }
//    if(!this->svgModelContainer.addElementToModel(titsModelName, documentPath, "BellyBig", true))
//    {
//        std::stringstream msg;
//        throw ExecutionInterrupted(
//                dynamic_cast<std::stringstream&>
//                (msg << "./resources/svgs/helloworld2.svg layer1 is bad").str()
//        );
//    }

    this->initSvgModelContainer();
    VAN_USER_INFO("SvgModelContainer initialization: {}", stopwatch->stop());
    delete stopwatch;
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
    if (this->eventProvider->isKeyJustPressed(Keyboard::KeyCode::Q))
    {
        this->window->grabCursor(!this->window->isCursorGrabbed());
    }

    Gui::Model *guiModel = this->gui->getModel();
    if (guiModel->skipInterpolationFrames)
    {
        if (this->application->getTicksSinceStart() % guiModel->skipSteps == 0)
        {
            this->svgModelContainer.setQuality(this->gui->getModel()->quality);
            this->svgModelContainer.update(0.5f * this->gui->getModel()->interpolationSpeed * (VNfloat)guiModel->skipSteps);
        }
    }
    else
    {
        this->svgModelContainer.setQuality(this->gui->getModel()->quality);
        this->svgModelContainer.update(0.5f * this->gui->getModel()->interpolationSpeed);
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
    Gui::Model *guiModel = this->gui->getModel();
//    if (true)
//    {
//        static double averageFps = 0.0f;
//        averageFps += 1.0/this->application->getDeltatime();
//        if (this->application->getFixedUpdateTicks() % 60 == 0)
//        {
//            VAN_USER_INFO("FPS: {}", averageFps/60.0);
//            averageFps = 0.0;
//        }
//    }

    Ref<Postprocessing> gl;
    if (guiModel->isFastBlur)
        gl = this->fastGlow;
    else
        gl = this->glow;

    glDisable(GL_DEPTH_TEST);


    this->windowViewportSize = this->gui->getModel()->renderViewportSize;
    glm::vec2 orthoDims = {windowViewportSize.x > windowViewportSize.y ? 1.0f : windowViewportSize.x / windowViewportSize.y,
                           windowViewportSize.y > windowViewportSize.x ? 1.0f : windowViewportSize.y / windowViewportSize.x};
//    glm::mat4 ortho = glm::ortho(-orthoDims.x/2.0f, orthoDims.x/2.0f, -orthoDims.y/2.0f, orthoDims.y/2.0f, 0.1f, 10.0f);
    glm::mat4 ortho = glm::ortho(-orthoDims.x, orthoDims.x, -orthoDims.y, orthoDims.y, 0.1f, 10.0f);
    this->framebufferForGui->resize(this->windowViewportSize.x, this->windowViewportSize.y);


    Ref<Mesh> meshToRender = this->svgModelContainer.getModels().begin()->second.triangulatedMesh;

    gl->getFramebuffer()->resize(this->windowViewportSize.x, this->windowViewportSize.y);
    gl->bind();
    glClear(GL_COLOR_BUFFER_BIT);
    this->lineShader->bind();
    if (guiModel->drawBlur)
    {
        this->lineShader->setGlobalFloat3("clientColor", guiModel->auraColor);
        this->lineShader->setGlobalMat4("proj", ortho);
        meshToRender->bind();
        glDrawElements(GL_TRIANGLES, meshToRender->getVertexArray()->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
    }
    gl->unbind();
    this->framebufferForGui->bind();

    if (guiModel->drawBlur)
    {
        Ref<Shader> glowShader = gl->getShader();
        gl->bindShader();
        glowShader->setGlobalFloat2("screenResolution", gl->getFramebuffer()->getGeometry());
        glowShader->setGlobalFloat("power", guiModel->glowPower);
        gl->draw();
    }
    else
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    if (guiModel->drawBody)
    {
        this->lineShader->bind();
        meshToRender->bind();
        this->lineShader->setGlobalMat4("proj", ortho);
        this->lineShader->setGlobalFloat3("clientColor", glm::vec3(guiModel->fillColor));
        glDrawElements(GL_TRIANGLES, meshToRender->getVertexArray()->getIndexBuffer()->getCount(), GL_UNSIGNED_INT,
                       nullptr);
        meshToRender->unbind();
    }
//    if (this->gui->getModel()->currentlySelectedItemType == Gui::SelectedTreeItem::Model)
//    {
//        VNuint modelIndex = this->gui->getModel()->modelSelectedIndex;
//        SvgModelContainer::Model *model = this->svgModelContainer.getModelByIndex(modelIndex);
//        Ref<Mesh> borderMesh = model->borderMesh;
//        this->lineShader->bind();
//        this->lineShader->setGlobalFloat3("clientColor", glm::vec3(0.8f, 0.8f, 0.0f));
//        borderMesh->bind();
//        glDrawElements(GL_LINES, borderMesh->getVertexArray()->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
//        borderMesh->unbind();
//    }
//    else if (this->gui->getModel()->currentlySelectedItemType == Gui::SelectedTreeItem::Element)
//    {
//        VNuint modelIndex = this->gui->getModel()->modelSelectedIndex;
//        VNuint elementIndex = this->gui->getModel()->elementSelectedIndex;
//        SvgModelContainer::Model *model = this->svgModelContainer.getModelByIndex(modelIndex);
//        SvgModelContainer::ModelElement *element = &model->elements[elementIndex];
//        Ref<Mesh> borderMesh = element->transformedBorderMesh;
//        this->lineShader->bind();
//        this->lineShader->setGlobalFloat3("clientColor", glm::vec3(0.8f, 0.8f, 0.0f));
//        borderMesh->bind();
//        glDrawElements(GL_LINES, borderMesh->getVertexArray()->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
//        borderMesh->unbind();
//    }
//    if (this->gui->getModel()->drawBorders
//    {
//        printf("ONLINE\n");
//        Ref<Mesh> borderMesh = this->svgModelContainer.getModels().begin()->second.borderMesh;
//        this->lineShader->bind();
//        this->lineShader->setGlobalFloat3("clientColor", guiModel->borderColor);
//        borderMesh->bind();
//        glDrawElements(GL_LINES, borderMesh->getVertexArray()->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
//        borderMesh->unbind();
//    }
    this->framebufferForGui->unbind();

    this->renderLayerPreview();


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

SvgModelContainer *CustomState::getModelContainer() noexcept
{
    return &this->svgModelContainer;
}

void CustomState::renderLayerPreview() noexcept
{
    if (!this->gui->shouldBePreviewUpdated())
        return;
    Gui::Model *guiModel = this->gui->getModel();
    if (!this->gui->wasPreviewWindowSizeChanged() || this->previewLayerMesh == nullptr)
    {
        std::vector<VNfloat> modelVertices;
        if (guiModel->currentlySelectedItemType == Gui::SelectedTreeItem::Model)
        {
            VNuint modelIndex = guiModel->modelSelectedIndex;
            SvgModelContainer::Model *model = this->svgModelContainer.getModelByIndex(modelIndex);
            this->previewLayerMesh = model->borderMesh;
        }
        else if (guiModel->currentlySelectedItemType == Gui::SelectedTreeItem::Group)
        {
            VNuint modelIndex = guiModel->modelSelectedIndex;
            SvgModelContainer::Model *model = this->svgModelContainer.getModelByIndex(modelIndex);
            VNuint groupIndex = guiModel->groupSelectedIndex;
            SvgModelContainer::Group &group = model->groups[groupIndex];
            this->previewLayerMesh = group.borderMesh;
        }
        else if (guiModel->currentlySelectedItemType == Gui::SelectedTreeItem::KeyedElement)
        {
            VNuint modelIndex = guiModel->modelSelectedIndex;
            SvgModelContainer::Model *model = this->svgModelContainer.getModelByIndex(modelIndex);
            VNuint groupIndex = guiModel->groupSelectedIndex;
            SvgModelContainer::Group &group = model->groups[groupIndex];
            VNuint keyedElementIndex = guiModel->keyedElementSelectedIndex;
            SvgModelContainer::KeyedElement &keyedElement = group.keyedElements[keyedElementIndex];
            this->previewLayerMesh = keyedElement.borderMesh;
        }
        else if (guiModel->currentlySelectedItemType == Gui::SelectedTreeItem::Element)
        {
            VNuint modelIndex = guiModel->modelSelectedIndex;
            SvgModelContainer::Model *model = this->svgModelContainer.getModelByIndex(modelIndex);
            VNuint groupIndex = guiModel->groupSelectedIndex;
            SvgModelContainer::Group &group = model->groups[groupIndex];
            VNuint keyedElementIndex = guiModel->keyedElementSelectedIndex;
            SvgModelContainer::KeyedElement &keyedElement = group.keyedElements[keyedElementIndex];
            VNuint elementIndex = guiModel->elementSelectedIndex;
            SvgModelContainer::Element &element = keyedElement.keys[elementIndex];
            this->previewLayerMesh = element.borderMesh;
        }
    }

    if (this->gui->wasPreviewWindowSizeChanged())
    {
        glm::vec2 &previewLayerSize = guiModel->previewViewportSize;
        this->framebufferForLayerPreview->resize(previewLayerSize.x, previewLayerSize.y);
    }
    glm::vec2 previewLayerSize = this->gui->getModel()->previewViewportSize;
    glm::vec2 orthoDims = {previewLayerSize.x > previewLayerSize.y ? 1.0f : previewLayerSize.x / previewLayerSize.y,
                           previewLayerSize.y > previewLayerSize.x ? 1.0f : previewLayerSize.y / previewLayerSize.x};
    glm::mat4 ortho = glm::ortho(-orthoDims.x * 2.0f, orthoDims.x * 2.0f, -orthoDims.y * 2.0f, orthoDims.y * 2.0f, 0.1f, 10.0f);
    this->lineShader->bind();
    this->lineShader->setGlobalMat4("proj", ortho);
    this->lineShader->setGlobalFloat3("clientColor", glm::vec3(1.0f));
    this->previewLayerMesh->bind();
    this->framebufferForLayerPreview->bind();
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawElements(GL_LINES, this->previewLayerMesh->getVertexArray()->getIndexBuffer()->getCount(), GL_UNSIGNED_INT,
                   nullptr);
    this->framebufferForLayerPreview->unbind();
    this->previewLayerMesh->unbind();
}

void CustomState::updateModelPreview() noexcept
{
    this->shouldUpdateModelPreview = true;
}
