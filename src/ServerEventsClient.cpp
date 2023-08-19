// TODO: remove if possible #include <spdlog/spdlog.h>
#include "ServerEventsClient.h"
#include "JsonRpc/Connection/httplib.h"

namespace Casper
{

/// Construct a new Casper Client object
ServerEventsClient::ServerEventsClient(std::string address_)
    : address{std::move(address_)}
{
}

void ServerEventsClient::listen()
{
    httplib::Client client(address);

    // Set a longer read timeout since SSE can have long periods of inactivity
    client.set_read_timeout(500); // 500 seconds

    auto res = client.Get("/events/deploys",
                          [&](const char* data, size_t data_length)
                          {
                              std::string str_data(data, data_length);

                              // Handle the SSE data directly within the lambda.
                              if (str_data.substr(0, 5) == "data:")
                              {
                                  std::cout << "Received SSE event: " << str_data.substr(6) << std::endl;
                              }

                              return true; // Return true to continue receiving data.
                          });

    if (res.error() != httplib::Error::Success)
    {
        std::cerr << "Error: " << to_string(res.error()) << std::endl;
    }

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

} // namespace Casper
