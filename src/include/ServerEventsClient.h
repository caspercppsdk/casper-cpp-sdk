#pragma once

#include "Base.h"
#include "JsonRpc/Connection/httplib.h"

#include <string>
#include <map>
#include <set>
#include <vector>
#include <future>
#include <atomic>
#include <functional>

namespace Casper
{
enum class ChannelType
{
    Main,
    Deploys,
    Sigs
};

enum class EventType
{
    All,
    ApiVersion,
    BlockAdded,
    DeployAccepted,
    DeployProcessed,
    Fault,
    Step,
    FinalitySignature,
    DeployExpired
};

struct EventData
{
    bool hasData() const { return !payload.empty(); }

    EventType eventType;
    int id;
    std::string payload;
};

using EventCallback = std::function<void(const EventData&)>;

struct SSECallback
{
    EventType eventType;
    std::string name;
    EventCallback callbackFn;
    int startFrom;

    SSECallback(EventType et, const std::string& n, EventCallback cb, int sf = INT32_MAX)
        : eventType(et)
        , name(n)
        , callbackFn(cb)
        , startFrom(sf)
    {
    }
};


class ServerEventsClient
{
public:
    ServerEventsClient(const std::string& address_);
    void listen();
    void startListening();
    void stopListening();
    void addEventCallback(EventType eventType, const std::string& name, EventCallback cb, int startFrom = INT32_MAX);
    bool removeEventCallback(EventType eventType, const std::string& name);

private:
    void listenChannelAsync(ChannelType channelType, int startFrom, std::atomic<bool>& isRunning);
    bool parseEventType(const std::string& evtType, EventType& evt);
    bool parseStream(const std::string& line, EventData& eventData);
    void emitEvent(const EventData& eventData);

    std::string address;
    std::string accumulated_data;
    std::set<ChannelType> _channels;
    std::vector<std::unique_ptr<httplib::Client>> _clients;

    std::vector<SSECallback> _callbacks;
    std::map<EventType, ChannelType> eventTypeToChannelMap;

    std::vector<std::unique_ptr<std::atomic<bool>>> _runningFlags;
    std::vector<std::future<void>> _runningTasks;
};
} // namespace Casper