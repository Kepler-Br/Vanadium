#include "DefaultEventProvider.h"
#include "../../event/WindowEvent.h"
#include "../../event/MouseEvent.h"
#include "../../event/KeyEvent.h"
#include "DefaultIncludes.h"

namespace Vanadium
{

DefaultEventProvider::DefaultEventProvider(Window *window) :
        EventProvider(window)
{
    this->eventQueue.reserve(255);
    this->currentKeyState = SDL_GetKeyboardState(nullptr);
    // SDL_NUM_SCANCODES is total scancodes available.
    this->previousKeyState = new uint8_t[SDL_NUM_SCANCODES];
}

DefaultEventProvider::~DefaultEventProvider()
{
    delete[] this->previousKeyState;
}

void DefaultEventProvider::update() noexcept
{
    SDL_Event event;

    std::memcpy(this->previousKeyState, this->currentKeyState, SDL_NUM_SCANCODES);
    this->mousePrevPosition = this->mousePosition;
    this->prevMouseButtonMask = this->mouseButtonMask;
    this->mouseButtonMask = SDL_GetMouseState(&this->mousePosition.x, &this->mousePosition.y);
    this->mouseDelta = this->mousePosition - this->mousePrevPosition;
    // Flush all events if callback function was not set.
    if (!this->eventCallback)
    {
        SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
        return;
    }
    while (SDL_PollEvent(&event))
    {
        // SDL key scancode and Vanadium KeyCode are interchangeable in default platform realisation. Kinda.
        switch (event.type)
        {
            case SDL_QUIT:
                this->eventQueue.push_back(new WindowCloseEvent(&event, sizeof(event)));
                break;
            case SDL_MOUSEMOTION:
                this->eventQueue.push_back(new MouseMoveEvent(
                        event.motion.x, event.motion.y,
                        event.motion.xrel, event.motion.yrel,
                        &event, sizeof(event)
                        ));
                break;
            case SDL_KEYDOWN:
                this->eventQueue.push_back(new KeyPressedEvent((Keyboard::KeyCode)event.key.keysym.scancode, &event, sizeof(event)));
                break;
            case SDL_KEYUP:
                this->eventQueue.push_back(new KeyReleasedEvent((Keyboard::KeyCode)event.key.keysym.scancode, &event, sizeof(event)));
                break;
            case SDL_MOUSEBUTTONDOWN:
                this->eventQueue.push_back(new MouseButtonPressedEvent((uint16_t)event.button.button, &event, sizeof(event)));
                break;
            case SDL_MOUSEBUTTONUP:
                this->eventQueue.push_back(new MouseButtonReleasedEvent((uint16_t)event.button.button, &event, sizeof(event)));
                break;
            case SDL_MOUSEWHEEL:
                this->eventQueue.push_back(new MouseScrollEvent(event.wheel.y, event.wheel.x, &event, sizeof(event)));
                break;
            case SDL_WINDOWEVENT:
                switch (event.window.event)
                {
                    case SDL_WINDOWEVENT_RESIZED:
                        this->eventQueue.push_back(new WindowSizeChangedEvent((VNsize)event.window.data1, (VNsize)event.window.data2, &event, sizeof(event)));
                        break;
                    case SDL_WINDOWEVENT_FOCUS_GAINED:
                        this->eventQueue.push_back(new WindowFocusGainEvent(&event, sizeof(event)));
                        break;
                    case SDL_WINDOWEVENT_FOCUS_LOST:
                        this->eventQueue.push_back(new WindowFocusLostEvent(&event, sizeof(event)));
                        break;
                }
                break;
        }
    }
}

void DefaultEventProvider::dispatch() noexcept
{
    if (!this->eventCallback)
    {
        this->eventQueue.clear();
        return;
    }
    for (auto *event : this->eventQueue)
    {
        this->eventCallback(event);
        delete event;
    }
    this->eventQueue.clear();
}

bool DefaultEventProvider::isKeyPressed(Keyboard::KeyCode keycode) const noexcept
{
    return this->currentKeyState[(uint16_t)keycode];
}

bool DefaultEventProvider::isKeyReleased(Keyboard::KeyCode keycode) const noexcept
{
    return !this->currentKeyState[(uint16_t)keycode];
}

bool DefaultEventProvider::isKeyJustPressed(Keyboard::KeyCode keycode) const noexcept
{
    return this->currentKeyState[(uint16_t)keycode] && !this->previousKeyState[(uint16_t)keycode];
}

bool DefaultEventProvider::isKeyJustReleased(Keyboard::KeyCode keycode) const noexcept
{
    return !this->currentKeyState[(uint16_t)keycode] && this->previousKeyState[(uint16_t)keycode];
}

bool DefaultEventProvider::isMousePressed(Mouse::KeyCode keycode) const noexcept
{
    return (bool)(SDL_BUTTON((uint16_t)keycode) & this->mouseButtonMask);
}

bool DefaultEventProvider::isMouseReleased(Mouse::KeyCode keycode) const noexcept
{
    return !(SDL_BUTTON((uint16_t)keycode) & this->mouseButtonMask);
}

bool DefaultEventProvider::isMouseJustPressed(Mouse::KeyCode keycode) const noexcept
{
    return  (SDL_BUTTON((uint16_t)keycode) & this->mouseButtonMask) &&
            !(SDL_BUTTON((uint16_t)keycode) & this->prevMouseButtonMask);
}

bool DefaultEventProvider::isMouseJustReleased(Mouse::KeyCode keycode) const noexcept
{
    return !(SDL_BUTTON((uint16_t)keycode) & this->mouseButtonMask) &&
           (SDL_BUTTON((uint16_t)keycode) & this->prevMouseButtonMask);
}

glm::ivec2 DefaultEventProvider::getMouseDelta() const noexcept
{
    return this->mouseDelta;
}

glm::ivec2 DefaultEventProvider::getMousePosition() const noexcept
{
    glm::ivec2 mousePosition;

    SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
    return mousePosition;
}

}