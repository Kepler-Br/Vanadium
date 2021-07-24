#include "platform/default/DefaultEventProvider.h"

#include "event/KeyEvent.h"
#include "event/MouseEvent.h"
#include "event/WindowEvent.h"
#include "platform/default/DefaultIncludes.h"

namespace vanadium {

DefaultEventProvider::DefaultEventProvider(Window *window)
    : EventProvider(window) {
  this->_eventQueue.reserve(255);
  this->_currentKeyState = SDL_GetKeyboardState(nullptr);
  // SDL_NUM_SCANCODES is total scancodes available.
  this->_previousKeyState = new uint8_t[SDL_NUM_SCANCODES];
}

DefaultEventProvider::~DefaultEventProvider() {
  delete[] this->_previousKeyState;
}

void DefaultEventProvider::update() noexcept {
  SDL_Event event;

  std::memcpy(this->_previousKeyState, this->_currentKeyState,
              SDL_NUM_SCANCODES);
  this->_mousePrevPosition = this->_mousePosition;
  this->_prevMouseButtonMask = this->_mouseButtonMask;
  this->_mouseButtonMask =
      SDL_GetMouseState(&this->_mousePosition.x, &this->_mousePosition.y);
  this->_mouseDelta = this->_mousePosition - this->_mousePrevPosition;
  // Flush all events if callback function was not set.
  if (!this->_eventCallback) {
    SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
    return;
  }
  while (SDL_PollEvent(&event)) {
    // SDL key scancode and Vanadium KeyCode are interchangeable in default
    // platform realisation. Kinda.
    switch (event.type) {
      case SDL_QUIT:
        this->_eventQueue.push_back(
            new WindowCloseEvent(&event, sizeof(event)));
        break;
      case SDL_MOUSEMOTION:
        this->_eventQueue.push_back(new MouseMoveEvent(
            event.motion.x, event.motion.y, event.motion.xrel,
            event.motion.yrel, &event, sizeof(event)));
        break;
      case SDL_KEYDOWN:
        this->_eventQueue.push_back(
            new KeyPressedEvent((keyboard::KeyCode)event.key.keysym.scancode,
                                &event, sizeof(event)));
        break;
      case SDL_KEYUP:
        this->_eventQueue.push_back(
            new KeyReleasedEvent((keyboard::KeyCode)event.key.keysym.scancode,
                                 &event, sizeof(event)));
        break;
      case SDL_MOUSEBUTTONDOWN:
        this->_eventQueue.push_back(new MouseButtonPressedEvent(
            mouse::fromInt(event.button.button), &event, sizeof(event)));
        break;
      case SDL_MOUSEBUTTONUP:
        this->_eventQueue.push_back(new MouseButtonReleasedEvent(
            mouse::fromInt(event.button.button), &event, sizeof(event)));
        break;
      case SDL_MOUSEWHEEL:
        this->_eventQueue.push_back(new MouseScrollEvent(
            event.wheel.y, event.wheel.x, &event, sizeof(event)));
        break;
      case SDL_WINDOWEVENT:
        switch (event.window.event) {
          case SDL_WINDOWEVENT_RESIZED:
            this->_eventQueue.push_back(new WindowResizedEvent(
                (uint)event.window.data1, (uint)event.window.data2, &event,
                sizeof(event)));
            break;
          case SDL_WINDOWEVENT_FOCUS_GAINED:
            this->_eventQueue.push_back(
                new WindowFocusGainEvent(&event, sizeof(event)));
            break;
          case SDL_WINDOWEVENT_FOCUS_LOST:
            this->_eventQueue.push_back(
                new WindowFocusLostEvent(&event, sizeof(event)));
            break;
        }
        break;
    }
  }
}

void DefaultEventProvider::dispatch() noexcept {
  if (!this->_eventCallback) {
    this->_eventQueue.clear();
    return;
  }
  for (auto *event : this->_eventQueue) {
    this->_eventCallback(event);
    delete event;
  }
  this->_eventQueue.clear();
}

bool DefaultEventProvider::isKeyPressed(
    keyboard::KeyCode keycode) const noexcept {
  return this->_currentKeyState[(uint16_t)keycode];
}

bool DefaultEventProvider::isKeyReleased(
    keyboard::KeyCode keycode) const noexcept {
  return !this->_currentKeyState[(uint16_t)keycode];
}

bool DefaultEventProvider::isKeyJustPressed(
    keyboard::KeyCode keycode) const noexcept {
  return this->_currentKeyState[(uint16_t)keycode] &&
         !this->_previousKeyState[(uint16_t)keycode];
}

bool DefaultEventProvider::isKeyJustReleased(
    keyboard::KeyCode keycode) const noexcept {
  return !this->_currentKeyState[(uint16_t)keycode] &&
         this->_previousKeyState[(uint16_t)keycode];
}

bool DefaultEventProvider::isMousePressed(
    mouse::KeyCode keycode) const noexcept {
  return (bool)(SDL_BUTTON((uint16_t)keycode) & this->_mouseButtonMask);
}

bool DefaultEventProvider::isMouseReleased(
    mouse::KeyCode keycode) const noexcept {
  return !(SDL_BUTTON((uint16_t)keycode) & this->_mouseButtonMask);
}

bool DefaultEventProvider::isMouseJustPressed(
    mouse::KeyCode keycode) const noexcept {
  return (SDL_BUTTON((uint16_t)keycode) & this->_mouseButtonMask) &&
         !(SDL_BUTTON((uint16_t)keycode) & this->_prevMouseButtonMask);
}

bool DefaultEventProvider::isMouseJustReleased(
    mouse::KeyCode keycode) const noexcept {
  return !(SDL_BUTTON((uint16_t)keycode) & this->_mouseButtonMask) &&
         (SDL_BUTTON((uint16_t)keycode) & this->_prevMouseButtonMask);
}

glm::ivec2 DefaultEventProvider::getMouseDelta() const noexcept {
  return this->_mouseDelta;
}

glm::ivec2 DefaultEventProvider::getMousePosition() const noexcept {
  glm::ivec2 mousePosition;

  SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
  return mousePosition;
}

}  // namespace vanadium