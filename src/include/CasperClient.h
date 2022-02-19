#pragma once

#include <filesystem>
#include <string>

// http connection
#include "JsonRpc/Connection/HttpLibConnector.h"

// json rpc result types
#include "JsonRpc/ResultTypes/GetAuctionInfoResult.h"
#include "JsonRpc/ResultTypes/GetBalanceResult.h"
#include "JsonRpc/ResultTypes/GetBlockResult.h"
#include "JsonRpc/ResultTypes/GetBlockTransfersResult.h"
#include "JsonRpc/ResultTypes/GetDeployResult.h"
#include "JsonRpc/ResultTypes/GetDictionaryItemResult.h"
#include "JsonRpc/ResultTypes/GetEraInfoResult.h"
#include "JsonRpc/ResultTypes/GetItemResult.h"
#include "JsonRpc/ResultTypes/GetStateRootHashResult.h"
#include "JsonRpc/ResultTypes/GetStatusResult.h"
#include "JsonRpc/ResultTypes/InfoGetPeersResult.h"
#include "JsonRpc/ResultTypes/PutDeployResult.h"

// param types
#include "Types/Bid.h"
#include "Types/BlockIdentifier.h"
#include "Types/Deploy.h"
#include "Types/EraSummary.h"
#include "Types/GlobalStateKey.h"
#include "Types/URef.h"

// Utils
#include "Utils/CryptoUtil.h"

// external libraries
#include "jsonrpccxx/client.hpp"
#include "magic_enum/magic_enum.hpp"
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
  GetStateRootHashResult GetStateRootHash(std::string block_hash = "");
  GetStateRootHashResult GetStateRootHash(uint64_t block_height);
  GetDeployInfoResult GetDeployInfo(std::string deploy_hash);
  GetStatusResult GetStatusInfo();
  GetBlockTransfersResult GetBlockTransfers(std::string block_hash = "");
  GetBlockTransfersResult GetBlockTransfers(uint64_t block_height);
  GetBlockResult GetBlock(std::string block_hash = "");
  GetBlockResult GetBlock(uint64_t block_height);
  GetEraInfoResult GetEraInfoBySwitchBlock(std::string block_hash = "");
  GetEraInfoResult GetEraInfoBySwitchBlock(uint64_t block_height);
  PutDeployResult PutDeploy(Deploy deploy);

  GetItemResult GetItem(std::string state_root_hash,
                        std::string key,
                        std::vector<std::string> path = {});

  GetDictionaryItemResult GetDictionaryItem(std::string stateRootHash,
                                            std::string dictionaryItem);
  GetDictionaryItemResult GetDictionaryItemByAccount(
      std::string stateRootHash,
      std::string accountKey,
      std::string dictionaryName,
      std::string dictionaryItemKey);
  GetDictionaryItemResult GetDictionaryItemByContract(
      std::string stateRootHash,
      std::string contractKey,
      std::string dictionaryName,
      std::string dictionaryItemKey);
  GetDictionaryItemResult GetDictionaryItemByURef(
      std::string stateRootHash,
      std::string seedURef,
      std::string dictionaryItemKey);

  // TODO: GetAccountBalance stateRootHash should have a default value as
  // empty string however, there is a bug in the cpp file getstateroothash()
  // because there is no await process to wait the result
  GetBalanceResult GetAccountBalance(std::string purseURef,
                                     std::string stateRootHash);

  GetAuctionInfoResult GetAuctionInfo(std::string block_hash = "");
  GetAuctionInfoResult GetAuctionInfo(uint64_t block_height);
};

};  // namespace Casper