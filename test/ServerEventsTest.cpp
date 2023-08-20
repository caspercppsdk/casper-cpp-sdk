#define TEST_NO_MAIN 1

#include "ServerEventsTest.h"
#include "acutest.h"
#include <thread>

namespace Casper
{

void Hello_SSE_Test(void)
{
    bool shouldPrint = true; // Add this line to control the printing

    ServerEventsClient client("http://93.190.141.13:9999");

    auto printCallback = [&](const std::string& message, const Casper::EventData& eventData)
    {
        if (shouldPrint)
        {
            std::cout << message << eventData.payload << std::endl;
        }
    };

    // Use the printCallback in your event callbacks
    client.addEventCallback(
        Casper::EventType::ApiVersion, "ApiVersion",
        std::bind(printCallback, "Received ApiVersion event with payload: ", std::placeholders::_1));

    client.addEventCallback(
        Casper::EventType::BlockAdded, "BlockAdded",
        std::bind(printCallback, "Received BlockAdded event with payload: ", std::placeholders::_1));

    client.addEventCallback(
        Casper::EventType::DeployAccepted, "DeployAccepted",
        std::bind(printCallback, "Received DeployAccepted event with payload: ", std::placeholders::_1));

    client.addEventCallback(
        Casper::EventType::DeployProcessed, "DeployProcessed",
        std::bind(printCallback, "Received DeployProcessed event with payload: ", std::placeholders::_1));

    client.addEventCallback(Casper::EventType::Fault, "Fault",
                            std::bind(printCallback, "Received Fault event with payload: ", std::placeholders::_1));

    client.addEventCallback(Casper::EventType::Step, "Step",
                            std::bind(printCallback, "Received Step event with payload: ", std::placeholders::_1));

    client.addEventCallback(
        Casper::EventType::FinalitySignature, "FinalitySignature",
        std::bind(printCallback, "Received FinalitySignature event with payload: ", std::placeholders::_1));

    client.addEventCallback(
        Casper::EventType::DeployExpired, "DeployExpired",
        std::bind(printCallback, "Received DeployExpired event with payload: ", std::placeholders::_1));

    // Start listening on the channels
    client.startListening();

    // Sleep for 1000 seconds to give time for events to be received
    std::this_thread::sleep_for(std::chrono::seconds(100000));

    // Stop listening
    client.stopListening();
}

} // namespace Casper
