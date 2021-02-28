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
    using SubscribersMap = std::unordered_map<Event::Type, SubscribersArray>;

private:
    SubscribersMap subscribers;
    SubscribersArray subscribersToAny;
    SubscribersMap prioritySubscribers;
    SubscribersArray prioritySubscribersToAny;

    // Todo: think about another name. Ugly method.
    void dispatchUsingInput(Event *event, SubscribersArray &any, SubscribersMap &map)
    {
        if (event->isHandled())
            return;
        for (const auto &subscriber : any)
        {
            subscriber(event);
            if (event->isHandled())
                return;
        }
        if (map.find(event->getType()) == map.end())
            return;
        const SubscribersArray &subscribersArray = map[event->getType()];
        for (const auto &subscriber : subscribersArray)
        {
            subscriber(event);
            if (event->isHandled())
                return;
        }
    }

public:
    EventDispatcher() = default;

    void dispatch(Event *event) noexcept
    {
        this->dispatchUsingInput(event, this->prioritySubscribersToAny, this->prioritySubscribers);
        this->dispatchUsingInput(event, this->subscribersToAny, this->subscribers);
    }

    void subscribe(Event::Type eventType, const EventFunction &function)
    {
        if (eventType == Event::Type::Any)
        {
            this->subscribersToAny.push_back(EventFunction(function));
            return;
        }
        if (this->subscribers.find(eventType) == this->subscribers.end())
            this->subscribers[eventType] = SubscribersArray();
        this->subscribers[eventType].push_back(EventFunction(function));
    }

    void prioritySubscribe(Event::Type eventType, const EventFunction &function)
    {
        if (eventType == Event::Type::Any)
        {
            this->prioritySubscribersToAny.push_back(EventFunction(function));
            return;
        }
        if (this->prioritySubscribers.find(eventType) == this->prioritySubscribers.end())
            this->prioritySubscribers[eventType] = SubscribersArray();
        this->subscribers[eventType].push_back(EventFunction(function));
    }

};

}

#endif //VANADIUM_EVENTDISPATCHER_H
