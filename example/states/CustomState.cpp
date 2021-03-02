#include "CustomState.h"
#define EVENT_SUBSCRIBE(memberFunction, eventType) [this](Event *event){ memberFunction((eventType *)event); }


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
//    VAN_USER_INFO(event->toString());
}

void CustomState::onMouseMove(MouseMoveEvent *event) noexcept
{
//    VAN_USER_INFO(event->toString());
}

void CustomState::onMouseScroll(MouseScrollEvent *event) noexcept
{
//    VAN_USER_INFO(event->toString());
}

void CustomState::onAttach(UserEndApplication *application, const std::string &name)
{
    // Todo: think about event setup boilerplate.
    this->setUpEvents();

    static VNfloat one = 1.0f;
    static VNfloat vboArray[] = {one, one, 0.0f,
                                 one, -one, 0.0f,
                                 -one, -one, 0.0f,
                                 -one, one, 0.0f,
                                 };
    this->ibo = IndexBufferFactory::create({0, 1, 2, 3});
    this->vbo = VertexBufferFactory::create(&vboArray, sizeof(vboArray));
    this->vbo->setLayout({{ DataTypes::Float3, "a_Position" }});
    this->vao = VertexArrayFactory::create();
    this->vao->setIndexBuffer(this->ibo);
    this->vao->addVertexBuffer(this->vbo);

    this->shader = ShaderFactory::create("shaders/shader.xml", "Plain");
    if (!this->shader)
    {
        std::stringstream msg;
        throw ExecutionInterrupted(
                dynamic_cast<std::stringstream&>
                (msg << "Shader not loaded: " << "shaders/shader.xml").str()
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
    if (this->eventProvider->isKeyJustReleased(Keyboard::KeyCode::F))
    {
        this->window->setFullScreen(!this->window->isFullScreen());
    }
    if (this->eventProvider->isKeyJustReleased(Keyboard::KeyCode::Escape))
    {
        this->stateStack->requestPopAll();
    }
}

void CustomState::fixedUpdate(double deltatime)
{

}

void CustomState::preRender()
{

}

void CustomState::render()
{
    RenderApi::instance()->clear();
    this->shader->bind();
    this->shader->setGlobalFloat2("iResolution", this->application->getWindow()->getGeometry());
    this->shader->setGlobalFloat("iTime", (VNfloat)this->application->getSecondsSinceStart());
//    this->shader->setGlobalFloat("iFrame", (VNfloat)this->application->getDeltatime());
//    this->shader->setGlobalFloat2("iMouse", glm::vec2(1.0f));
    this->vao->bind();
    glDrawElements(GL_TRIANGLE_FAN, this->vao->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
}

void CustomState::postRender()
{
//    if (this->application->getTicksSinceStart() % 10 == 0)
//        VAN_USER_INFO("{} FPS.", (int)(1.0/this->application->getDeltatime()));
}

const std::string &CustomState::getName() const noexcept
{
    return this->name;
}

