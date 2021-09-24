#pragma once

#include <functional>
#include <unordered_map>
#include <vector>

#include "event/Event.h"

namespace vanadium {

class EventDispatcher {
  using EventFunction = std::function<void(Event *event)>;
  using SubscribersArray = std::vector<EventFunction>;
  using SubscribersMap = std::unordered_map<Event::Type, SubscribersArray>;

 public:
  virtual ~EventDispatcher() = default;

  virtual void dispatch(Event *event) noexcept = 0;
  virtual void subscribe(Event::Type eventType, EventFunction function) = 0;
  virtual void prioritySubscribe(Event::Type eventType,
                                 EventFunction function) = 0;
};

}  // namespace vanadium
