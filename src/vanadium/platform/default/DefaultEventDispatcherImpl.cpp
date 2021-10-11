#include "DefaultEventDispatcherImpl.h"

namespace vanadium {

void DefaultEventDispatcherImpl::dispatchUsingInput(
    Event *event, DefaultEventDispatcherImpl::SubscribersArray &any,
    DefaultEventDispatcherImpl::SubscribersMap &map) const {
  if (event->isHandled()) {
    return;
  }

  for (const auto &subscriber : any) {
    subscriber(event);
    if (event->isHandled()) {
      return;
    }
  }

  if (map.find(event->getType()) == map.end()) {
    return;
  }

  const SubscribersArray &subscribersArray = map[event->getType()];

  for (const auto &subscriber : subscribersArray) {
    subscriber(event);
    if (event->isHandled()) return;
  }
}

void DefaultEventDispatcherImpl::dispatch(Event *event) noexcept {
  this->dispatchUsingInput(event, this->_prioritySubscribersToAny,
                           this->_prioritySubscribers);

  this->dispatchUsingInput(event, this->_subscribersToAny,
                           this->_subscribers);
}

void DefaultEventDispatcherImpl::subscribe(
    Event::Type eventType, DefaultEventDispatcherImpl::EventFunction function) {
  if (eventType == Event::Type::Any) {
    this->_subscribersToAny.push_back(std::move(function));
    return;
  }

  if (this->_subscribers.find(eventType) == this->_subscribers.end()) {
    this->_subscribers[eventType] = SubscribersArray();
  }

  this->_subscribers[eventType].push_back(std::move(function));
}

void DefaultEventDispatcherImpl::prioritySubscribe(
    Event::Type eventType, DefaultEventDispatcherImpl::EventFunction function) {
  if (eventType == Event::Type::Any) {
    this->_prioritySubscribersToAny.push_back(std::move(function));
    return;
  }

  if (this->_prioritySubscribers.find(eventType) ==
      this->_prioritySubscribers.end()) {
    this->_prioritySubscribers[eventType] = SubscribersArray();
  }

  this->_subscribers[eventType].push_back(std::move(function));
}

}
