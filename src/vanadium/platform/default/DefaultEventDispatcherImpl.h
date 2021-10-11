#pragma once

#include <functional>
#include <unordered_map>
#include <vector>

#include "vanadium/core/interfaces/constructed/EventDispatcher.h"
#include "vanadium/event/Event.h"

namespace vanadium {

class Event;

class DefaultEventDispatcherImpl : public EventDispatcher {
  using EventFunction = std::function<void(Event *event)>;
  using SubscribersArray = std::vector<EventFunction>;
  using SubscribersMap = std::unordered_map<Event::Type, SubscribersArray>;

 private:
  SubscribersMap _subscribers;
  SubscribersArray _subscribersToAny;
  SubscribersMap _prioritySubscribers;
  SubscribersArray _prioritySubscribersToAny;

  void dispatchUsingInput(Event *event, SubscribersArray &any,
                          SubscribersMap &map) const;

 public:
  DefaultEventDispatcherImpl() = default;

  void dispatch(Event *event) noexcept override;

  void subscribe(Event::Type eventType, EventFunction function) override;

  void prioritySubscribe(Event::Type eventType, EventFunction function) override;
};

}  // namespace vanadium
