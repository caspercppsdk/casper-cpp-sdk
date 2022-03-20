#pragma once
#include <string>

#include "JsonRpc/Connection/httplib.h"
#include "jsonrpccxx/iclientconnector.hpp"
#include "jsonrpccxx/server.hpp"

/**
 * @brief Wrapper class for the Http Client Connection class in jsonrpccxx.
 *
 */
namespace Casper {
class HttpLibConnector : public jsonrpccxx::IClientConnector {
 public:
  /**
   * @brief Construct a new Http Lib Connector object. Explicit to prevent
   * implicit conversion.
   *
   * @param host
   */
  explicit HttpLibConnector(const std::string& host)
      : httpClient(host.c_str()) {}

  /**
   * @brief Send the request to the server via the Http Client Connection class.
   *
   * @param request
   * @return std::string
   */
  std::string Send(const std::string& request) override {
    auto res = httpClient.Post("/rpc", request, "application/json");
    if (!res || res->status != 200) {
      throw jsonrpccxx::JsonRpcException(
          -32003, "client connector error, received status != 200");
    }
    return res->body;
  }

 private:
  /// httplib::Client object to send the request to the server as an RPC call.
  httplib::Client httpClient;
};
}  // namespace Casper
