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

    constexpr VNfloat one = 1.0f;
                                // First 4 are vertices, second 2 UVs.
    static VNfloat vboArray[] = {one, one, 0.0f, 1.0f, one, one,
                                 one, -one, 0.0f, 1.0f, one, 0.0f,
                                 -one, -one, 0.0f, 1.0f, 0.0f, 0.0f,
                                 -one, one, 0.0f, 1.0f, 0.0f, one,
    };
    auto ibo = IndexBufferFactory::create({0, 1, 2, 3});
    auto vbo = VertexBufferFactory::create(&vboArray, sizeof(vboArray));
    vbo->setLayout({{ DataTypes::Float4, "a_Position" }, { DataTypes::Float2, "a_UV" }});
    auto vao = VertexArrayFactory::create();
    vao->setIndexBuffer(ibo);
    vao->addVertexBuffer(vbo);

    this->mesh = MakeRef<Mesh>(vao);

    this->shader = ShaderFactory::create("shaders/plain.xml", "Plain");
    if (!this->shader || !*this->shader)
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
    this->shader->setGlobalMat4("model", glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)), glm::radians((float)this->application->getSecondsSinceStart()*100.0f), glm::vec3(1.0f, 1.0f, 1.0f)));
//    this->shader->setGlobalFloat2("iResolution", this->application->getWindow()->getGeometry());
//    this->shader->setGlobalFloat("iTime", (VNfloat)this->application->getSecondsSinceStart());
//    this->shader->setGlobalFloat("iFrame", (VNfloat)this->application->getDeltatime());
//    this->shader->setGlobalFloat2("iMouse", glm::vec2(1.0f));
//    this->vao->bind();
    this->texture->bind(0);
    this->mesh->bind();
    glDrawElements(GL_TRIANGLE_FAN, this->mesh->getVertexArray()->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
}

void CustomState::postRender()
{

}

const std::string &CustomState::getName() const noexcept
{
    return this->name;
}

