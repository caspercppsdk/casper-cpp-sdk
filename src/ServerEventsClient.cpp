#include "ServerEventsClient.h"
#include <iostream>
#include <httplib.h>
#include <thread>
#include <nlohmann/json.hpp>

namespace Casper
{

ServerEventsClient::ServerEventsClient(const std::string& address_)
    : address(address_)
{
    eventTypeToChannelMap = {{EventType::DeployAccepted, ChannelType::Deploys},
                             {EventType::BlockAdded, ChannelType::Main},
                             {EventType::DeployProcessed, ChannelType::Main},
                             {EventType::Fault, ChannelType::Main},
                             {EventType::Step, ChannelType::Main},
                             {EventType::FinalitySignature, ChannelType::Sigs},
                             {EventType::DeployExpired, ChannelType::Main}};
}


void ServerEventsClient::startListening()
{
    _runningFlags.clear();
    _runningTasks.clear();

    // Store which channels we have already started to avoid starting the same channel multiple times
    std::set<ChannelType> startedChannels;

    for (const auto& callback : _callbacks)
    {
        auto channelType = eventTypeToChannelMap[callback.eventType];
        if (startedChannels.find(channelType) == startedChannels.end())
        {
            _runningFlags.emplace_back(std::make_unique<std::atomic<bool>>(true));

            _runningTasks.emplace_back(
                std::async(std::launch::async, [this, channelType, &callback]()
                           { this->listenChannelAsync(channelType, callback.startFrom, *_runningFlags.back()); }));

            startedChannels.insert(channelType);
        }
    }
}


void ServerEventsClient::stopListening()
{
    for (size_t i = 0; i < _runningFlags.size(); ++i)
    {
        _runningFlags[i]->store(false);
        _runningTasks[i].wait();
    }
}

void ServerEventsClient::addEventCallback(EventType eventType, const std::string& name, EventCallback cb, int startFrom)
{
    _callbacks.emplace_back(eventType, name, cb, startFrom);

    // Get the channel for the event type and add it to _channels
    auto it = eventTypeToChannelMap.find(eventType);
    if (it != eventTypeToChannelMap.end())
    {
        _channels.insert(it->second);
    }
}


bool ServerEventsClient::removeEventCallback(EventType eventType, const std::string& name)
{
    for (auto it = _callbacks.begin(); it != _callbacks.end(); ++it)
    {
        if (it->eventType == eventType && it->name == name)
        {
            _callbacks.erase(it);
            return true;
        }
    }
    return false;
}

void ServerEventsClient::listenChannelAsync(ChannelType channelType, int startFrom, std::atomic<bool>& isRunning)
{
    std::string local_accumulated_data; // Each task has its own local copy

    httplib::Client client(address);
    client.set_read_timeout(500); // 500 seconds

    std::string endpoint;
    switch (channelType)
    {
    case ChannelType::Main:
        endpoint = "/events/main";
        break;
    case ChannelType::Deploys:
        endpoint = "/events/deploys";
        break;
    case ChannelType::Sigs:
        endpoint = "/events/sigs";
        break;
    }

    if (startFrom != INT32_MAX)
    {
        endpoint += "?start_from=" + std::to_string(startFrom);
    }

    auto res = client.Get(endpoint.c_str(),
                          [&](const char* data, size_t data_length)
                          {
                              local_accumulated_data.append(data, data_length);
                              size_t pos;

                              while ((pos = local_accumulated_data.find("\n\n")) != std::string::npos && isRunning)
                              {
                                  std::string full_event = local_accumulated_data.substr(0, pos);
                                  local_accumulated_data.erase(0, pos + 2);

                                  EventData eventData;
                                  if (parseStream(full_event, eventData))
                                  {
                                      emitEvent(eventData);
                                  }
                              }

                              return isRunning.load(); // Continue receiving data as long as isRunning is true.
                          });

    if (res.error() != httplib::Error::Success && isRunning)
    {
        std::cerr << "Error: " << httplib::to_string(res.error()) << std::endl;
    }
}

bool ServerEventsClient::parseEventType(const std::string& evtType, EventType& evt)
{
    if (evtType == "ApiVersion")
    {
        evt = EventType::ApiVersion;
    }
    else if (evtType == "BlockAdded")
    {
        evt = EventType::BlockAdded;
    }
    else if (evtType == "DeployAccepted")
    {
        evt = EventType::DeployAccepted;
    }
    else if (evtType == "DeployProcessed")
    {
        evt = EventType::DeployProcessed;
    }
    else if (evtType == "Fault")
    {
        evt = EventType::Fault;
    }
    else if (evtType == "Step")
    {
        evt = EventType::Step;
    }
    else if (evtType == "FinalitySignature")
    {
        evt = EventType::FinalitySignature;
    }
    else if (evtType == "DeployExpired")
    {
        evt = EventType::DeployExpired;
    }
    else
    {
        return false;
    }
    return true;
}

bool ServerEventsClient::parseStream(const std::string& line, EventData& eventData)
{
    if (line.empty() || line.find(":") == 0)
    {
        return eventData.hasData();
    }

    // Split the line into data and id components
    size_t splitPos = line.find("\n");
    std::string dataLine = line.substr(0, splitPos);
    std::string idLine = splitPos != std::string::npos ? line.substr(splitPos + 1) : "";

    // Handle the data component
    if (dataLine.find("data:{\"ApiVersion\"") == 0)
    {
        eventData.eventType = EventType::ApiVersion;
        eventData.payload = dataLine.substr(5);
    }
    else if (dataLine.find("data:{") == 0)
    {
        size_t q1 = dataLine.find('"');
        size_t q2 = dataLine.find('"', q1 + 1);
        std::string evtType = dataLine.substr(q1 + 1, q2 - q1 - 1);

        EventType evt;
        if (parseEventType(evtType, evt))
        {
            eventData.eventType = evt;

            nlohmann::json j;
            try
            {
                j = nlohmann::json::parse(dataLine.substr(5));
                if (j.contains(evtType))
                {
                    eventData.payload = j[evtType].dump();
                }
            }
            catch (const nlohmann::json::exception& e)
            {
                std::cerr << "JSON parsing error: " << e.what() << std::endl;
                std::cerr << "Failed to parse: " << dataLine.substr(5) << std::endl;
                return false;
            }
        }
    }

    // Handle the id component
    if (idLine.find("id:") == 0)
    {
        try
        {
            eventData.id = std::stoi(idLine.substr(3));
        }
        catch (const std::exception&)
        {
            return false;
        }
    }

    return true;
}


void ServerEventsClient::emitEvent(const EventData& eventData)
{
    for (const auto& callback : _callbacks)
    {
        if (callback.eventType == eventData.eventType)
        {
            callback.callbackFn(eventData);
        }
    }
}

} // namespace Casper
