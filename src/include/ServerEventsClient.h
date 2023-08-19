#pragma once

#include <string>

// casper server test address
#define SSE_TEST_ADDRESS "http://93.190.141.13:9999"

namespace Casper
{
class ServerEventsClient
{
public:
    /**
     * @brief Construct a new ServerEventsClient object
     *
     * @param address is a URL of the node like 'http://127.0.0.1:9999'. Default
     * endpoint is '/events'.
     */
    ServerEventsClient(std::string address_);

    void listen();

private:
    std::string address;
};


} // namespace Casper