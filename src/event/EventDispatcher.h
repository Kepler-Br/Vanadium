#ifndef VANADIUM_EVENTDISPATCHER_H
#define VANADIUM_EVENTDISPATCHER_H

#include "Event.h"
#include <functional>
#include <unordered_map>
#include <vector>

namespace Vanadium
{

class EventDispatcher
{
    using EventFunction = std::function<void(Event *event)>;
    using SubscribersArray = std::vector<EventFunction>;

private:
    std::unordered_map<EventType, SubscribersArray> subscribers;

public:
    EventDispatcher()
    {}

    void dispatch(Event &event) noexcept
    {
        if (this->subscribers.find(event.getType()) == this->subscribers.end())
            return;
        const SubscribersArray &subscribersArray = this->subscribers[event.getType()];
        for (const auto &subscriber : subscribersArray)
        {
            subscriber(&event);
            if (event.isHandled())
                break;
        }
    }
    void subscribe(EventType eventType, const EventFunction &function)
    {
        if (this->subscribers.find(eventType) == this->subscribers.end())
            this->subscribers[eventType] = SubscribersArray();
        this->subscribers[eventType].push_back(EventFunction(function));
    }
};

}

#endif //VANADIUM_EVENTDISPATCHER_H
