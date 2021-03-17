#include "CustomState.h"
#define EVENT_SUBSCRIBE(memberFunction, eventType) [this](Event *event){ memberFunction((eventType *)event); }
// Todo: remove this:
#include "../../vanadium/src/platform/opengl/OpenGLFramebuffer.h"
#include "gui/Gui.h"

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
    this->gui->mouseDelta = {(float)event->getDelta().x, (float)event->getDelta().y};
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



    size_t id;
    // Create models.
//    std::string newModelName = "Test model 1";
    id = this->svgModelContainer.addModel();
    if (id == 0)
    {
        std::stringstream msg;
        throw ExecutionInterrupted(
                this->svgModelContainer.getErrorString()
        );
    }

    // Add groups to models.
//    std::string newGroupName = "Test group 1";
    id = this->svgModelContainer.addGroup(id);
    if(id == 0)
    {
        std::stringstream msg;
        throw ExecutionInterrupted(
                this->svgModelContainer.getErrorString()
        );
    }

    // Add keyed elements to groups.
    id = this->svgModelContainer.addKeyedElement(id);
    if(id == 0)
    {
        std::stringstream msg;
        throw ExecutionInterrupted(
                this->svgModelContainer.getErrorString()
        );
    }

    // Add elements to keyed elements.
    size_t elementID;
    elementID = this->svgModelContainer.addKey(id, "./resources/svgs/helloworld.svg", "layer1");
    if(!elementID)
    {
        std::stringstream msg;
        throw ExecutionInterrupted(
                this->svgModelContainer.getErrorString()
        );
    }

    elementID = this->svgModelContainer.addKey(id, "./resources/svgs/helloworld2.svg", "layer1");
    if(!elementID)
    {
        std::stringstream msg;
        throw ExecutionInterrupted(
                this->svgModelContainer.getErrorString()
        );
    }
    elementID = this->svgModelContainer.addKey(id, "./resources/svgs/helloworld3.svg", "layer1");
    if(!elementID)
    {
        std::stringstream msg;
        throw ExecutionInterrupted(
                this->svgModelContainer.getErrorString()
        );
    }








    id = this->svgModelContainer.addModel();
    if (id == 0)
    {
        std::stringstream msg;
        throw ExecutionInterrupted(
                this->svgModelContainer.getErrorString()
        );
    }

    // Add groups to models.
//    std::string newGroupName = "Test group 1";
    id = this->svgModelContainer.addGroup(id);
    if(id == 0)
    {
        std::stringstream msg;
        throw ExecutionInterrupted(
                this->svgModelContainer.getErrorString()
        );
    }

    // Add keyed elements to groups.
    id = this->svgModelContainer.addKeyedElement(id);
    if(id == 0)
    {
        std::stringstream msg;
        throw ExecutionInterrupted(
                this->svgModelContainer.getErrorString()
        );
    }

    // Add elements to keyed elements.
    elementID = this->svgModelContainer.addKey(id, "./resources/svgs/helloworld.svg", "layer1");
    if(!elementID)
    {
        std::stringstream msg;
        throw ExecutionInterrupted(
                this->svgModelContainer.getErrorString()
        );
    }
    elementID = this->svgModelContainer.addKey(id, "./resources/svgs/helloworld2.svg", "layer1");
    if(!elementID)
    {
        std::stringstream msg;
        throw ExecutionInterrupted(
                this->svgModelContainer.getErrorString()
        );
    }
    elementID = this->svgModelContainer.addKey(id, "./resources/svgs/helloworld3.svg", "layer1");
    if(!elementID)
    {
        std::stringstream msg;
        throw ExecutionInterrupted(
                this->svgModelContainer.getErrorString()
        );
    }


    this->svgModelContainer.update(1.0f);
}

