#pragma once

#include <functional>
#include <unordered_map>
#include <vector>

#include "event/Event.h"

namespace vanadium {

class Event;

class EventDispatcher {
  using EventFunction = std::function<void(Event *event)>;
  using SubscribersArray = std::vector<EventFunction>;
  using SubscribersMap = std::unordered_map<Event::Type, SubscribersArray>;

 private:
  SubscribersMap _subscribers;
  SubscribersArray _subscribersToAny;
  SubscribersMap _prioritySubscribers;
  SubscribersArray _prioritySubscribersToAny;

  void dispatchUsingInput(Event *event, SubscribersArray &any,
                          SubscribersMap &map) const {
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

 public:
  EventDispatcher() = default;

  void dispatch(Event *event) noexcept {
    this->dispatchUsingInput(event, this->_prioritySubscribersToAny,
                             this->_prioritySubscribers);

    this->dispatchUsingInput(event, this->_subscribersToAny,
                             this->_subscribers);
  }

  void subscribe(Event::Type eventType, EventFunction function) {
    if (eventType == Event::Type::Any) {
      this->_subscribersToAny.push_back(std::move(function));
      return;
    }

    if (this->_subscribers.find(eventType) == this->_subscribers.end()) {
      this->_subscribers[eventType] = SubscribersArray();
    }

    this->_subscribers[eventType].push_back(std::move(function));
  }

  void prioritySubscribe(Event::Type eventType, EventFunction function) {
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
};

}  // namespace vanadium
