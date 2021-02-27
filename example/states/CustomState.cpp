#include "CustomState.h"

void CustomState::setUpEvents() noexcept
{
    this->eventProvider->setEventCallback(
            [this](Event *event) { this->eventDispatcher.dispatch(event); }
    );
    this->eventDispatcher.subscribe(
            Event::Type::KeyPressed,
            [this](Event *event){ this->onKeyPressed((KeyPressedEvent *)event); }
    );
    this->eventDispatcher.subscribe(
            Event::Type::KeyReleased,
            [this](Event *event){ this->onKeyReleased((KeyReleasedEvent *)event); }
    );
    this->eventDispatcher.subscribe(
            Event::Type::WindowClose,
            [this](Event *event){ this->onWindowClose((WindowCloseEvent *)event); }
    );
    this->eventDispatcher.subscribe(
            Event::Type::MouseMove,
            [this](Event *event){ this->onMouseMove((MouseMoveEvent *)event); }
    );
    this->eventDispatcher.subscribe(
            Event::Type::WindowSizeChanged,
            [this](Event *event){ this->onWindowResized((WindowSizeChangedEvent *)event); }
    );
    this->eventDispatcher.subscribe(
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
    this->application = application;
    this->eventProvider = application->getEventProvider();
    this->stateStack = application->getStateStack();
    this->name = name;
    // Todo: think about event setup boilerplate.
    this->setUpEvents();

    this->shader = ShaderFactory::create("./shader.xml", "Plain");
}

void CustomState::onDetach()
{
    this->eventProvider->setEventCallback(nullptr);
}

void CustomState::onStateLostPriority()
{
    VAN_USER_INFO("{} lost priority on state queue!", this->getName());
}

void CustomState::onStateGainedPriority()
{
    VAN_USER_INFO("{} lost priority on state queue!", this->getName());
    // Todo: THIS IS NOT OK. Make Application class resubscribe states automatically.
    this->eventProvider->setEventCallback(
            [this](Event *event) { this->eventDispatcher.dispatch(event); }
    );
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
}

void CustomState::postRender()
{

}

const std::string &CustomState::getName() const noexcept
{
    return this->name;
}

//Ref<Framebuffer> CustomState::getTargetFramebuffer() const noexcept
//{
//    return nullptr;
//}