void CustomState::drawArrows(const glm::vec2 &position, const glm::mat2 &transMatrix)
{
    this->plainColor2D->bind();
    this->plainColor2D->setGlobalMat4("proj", this->guiViewportCamera->getVP());
    this->plainColor2D->setGlobalMat2("model", transMatrix);
    this->plainColor2D->setGlobalFloat2("position", position);
    this->plainColor2D->setGlobalFloat4("clientColor", glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
    RenderApi::instance()->drawMesh(this->arrow);
    glm::mat2 localRotation = {glm::cos(glm::radians(-90.0f)), glm::sin(glm::radians(-90.0f)),
                               -glm::sin(glm::radians(-90.0f)), glm::cos(glm::radians(-90.0f))};
    this->plainColor2D->setGlobalMat2("model", transMatrix * localRotation);
    this->plainColor2D->setGlobalFloat4("clientColor", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    RenderApi::instance()->drawMesh(this->arrow);
}

void CustomState::drawCircle(const glm::vec2 &position)
{
    this->plainColor2D->bind();
    this->plainColor2D->setGlobalMat4("proj", this->guiViewportCamera->getVP());
    this->plainColor2D->setGlobalMat2("model", glm::mat2(1.0f));
    this->plainColor2D->setGlobalFloat2("position", position);
    this->plainColor2D->setGlobalFloat4("clientColor", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    RenderApi::instance()->drawMesh(this->modelCenter);
}

void CustomState::renderSelected()
{
    Gui::Model *guiModel = this->gui->getModel();
    for (size_t selectedID : guiModel->selectedModels)
    {
        Ref<SvgModel::Object> object = this->svgModelContainer.getObject(selectedID);
        if (object == nullptr)
        {
            VAN_USER_ERROR("CustomState::renderSelected: invalid selected ID!");
            continue;
        }
        if (object->getType() == SvgModel::ModelType::Model)
        {
            this->drawModelWireframe(selectedID);
        }
        if (object->getType() == SvgModel::ModelType::Group)
        {
            this->drawGroupWireframe(selectedID);
        }
        if (object->getType() == SvgModel::ModelType::KeyedElement)
        {
            this->drawKeyElementWireframe(selectedID);
        }
        if (object->getType() == SvgModel::ModelType::Key)
        {
            this->drawKeyWireframe(selectedID);
        }
    }
}

void CustomState::renderMarkedWireframeModels()
{
    auto &container = this->svgModelContainer;
    glm::vec4 color = {this->gui->getModel()->wireframeColor.x,
                       this->gui->getModel()->wireframeColor.y,
                       this->gui->getModel()->wireframeColor.z,
                       1.0f};
    for (size_t modelID : container.getModelsIDs())
    {
        Ref<SvgModel::Model> model = container.getModel(modelID);
        if (model == nullptr)
        {
            continue;
        }
        for (size_t groupID : model->groupsIDs)
        {
            Ref<SvgModel::Group> group = container.getGroup(groupID);
            if (group == nullptr)
            {
                continue;
            }
            if (!(model->drawAsWireframe || this->gui->getModel()->drawWireframes ||
                  this->gui->getModel()->drawWireframeOnly || group->drawAsWireframe) ||
                group->disabled || model->disabled || group->isPatch)
            {
                continue;
            }
            if (!this->gui->getModel()->overrideWireframeColor)
            {
                color = {group->wireframeColor.x,
                         group->wireframeColor.y,
                         group->wireframeColor.z,
                         1.0f};
            }
            this->drawGroupWireframe(groupID, color, false);
        }
    }
}

void CustomState::renderPatches(int layerNumber, bool affectAura, bool affectBodyColor)
{
    Gui::Model *guiModel = this->gui->getModel();
    if (!affectAura && !affectBodyColor)
    {
        return;
    }
    this->plainColor2D->bind();
    this->plainColor2D->setGlobalMat4("proj", this->guiViewportCamera->getVP());
    if (guiModel->drawWireframeOnly)
    {
        return;
    }
    glm::vec4 color;
    if (affectAura)
    {
        color = {guiModel->auraColor.x,
                 guiModel->auraColor.y,
                 guiModel->auraColor.z,
                 1.0f};
    }
    else if (affectBodyColor)
    {
        color = {guiModel->bodyColor.x,
                 guiModel->bodyColor.y,
                 guiModel->bodyColor.z,
                 1.0f};
    }
    for (size_t modelID : this->svgModelContainer.getModelsIDs())
    {
        Ref<SvgModel::Model> model = this->svgModelContainer.getModel(modelID);
        if (model == nullptr ||
            model->drawAsWireframe ||
            this->gui->getModel()->drawWireframeOnly ||
            model->disabled)
        {
            continue;
        }
        for (size_t groupID : model->groupsIDs)
        {
            Ref<SvgModel::Group> group = this->svgModelContainer.getGroup(groupID);
            if (group == nullptr ||
                group->drawAsWireframe ||
                group->disabled ||
                !group->isPatch ||
                group->drawLayer != layerNumber ||
                group->triangulatedMesh == nullptr)
            {
                continue;
            }
            if (!(group->affectAura && affectAura || group->affectBodyColor && affectBodyColor))
            {
                continue;
            }
            if (affectAura && !guiModel->overrideAuraColor)
            {
                color = {group->auraColor.x,
                         group->auraColor.y,
                         group->auraColor.z,
                         1.0f};
            }
            else if (affectBodyColor && !guiModel->overrideBodyColor)
            {
                color = {group->bodyColor.x,
                         group->bodyColor.y,
                         group->bodyColor.z,
                         1.0f};
            }
            this->plainColor2D->setGlobalFloat4("clientColor", color);
            glm::mat2 transformationMatrix = group->rotationMatrix * model->rotationMatrix * group->scaleMatrix * model->scaleMatrix;
            this->plainColor2D->setGlobalMat2("model", transformationMatrix);
            this->plainColor2D->setGlobalFloat2("position", model->rotationMatrix * group->position + model->position);
            RenderApi::instance()->drawMesh(group->triangulatedMesh);
        }
    }
}

void CustomState::renderBlur(int layerNumber)
{
    Gui::Model *guiModel = this->gui->getModel();
    this->plainColor2D->bind();
    this->plainColor2D->setGlobalMat4("proj", this->guiViewportCamera->getVP());
    if (guiModel->drawBlur)
    {
        for (size_t modelID : this->svgModelContainer.getModelsIDs())
        {
            Ref<SvgModel::Model> model = this->svgModelContainer.getModel(modelID);
            if (model == nullptr ||
                model->drawAsWireframe ||
                this->gui->getModel()->drawWireframeOnly ||
                model->disabled)
            {
                continue;
            }
            glm::vec4 color = {this->gui->getModel()->auraColor.x,
                               this->gui->getModel()->auraColor.y,
                               this->gui->getModel()->auraColor.z,
                               1.0f};
            this->plainColor2D->setGlobalFloat4("clientColor", color);
            for (size_t groupID : model->groupsIDs)
            {
                Ref<SvgModel::Group> group = this->svgModelContainer.getGroup(groupID);
                if (group == nullptr ||
                    group->drawAsWireframe ||
                    group->disabled ||
                    group->isPatch ||
                    group->drawLayer != layerNumber ||
                    group->triangulatedMesh == nullptr)
                {
                    continue;
                }
                if (!this->gui->getModel()->overrideAuraColor)
                {
                    color = {group->auraColor.x,
                             group->auraColor.y,
                             group->auraColor.z,
                             1.0f};
                    this->plainColor2D->setGlobalFloat4("clientColor", color);
                }
                glm::mat2 transformationMatrix = group->rotationMatrix * model->rotationMatrix * group->scaleMatrix * model->scaleMatrix;
                this->plainColor2D->setGlobalMat2("model", transformationMatrix);
                this->plainColor2D->setGlobalFloat2("position", model->position + model->rotationMatrix * group->position);
                RenderApi::instance()->drawMesh(group->triangulatedMesh);
            }
        }
    }
}

void CustomState::renderBodies(int layerNumber)
{
    Gui::Model *guiModel = this->gui->getModel();
    this->plainColor2D->bind();
    this->plainColor2D->setGlobalMat4("proj", this->guiViewportCamera->getVP());
    if (guiModel->drawWireframeOnly)
    {
        return;
    }
    for (size_t modelID : this->svgModelContainer.getModelsIDs())
    {
        Ref<SvgModel::Model> model = this->svgModelContainer.getModel(modelID);
        if (model == nullptr ||
            model->drawAsWireframe ||
            this->gui->getModel()->drawWireframeOnly ||
            model->disabled)
        {
            continue;
        }
        glm::vec4 color = {this->gui->getModel()->bodyColor.x,
                           this->gui->getModel()->bodyColor.y,
                           this->gui->getModel()->bodyColor.z,
                           1.0f};
        this->plainColor2D->setGlobalFloat4("clientColor", color);
        for (size_t groupID : model->groupsIDs)
        {
            Ref<SvgModel::Group> group = this->svgModelContainer.getGroup(groupID);
            if (group == nullptr ||
                group->drawAsWireframe ||
                group->disabled ||
                group->isPatch ||
                group->drawLayer != layerNumber ||
                group->triangulatedMesh == nullptr)
            {
                continue;
            }
            if (!this->gui->getModel()->overrideBodyColor)
            {
                color = {group->bodyColor.x,
                         group->bodyColor.y,
                         group->bodyColor.z,
                         1.0f};
                this->plainColor2D->setGlobalFloat4("clientColor", color);
            }
            Ref<SvgModel::KeyedElement> kkk = this->svgModelContainer.getKeyedElement(group->keyedElementsIDs[0]);
            glm::mat2 transformationMatrix = kkk->rotationMatrix * group->rotationMatrix * model->rotationMatrix * group->scaleMatrix * model->scaleMatrix * kkk->scaleMatrix;
            this->plainColor2D->setGlobalMat2("model", transformationMatrix);
            this->plainColor2D->setGlobalFloat2("position",kkk->rotationMatrix *  model->rotationMatrix * group->position + model->position);
            RenderApi::instance()->drawMesh(group->triangulatedMesh);
        }
    }
}

void CustomState::renderModels()
{
    Gui::Model *guiModel = this->gui->getModel();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    this->framebufferMain->bind();
    glClear(GL_COLOR_BUFFER_BIT);
    this->framebufferMain->unbind();

    this->blurPostProcessing->bind();
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_STENCIL_TEST);
    for (VNint layerNumber = 0; layerNumber < this->svgModelContainer.getTotalLayers(); layerNumber++)
    {
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
        glStencilFunc(GL_ALWAYS, 1, 0xFF); // all fragments should pass the stencil test
        glStencilMask(0xFF);  // enable writing to the stencil buffer
        this->renderBlur(layerNumber);
        glStencilFunc(GL_EQUAL, 1, 0xFF);
        glStencilMask(0x00); // disable writing to the stencil buffer
        if (!guiModel->overrideAuraColor)
        {
            this->renderPatches(layerNumber, true, false);
        }
    }
    glStencilMask(0xFF);
    glClear(GL_STENCIL_BUFFER_BIT);
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilMask(0x00);
    this->blurPostProcessing->unbind();



    this->framebufferMain->bind();
    this->plainColor2D->bind();
    this->plainColor2D->setGlobalMat4("proj", this->guiViewportCamera->getVP());
    this->plainColor2D->setGlobalFloat4("clientColor", glm::vec4(1.0f, 1.0f, 1.0f, 0.6f));
    this->plainColor2D->setGlobalMat2("model", glm::mat2(1.0f));
    this->plainColor2D->setGlobalFloat2("position", glm::vec2(0.0f));
    RenderApi::instance()->drawMesh(this->grid);
    Ref<Shader> currentBlurShader = this->blurPostProcessing->getShader();
    currentBlurShader->bind();
    currentBlurShader->setGlobalFloat2("screenResolution", this->blurPostProcessing->getFramebuffer()->getGeometry());
    currentBlurShader->setGlobalFloat("power", guiModel->glowPower);
    this->blurPostProcessing->draw();
    this->framebufferMain->unbind();


    this->framebufferMain->bind();
    for (VNint layerNumber = 0; layerNumber < this->svgModelContainer.getTotalLayers(); layerNumber++)
    {
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
        glStencilFunc(GL_ALWAYS, 1, 0xFF); // all fragments should pass the stencil test
        glStencilMask(0xFF);  // enable writing to the stencil buffer
        this->renderBodies(layerNumber);
        glStencilFunc(GL_EQUAL, 1, 0xFF);
        glStencilMask(0x00); // disable writing to the stencil buffer
        if (!guiModel->overrideBodyColor)
        {
            this->renderPatches(layerNumber, false, true);
        }
    }
    glStencilMask(0xFF);
    glClear(GL_STENCIL_BUFFER_BIT);
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilMask(0x00);
    this->framebufferMain->unbind();

    this->framebufferMain->bind();
    this->renderSelected();
    this->framebufferMain->unbind();
}

void CustomState::drawModelWireframe(size_t id, const glm::vec4 &color, bool drawArrows)
{
    Ref<SvgModel::Model> modelObject = this->svgModelContainer.getModel(id);
    if (modelObject == nullptr)
    {
        return;
    }
    glm::vec2 rotatedKeyPosition = modelObject->position;
    if (drawArrows)
    {
        this->drawArrows(rotatedKeyPosition, glm::mat2(1.0f));
        this->drawCircle(glm::vec2(0.0f));
    }
    for (size_t groupID : modelObject->groupsIDs)
    {
        Ref<SvgModel::Group> object = this->svgModelContainer.getGroup(groupID);
        if (object == nullptr)
        {
            VAN_USER_ERROR("CustomState::renderSelected: invalid ID in model container!");
            continue;
        }
        this->drawGroupWireframe(groupID, color, false);
    }
}

void CustomState::drawGroupWireframe(size_t id, const glm::vec4 &color, bool drawArrows)
{
    Ref<SvgModel::Group> groupObject = this->svgModelContainer.getGroup(id);
    if (groupObject == nullptr)
    {
        return;
    }
    Ref<SvgModel::Model> modelObject = this->svgModelContainer.getModel(groupObject->parentID);
    if (modelObject == nullptr)
    {
        VAN_USER_ERROR("CustomState::drawGroupWireframe: invalid ID in group parent!");
        return;
    }
    glm::vec2 position = modelObject->position;
    glm::vec2 rotatedKeyPosition = modelObject->rotationMatrix * modelObject->scaleMatrix * groupObject->position;

    if (drawArrows)
    {

        this->drawArrows(position + rotatedKeyPosition, modelObject->rotationMatrix);
        this->drawCircle(position);
    }
    if (groupObject->borderMesh == nullptr)
    {
        return;
    }
    this->plainColor2D->bind();
    glm::mat2 transformationMatrix = groupObject->rotationMatrix * modelObject->rotationMatrix * groupObject->scaleMatrix * modelObject->scaleMatrix;
    this->plainColor2D->setGlobalMat4("proj", this->guiViewportCamera->getVP());
    this->plainColor2D->setGlobalMat2("model", transformationMatrix);
    this->plainColor2D->setGlobalFloat2("position", position + rotatedKeyPosition);
    this->plainColor2D->setGlobalFloat4("clientColor", color);
    RenderApi::instance()->drawMesh(groupObject->borderMesh);
}

void CustomState::drawKeyElementWireframe(size_t id, const glm::vec4 &color, bool drawArrows)
{
    Ref<SvgModel::KeyedElement> keyedElementObject = this->svgModelContainer.getKeyedElement(id);
    if (keyedElementObject == nullptr)
    {
        return;
    }
    Ref<SvgModel::Group> groupObject = this->svgModelContainer.getGroup(keyedElementObject->parentID);
    if (groupObject == nullptr)
    {
        VAN_USER_ERROR("CustomState::drawKeyElementWireframe: invalid ID in keyed element parent!");
        return;
    }
    Ref<SvgModel::Model> modelObject = this->svgModelContainer.getModel(groupObject->parentID);
    if (modelObject == nullptr)
    {
        VAN_USER_ERROR("CustomState::drawKeyElementWireframe: invalid ID in group parent!");
        return;
    }
    glm::vec2 position = modelObject->position + modelObject->rotationMatrix * groupObject->position;
    glm::vec2 rotatedKeyPosition = modelObject->rotationMatrix * groupObject->rotationMatrix * keyedElementObject->position;
    if (drawArrows)
    {
        this->drawArrows(position + rotatedKeyPosition, modelObject->rotationMatrix * groupObject->rotationMatrix);
        this->drawCircle(position);
    }
    if (keyedElementObject->borderMesh == nullptr)
    {
        return;
    }

    this->plainColor2D->bind();
    glm::mat2 transformationMatrix = modelObject->rotationMatrix * groupObject->rotationMatrix * keyedElementObject->rotationMatrix *
            modelObject->scaleMatrix * groupObject->scaleMatrix * keyedElementObject->scaleMatrix;
    this->plainColor2D->setGlobalMat4("proj", this->guiViewportCamera->getVP());
    this->plainColor2D->setGlobalMat2("model", transformationMatrix);
    this->plainColor2D->setGlobalFloat2("position", position + rotatedKeyPosition);
    this->plainColor2D->setGlobalFloat4("clientColor", color);
    RenderApi::instance()->drawMesh(keyedElementObject->borderMesh);
    for (size_t keyID : keyedElementObject->keysIDs)
    {
        this->drawKeyWireframe(keyID, color * 0.8f);
    }
}

void CustomState::drawKeyWireframe(size_t id, const glm::vec4 &color, bool drawArrows)
{
    Ref<SvgModel::Key> keyObject = this->svgModelContainer.getKey(id);
    if (keyObject == nullptr)
    {
        return;
    }
    Ref<SvgModel::KeyedElement> keyedElementObject = this->svgModelContainer.getKeyedElement(keyObject->parentID);
    if (keyedElementObject == nullptr)
    {
        return;
    }
    if (keyObject->borderMesh == nullptr)
    {
        return;
    }
    Ref<SvgModel::Group> groupObject = this->svgModelContainer.getGroup(keyedElementObject->parentID);
    if (groupObject == nullptr)
    {
        return;
    }
    Ref<SvgModel::Model> modelObject = this->svgModelContainer.getModel(groupObject->parentID);
    if (modelObject == nullptr)
    {
        return;
    }
//    glm::vec2 position = modelObject->position + modelObject->rotationMatrix * groupObject->position + modelObject->rotationMatrix * groupObject->rotationMatrix * keyedElementObject->position;
//    glm::vec2 rotatedKeyPosition = modelObject->rotationMatrix * groupObject->rotationMatrix * keyedElementObject->rotationMatrix * keyObject->position;
    glm::vec2 position = modelObject->position +
            modelObject->rotationMatrix * modelObject->scaleMatrix * groupObject->position +
            modelObject->rotationMatrix * groupObject->rotationMatrix * modelObject->scaleMatrix * groupObject->scaleMatrix * keyedElementObject->position;
    glm::vec2 rotatedKeyPosition = modelObject->rotationMatrix * groupObject->rotationMatrix * keyedElementObject->rotationMatrix * modelObject->scaleMatrix * groupObject->scaleMatrix * keyedElementObject->scaleMatrix * keyObject->position;

    if (drawArrows)
    {
        this->drawArrows(position + rotatedKeyPosition, modelObject->rotationMatrix * groupObject->rotationMatrix * keyedElementObject->rotationMatrix);
        this->drawCircle(position);
    }
    this->plainColor2D->bind();
    glm::mat2 transformationMatrix =
                                    modelObject->rotationMatrix*
                                    groupObject->rotationMatrix *
                                    keyedElementObject->rotationMatrix *
                                    keyObject->rotationMatrix *
                                    modelObject->scaleMatrix *
                                    groupObject->scaleMatrix *
                                    keyedElementObject->scaleMatrix *
                                    keyObject->scaleMatrix;
    this->plainColor2D->setGlobalMat4("proj", this->guiViewportCamera->getVP());
    this->plainColor2D->setGlobalMat2("model", transformationMatrix);
    this->plainColor2D->setGlobalFloat2("position", position + rotatedKeyPosition);
    this->plainColor2D->setGlobalFloat4("clientColor", color);
    RenderApi::instance()->drawMesh(keyObject->borderMesh);
}

void CustomState::onAttach(UserEndApplication *application, const std::string &name)
{
    // Todo: think about event setup boilerplate.
    this->setUpEvents();
    this->framebufferMain = FramebufferFactory::create({800, 600,
                                                        Framebuffer::AttachmentSpecification({Framebuffer::TextureFormat::Depth,
                                                                                                Framebuffer::TextureFormat::RGBA8,
                                                                                               }), 1, Texture::Filtering::Linear});
    if (this->framebufferMain == nullptr || !(*this->framebufferMain))
    {
        std::stringstream msg;
        throw ExecutionInterrupted(
                dynamic_cast<std::stringstream&>
                (msg << "Framebuffer foils.").str()
        );
    }
    this->framebufferPreview = FramebufferFactory::create({800, 600,
                                                           Framebuffer::AttachmentSpecification({Framebuffer::TextureFormat::Depth,
                                                                                                Framebuffer::TextureFormat::RGBA8,
                                                                                               }), 1, Texture::Filtering::Linear});
    if (this->framebufferPreview == nullptr || !(*this->framebufferPreview))
    {
        std::stringstream msg;
        throw ExecutionInterrupted(
                dynamic_cast<std::stringstream&>
                (msg << "Framebuffer foils.").str()
        );
    }

    this->framebuffer1 = FramebufferFactory::create({800, 600,
                                                     Framebuffer::AttachmentSpecification({Framebuffer::TextureFormat::Depth,
                                                                                                        Framebuffer::TextureFormat::RGBA8,
                                                                                                       }), 1, Texture::Filtering::Linear});
    if (this->framebuffer1 == nullptr || !(*this->framebuffer1))
    {
        std::stringstream msg;
        throw ExecutionInterrupted(
                dynamic_cast<std::stringstream&>
                (msg << "Framebuffer foils.").str()
        );
    }

    this->framebuffer2 = FramebufferFactory::create({800, 600,
                                                     Framebuffer::AttachmentSpecification({Framebuffer::TextureFormat::Depth,
                                                                                                         Framebuffer::TextureFormat::RGBA8,
                                                                                                        }), 1, Texture::Filtering::Linear});
    if (this->framebuffer2 == nullptr || !(*this->framebuffer2))
    {
        std::stringstream msg;
        throw ExecutionInterrupted(
                dynamic_cast<std::stringstream&>
                (msg << "Framebuffer foils.").str()
        );
    }

    this->unitWireframePlane = MeshFactory::unitWireframePlane(2.0f);
    this->modelCenter = MeshFactory::unitCircle(8, 0.03f);
    this->screenPlane = MeshFactory::unitPlane(2.0f);

    this->gui = MakeRef<Gui>(this->framebufferMain, this->framebufferPreview, this->application, this);

    this->guiViewportCamera = MakeRef<PositionCamera>(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    this->guiPreviewViewportCamera = MakeRef<PositionCamera>(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    this->texture = TextureFactory::create("textures/tex.png");
    if (!this->texture || !*this->texture)
    {
        std::stringstream msg;
        throw ExecutionInterrupted(
                dynamic_cast<std::stringstream&>
                (msg << "Texture not loaded: " << "textures/tex.png").str()
        );
    }

    this->plainColorShader = ShaderFactory::create("shaders/plainColor.xml", "Line shader");

    this->plainColor2D = ShaderFactory::create("shaders/plainColor2D.xml", "Plain color 2D");

    this->slowBlurShader = ShaderFactory::create("shaders/slowBlur.xml", "Blur shader");
    this->blurShader = ShaderFactory::create("shaders/blur.xml", "Blur shader");
    this->fastBlurShader = ShaderFactory::create("shaders/fastBlur.xml", "Fast blur shader");
    Ref<Shader> currentGlowShader;
    switch (this->gui->getModel()->blurQuality)
    {
        case (0):
            currentGlowShader = this->fastBlurShader;
            break;
        case (1):
            currentGlowShader = this->blurShader;
            break;
        case (2):
            currentGlowShader = this->slowBlurShader;
            break;
        default:
            currentGlowShader = this->fastBlurShader;
            break;
    }
    this->blurPostProcessing = PostprocessingFactory::create(currentGlowShader, this->window->getWidth(), this->window->getHeight());


    Stopwatch *stopwatch = Stopwatch::create();
    stopwatch->start();
    this->grid = MeshFactory::grid(2.0f, 2.0f/16.0f);
    this->arrow = MeshFactory::unitArrow(0.15f);

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
            if (Math::isEqual(this->gui->getModel()->interpolationSpeed, 1.0f, 0.01f))
            {
                this->svgModelContainer.update(1.0f, 0.001f);
            }
            else
            {
                this->svgModelContainer.update(40.0f * this->gui->getModel()->interpolationSpeed * (VNfloat)guiModel->skipSteps * deltatime, 0.001f);
            }
        }
    }
    else
    {
        this->svgModelContainer.setQuality(this->gui->getModel()->quality);
        if (Math::isEqual(this->gui->getModel()->interpolationSpeed, 1.0f, 0.01f))
        {
            this->svgModelContainer.update(1.0f, 0.001f);
        }
        else
        {
            this->svgModelContainer.update(40.0f * this->gui->getModel()->interpolationSpeed * deltatime, 0.001f);
        }
    }

    Ref<Shader> currentGlowShader;
    switch (this->gui->getModel()->blurQuality)
    {
        case (0):
            currentGlowShader = this->fastBlurShader;
            break;
        case (1):
            currentGlowShader = this->blurShader;
            break;
        case (2):
            currentGlowShader = this->slowBlurShader;
            break;
        default:
            currentGlowShader = this->fastBlurShader;
            break;
    }
    this->blurPostProcessing->setShader(currentGlowShader);
}

void CustomState::fixedUpdate(double deltatime)
{
//    if (this->guiModel.hueScrolling)
//    {
//        this->guiModel.glowHue += deltatime/10.0f;
//        this->guiModel.glowHue = this->guiModel.glowHue > 1.0f ? 0.0f : this->guiModel.glowHue;
//    }
    this->mainCameraScale = Math::lerpDelta(this->mainCameraScale, this->targetMainCameraScale, deltatime * 10.0f, 0.01f);
    this->previewCameraScale = Math::lerpDelta(this->previewCameraScale, this->targetPreviewCameraScale, deltatime * 10.0f, 0.01f);
    this->mainCameraPosition = Math::lerpDelta(this->mainCameraPosition, this->targetMainCameraPosition, deltatime * 15.0f, 0.01f);
}

void CustomState::preRender()
{
    RenderApi::instance()->clear();
}

void CustomState::render()
{
    if (!Math::isEqual(this->targetPreviewCameraScale, this->previewCameraScale, 0.01f))
    {
        const VNfloat scale = this->previewCameraScale;
        const glm::vec2 viewportSize = this->gui->getModel()->previewViewportSize;
        glm::vec2 orthoDims = {viewportSize.x / viewportSize.y,
                               viewportSize.y / viewportSize.x};
        VNfloat delta = 0.0f;
        if (orthoDims.x < 1.0f)
        {
            delta = 1.0f - orthoDims.x;
        }
        if (orthoDims.y < 1.0f)
        {
            delta = 1.0f - orthoDims.y;
        }
        orthoDims += delta;
        this->guiPreviewViewportCamera->setOrthographic(-orthoDims.x*scale, orthoDims.x*scale,
                                                 -orthoDims.y*scale, orthoDims.y*scale, 0.1f, 2.0f);
    }
    if (!Math::isEqual(this->mainCameraScale, this->targetMainCameraScale, 0.01f))
    {
        const VNfloat scale = this->mainCameraScale;
        const glm::vec2 viewportSize = this->gui->getModel()->renderViewportSize;
        glm::vec2 orthoDims = {viewportSize.x / viewportSize.y,
                               viewportSize.y / viewportSize.x};
        VNfloat delta = 0.0f;
        if (orthoDims.x < 1.0f)
        {
            delta = 1.0f - orthoDims.x;
        }
        if (orthoDims.y < 1.0f)
        {
            delta = 1.0f - orthoDims.y;
        }
        orthoDims += delta;
        this->guiViewportCamera->setOrthographic(-orthoDims.x*scale, orthoDims.x*scale,
                                                 -orthoDims.y*scale, orthoDims.y*scale, 0.1f, 2.0f);
    }
    if (!Math::isEqual(this->mainCameraPosition, this->targetMainCameraPosition, 0.01f))
    {
        const glm::vec3 &center = this->guiViewportCamera->getCenter();
        const glm::vec3 &position = this->guiViewportCamera->getPosition();
        const glm::vec3 &up = this->guiViewportCamera->getWorldUp();

        const glm::vec3 newPosition = {this->mainCameraPosition.x, this->mainCameraPosition.y, position.z};
        const glm::vec3 newCenter = {this->mainCameraPosition.x, this->mainCameraPosition.y, center.z};

        this->guiViewportCamera->lookAt(newPosition, newCenter , up);

    }
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

    glDisable(GL_DEPTH_TEST);

    this->gui->render();

    Gui::Model *guiModel = this->gui->getModel();
    this->blurPostProcessing->getFramebuffer()->resize(guiModel->renderViewportSize.x, guiModel->renderViewportSize.y);
    this->framebufferMain->resize(guiModel->renderViewportSize.x, guiModel->renderViewportSize.y);
    this->framebuffer1->resize(guiModel->renderViewportSize.x, guiModel->renderViewportSize.y);
    this->framebuffer2->resize(guiModel->renderViewportSize.x, guiModel->renderViewportSize.y);

    this->framebufferPreview->resize(guiModel->previewViewportSize.x, guiModel->previewViewportSize.y);
    this->renderModels();
//    this->framebufferMain->bind();
//    glClear(GL_COLOR_BUFFER_BIT);
//    this->renderSelected();
//    this->framebufferMain->unbind();
    this->renderPreview();



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

void CustomState::renderPreview() noexcept
{
//    Gui::Model *guiModel = this->gui->getModel();
//    Ref<Mesh> meshToRender;
//    if (guiModel->currentlySelectedItemType == Gui::SelectedTreeItem::Model)
//    {
//        VNuint modelIndex = guiModel->modelSelectedIndex;
//        SvgModelContainer::Model *model = this->svgModelContainer.getModelByIndex(modelIndex);
//        meshToRender = model->borderMesh;
//    }
//    else if (guiModel->currentlySelectedItemType == Gui::SelectedTreeItem::Group)
//    {
//        VNuint modelIndex = guiModel->modelSelectedIndex;
//        SvgModelContainer::Model *model = this->svgModelContainer.getModelByIndex(modelIndex);
//        VNuint groupIndex = guiModel->groupSelectedIndex;
//        SvgModelContainer::Group &group = model->groups[groupIndex];
//        meshToRender = group.borderMesh;
//    }
//    else if (guiModel->currentlySelectedItemType == Gui::SelectedTreeItem::KeyedElement)
//    {
//        VNuint modelIndex = guiModel->modelSelectedIndex;
//        SvgModelContainer::Model *model = this->svgModelContainer.getModelByIndex(modelIndex);
//        VNuint groupIndex = guiModel->groupSelectedIndex;
//        SvgModelContainer::Group &group = model->groups[groupIndex];
//        VNuint keyedElementIndex = guiModel->keyedElementSelectedIndex;
//        SvgModelContainer::KeyedElement &keyedElement = group.keyedElements[keyedElementIndex];
//        meshToRender = keyedElement.borderMesh;
//    }
//    else if (guiModel->currentlySelectedItemType == Gui::SelectedTreeItem::Element)
//    {
//        VNuint modelIndex = guiModel->modelSelectedIndex;
//        SvgModelContainer::Model *model = this->svgModelContainer.getModelByIndex(modelIndex);
//        VNuint groupIndex = guiModel->groupSelectedIndex;
//        SvgModelContainer::Group &group = model->groups[groupIndex];
//        VNuint keyedElementIndex = guiModel->keyedElementSelectedIndex;
//        SvgModelContainer::KeyedElement &keyedElement = group.keyedElements[keyedElementIndex];
//        VNuint elementIndex = guiModel->elementSelectedIndex;
//        SvgModelContainer::Element &element = keyedElement.keys[elementIndex];
//        meshToRender = element.borderMesh;
//    }
//    else
//    {
//        return;
//    }
//
//    this->plainColorShader->bind();
//    this->plainColorShader->setGlobalMat4("proj", this->guiPreviewViewportCamera->getVP());
//    this->plainColorShader->setGlobalFloat4("clientColor", glm::vec4(1.0f));
//    meshToRender->bind();
//    this->framebufferPreview->bind();
//    glClear(GL_COLOR_BUFFER_BIT);
//    glDrawElements(GL_LINES, meshToRender->getVertexArray()->getIndexBuffer()->getCount(), GL_UNSIGNED_INT,
//                   nullptr);
//    this->framebufferPreview->unbind();
//    meshToRender->unbind();
}

void CustomState::onGuiViewportSizeChange(const glm::vec2 &newViewportSize)
{
    const VNfloat scale = this->mainCameraScale;
    glm::vec2 orthoDims = {newViewportSize.x / newViewportSize.y,
                           newViewportSize.y / newViewportSize.x};
    VNfloat delta = 0.0f;
    if (orthoDims.x < 1.0f)
    {
        delta = 1.0f - orthoDims.x;
    }
    if (orthoDims.y < 1.0f)
    {
        delta = 1.0f - orthoDims.y;
    }
    orthoDims += delta;
    this->guiViewportCamera->setOrthographic(-orthoDims.x*scale, orthoDims.x*scale,
                                             -orthoDims.y*scale, orthoDims.y*scale, 0.1f, 2.0f);
}

void CustomState::onGuiPreviewViewportSizeChange(const glm::vec2 &newGeometry)
{
    const VNfloat scale = this->previewCameraScale;
    const glm::vec2 viewportSize = this->gui->getModel()->previewViewportSize;
    glm::vec2 orthoDims = {viewportSize.x / viewportSize.y,
                           viewportSize.y / viewportSize.x};
    VNfloat delta = 0.0f;
    if (orthoDims.x < 1.0f)
    {
        delta = 1.0f - orthoDims.x;
    }
    if (orthoDims.y < 1.0f)
    {
        delta = 1.0f - orthoDims.y;
    }
    orthoDims += delta;
    this->guiPreviewViewportCamera->setOrthographic(-orthoDims.x*scale, orthoDims.x*scale,
                                                    -orthoDims.y*scale, orthoDims.y*scale, 0.1f, 2.0f);
}


Ref<PositionCamera> CustomState::getPreviewCamera() noexcept
{
    return this->guiPreviewViewportCamera;
}

Ref<PositionCamera> CustomState::getMainRenderCamera() noexcept
{
    return this->guiViewportCamera;
}

void CustomState::setMainCameraScale(VNfloat scale)
{
    const VNfloat minScale = 0.01f;
    this->targetMainCameraScale = scale < minScale ? minScale : scale;
}

void CustomState::addMainCameraScale(VNfloat scale)
{
    const VNfloat minScale = 0.01f;
    this->targetMainCameraScale += scale;
    if (this->targetMainCameraScale < minScale)
    {
        this->targetMainCameraScale = minScale;
    }
}

VNfloat CustomState::getMainCameraScale()
{
    return this->targetMainCameraScale;
}

void CustomState::setPreviewCameraScale(VNfloat scale)
{
    const VNfloat minScale = 1.00f;
    this->targetPreviewCameraScale = scale < minScale ? minScale : scale;
}

void CustomState::addPreviewCameraScale(VNfloat scale)
{
    const VNfloat minScale = 1.00f;
    this->targetPreviewCameraScale += scale;
    if (this->targetPreviewCameraScale < minScale)
    {
        this->targetPreviewCameraScale = minScale;
    }
}

void CustomState::setMainCameraPosition(const glm::vec2 &newPosition)
{
    this->targetMainCameraPosition = newPosition;
}

void CustomState::addMainCameraPosition(const glm::vec2 &newPosition)
{
    this->targetMainCameraPosition += newPosition;
}
