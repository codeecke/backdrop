#ifndef EVENTDISPATCHER_H
#define EVENTDISPATCHER_H

#include <unordered_map>
#include <vector>
#include <functional>
#include <string>

class EventDispatcher
{
public:
    using Callback = std::function<void(void *)>;

    void addEventListener(const std::string &eventName, Callback cb);
    void dispatchEvent(const std::string &eventName, void *payload = nullptr);

private:
    std::unordered_map<std::string, std::vector<Callback>> listeners;
};

#endif // EVENTDISPATCHER_H
