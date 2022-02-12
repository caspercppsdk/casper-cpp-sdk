#pragma once

#include <filesystem>
#include <string>

// http connection
#include "JsonRpc/Connection/HttpLibConnector.h"

// json rpc result types
#include "JsonRpc/ResultTypes/GetBalanceResult.h"
#include "JsonRpc/ResultTypes/GetBlockResult.h"
#include "JsonRpc/ResultTypes/GetBlockTransfersResult.h"
#include "JsonRpc/ResultTypes/GetDeployResult.h"
#include "JsonRpc/ResultTypes/GetEraInfoResult.h"
#include "JsonRpc/ResultTypes/GetStateRootHashResult.h"
#include "JsonRpc/ResultTypes/GetStatus.h"
#include "JsonRpc/ResultTypes/InfoGetPeersResult.h"

// param types
#include "Types/BlockIdentifier.h"
#include "Types/GlobalStateKey.h"
#include "Types/URef.h"

// external libraries
#include "jsonrpccxx/client.hpp"
#include "nlohmann/json.hpp"

// casper server test address
#define CASPER_TEST_ADDRESS "http://138.201.54.44:7777"

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
  GetBlockTransfersResult GetBlockTransfers(BlockIdentifier identifier);
  GetBlockTransfersResult GetBlockTransfers();
  GetBlockResult GetBlock(BlockIdentifier identifier);
  GetEraInfoResult GetEraInfoBySwitchBlock();
  GetEraInfoResult GetEraInfoBySwitchBlock(std::string hash);
  GetEraInfoResult GetEraInfoBySwitchBlock(uint64_t height);

  // stateGetItem
  // stateGetDictionaryItem
  // TODO: GetAccountBalance stateRootHash should have a default value as empty
  // string however, there is a bug in the cpp file getstateroothash() because
  // there is no await process to wait the result
  GetBalanceResult GetAccountBalance(std::string purseURef,
                                     std::string stateRootHash);
  // stateGetAuctionInfo
};

};  // namespace Casper