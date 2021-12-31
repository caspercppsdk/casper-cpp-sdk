#pragma once

#include <filesystem>
#include <string>

#include "JsonRpc/Connection/HttpLibConnector.h"
#include "JsonRpc/ResultTypes/GetStateRootHashResult.h"
#include "JsonRpc/ResultTypes/InfoGetPeersResult.h"
#include "JsonRpc/ResultTypes/GetDeployResult.h"
#include "JsonRpc/ResultTypes/GetStatus.h"

#include "jsonrpccxx/client.hpp"
#include "nlohmann/json.hpp"

#define CASPER_TEST_ADDRESS "http://127.0.0.1:7777"

namespace Casper {
class Client {
 private:
  std::string mAddress;
  HttpLibConnector mHttpConnector;
  jsonrpccxx::JsonRpcClient mRpcClient;

 public:
  Client(const std::string& address);

  InfoGetPeersResult GetNodePeers();
  GetStateRootHashResult GetStateRootHash(uint64_t block_height);
  GetStateRootHashResult GetStateRootHash(const std::string& block_hash = "");
  GetDeployInfoResult GetDeployInfo(const std::string& deploy_hash);
  GetStatusInfoResult GetStatusInfo();
};

};  // namespace Casper