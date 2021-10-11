#include "SdlEventProviderImpl.h"

#include "SdlIncludes.h"
#include "vanadium/core/interfaces/constructed/EventDispatcher.h"
#include "vanadium/event/KeyEvent.h"
#include "vanadium/event/MouseEvent.h"
#include "vanadium/event/WindowEvent.h"

namespace vanadium {

SdlEventProviderImpl::SdlEventProviderImpl(Ref<LoggerFactory> loggerFactory) {
  VAN_ENGINE_ASSERT((loggerFactory != nullptr), "loggerFactory is nullptr!");

  this->_eventQueue.reserve(255);
  this->_currentKeyState = SDL_GetKeyboardState(nullptr);
  // SDL_NUM_SCANCODES is total scancodes available.
  this->_previousKeyState =
      MakeUnique<std::array<uint8_t, SDL_NUM_SCANCODES>>();

  this->_logger = loggerFactory->construct("SdlEventProviderImpl");

  this->_logger->trace("Initialized");
}

SdlEventProviderImpl::~SdlEventProviderImpl() {
  this->_logger->trace("Destroyed");
}

#pragma region EventProvider

bool SdlEventProviderImpl::isKeyPressed(keyboard::KeyCode keycode) const {
  return this->_currentKeyState[(uint16_t)keycode];
}

bool SdlEventProviderImpl::isKeyReleased(keyboard::KeyCode keycode) const {
  return !this->_currentKeyState[(uint16_t)keycode];
}

bool SdlEventProviderImpl::isKeyJustPressed(keyboard::KeyCode keycode) const {
  return this->_currentKeyState[(uint16_t)keycode] &&
         !(*this->_previousKeyState)[(uint16_t)keycode];
}

bool SdlEventProviderImpl::isKeyJustReleased(keyboard::KeyCode keycode) const {
  return !this->_currentKeyState[(uint16_t)keycode] &&
         (*this->_previousKeyState)[(uint16_t)keycode];
}

bool SdlEventProviderImpl::isMousePressed(mouse::KeyCode keycode) const {
  return (bool)(SDL_BUTTON((uint16_t)keycode) & this->_mouseButtonMask);
}

bool SdlEventProviderImpl::isMouseReleased(mouse::KeyCode keycode) const {
  return !(SDL_BUTTON((uint16_t)keycode) & this->_mouseButtonMask);
}

bool SdlEventProviderImpl::isMouseJustPressed(mouse::KeyCode keycode) const {
  return (SDL_BUTTON((uint16_t)keycode) & this->_mouseButtonMask) &&
         !(SDL_BUTTON((uint16_t)keycode) & this->_prevMouseButtonMask);
}

bool SdlEventProviderImpl::isMouseJustReleased(mouse::KeyCode keycode) const {
  return !(SDL_BUTTON((uint16_t)keycode) & this->_mouseButtonMask) &&
         (SDL_BUTTON((uint16_t)keycode) & this->_prevMouseButtonMask);
}

glm::ivec2 SdlEventProviderImpl::getMouseDelta() const {
  return this->_mouseDelta;
}

glm::ivec2 SdlEventProviderImpl::getMousePosition() const {
  glm::ivec2 mousePosition;

  SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
  return mousePosition;
}

void SdlEventProviderImpl::setDispatcher(Ref<EventDispatcher> dispatcher) {
  this->_dispatcher = dispatcher;
}

#pragma endregion

#pragma region EngineEndEventProvider

void SdlEventProviderImpl::update() {
  SDL_Event event;

  std::memcpy(&this->_previousKeyState->back(), this->_currentKeyState,
              SDL_NUM_SCANCODES);
  this->_mousePrevPosition = this->_mousePosition;
  this->_prevMouseButtonMask = this->_mouseButtonMask;
  this->_mouseButtonMask =
      SDL_GetMouseState(&this->_mousePosition.x, &this->_mousePosition.y);
  this->_mouseDelta = this->_mousePosition - this->_mousePrevPosition;
  // Flush all events if callback function was not set.
  if (this->_dispatcher == nullptr) {
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
                (unsigned int)event.window.data1,
                (unsigned int)event.window.data2, &event, sizeof(event)));
            break;
          case SDL_WINDOWEVENT_FOCUS_GAINED:
            this->_eventQueue.push_back(
                new WindowFocusGainEvent(&event, sizeof(event)));
            break;
          case SDL_WINDOWEVENT_FOCUS_LOST:
            this->_eventQueue.push_back(
                new WindowFocusLostEvent(&event, sizeof(event)));
            break;
          default:
            break;
        }
        break;
      default:
        break;
    }
  }
}

void SdlEventProviderImpl::dispatch() {
  if (this->_dispatcher == nullptr) {
    for (auto *event : this->_eventQueue) {
      delete event;
    }
    this->_eventQueue.clear();
    return;
  }
  for (auto *event : this->_eventQueue) {
    this->_dispatcher->dispatch(event);

    delete event;
  }
  this->_eventQueue.clear();
}

#pragma endregion

}  // namespace vanadium
