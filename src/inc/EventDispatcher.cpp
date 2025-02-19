#include "EventDispatcher.h"

void EventDispatcher::addEventListener(const std::string &eventName, Callback cb)
{
    listeners[eventName].push_back(cb);
}

void EventDispatcher::dispatchEvent(const std::string &eventName, void *payload)
{
    if (listeners.find(eventName) == listeners.end())
        return;
    for (const auto &cb : listeners[eventName])
    {
        cb(payload);
    }
}
