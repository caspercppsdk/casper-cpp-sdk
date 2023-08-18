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
#include "JsonRpc/ResultTypes/QueryGlobalStateResult.h"
#include "JsonRpc/ResultTypes/SpeculativeExecResult.h"

// param types
#include "Types/Bid.h"
#include "Types/Deploy.h"
#include "Types/EraSummary.h"
#include "Types/GlobalStateKey.h"
#include "Types/URef.h"

// Utils
#include "Utils/CryptoUtil.h"
#include "Utils/LogConfigurator.h"

// external libraries
#include "jsonrpccxx/client.hpp"
#include "magic_enum/magic_enum.hpp"
#include "nlohmann/json.hpp"

// casper server test address
#define CASPER_TEST_ADDRESS "http://103.104.75.222:7777"

namespace Casper {
class Client {
 private:
  std::string mAddress;
  HttpLibConnector mHttpConnector;
  jsonrpccxx::JsonRpcClient mRpcClient;

 public:
  /**
   * @brief Construct a new Casper Client object
   *
   * @param address is a URL of the node like 'http://127.0.0.1:7777'. Default
   * endpoint is '/rpc'.
   */
  Client(const std::string& address, const LogConfig* const log_config = nullptr);

  /**
   * @brief Get a list of the nodes.
   *
   * @return InfoGetPeersResult that is a struct contains a Peer vector.
   */
  InfoGetPeersResult GetNodePeers();

  /**
   * @brief Returns the state root hash at a given block
   *
   * @param block_hash Block hash string of the node. Use empty string to get
   * the state root hash of the latest block.
   * @return GetStateRootHashResult that contains the state_root_hash as a
   * string.
   */
  GetStateRootHashResult GetStateRootHash(std::string block_hash = "");

  /**
   * @brief Returns the state root hash at a given height
   *
   * @param block_height The height of the block as a uint64_t.
   * @return GetStateRootHashResult that contains the state_root_hash as a
   * string.
   */
  GetStateRootHashResult GetStateRootHash(uint64_t block_height);

  /**
   * @brief Returns the deploy info.
   *
   * @param deploy_hash Hash string of the deploy.
   * @return GetDeployInfoResult that contains the deploy information as a
   * string.
   */
  GetDeployInfoResult GetDeployInfo(std::string deploy_hash, int counter = 0);

  /**
   * @brief Returns the status info.
   *
   * @return GetStatusResult that contains the status information as a string.
   */
  GetStatusResult GetStatusInfo();

  /**
   * @brief Returns the transfers infotmation.
   * @param block_hash Block hash string of the node. Use empty string to get
   * the transfers of the latest block.
   * @return GetBlockTransfersResult that contains the transfers info.
   */
  GetBlockTransfersResult GetBlockTransfers(std::string block_hash = "");

  /**
   * @brief Returns the transfers information.
   * @param block_height The height of the block as a uint64_t.
   * @return GetBlockTransfersResult that contains the transfers info.
   */
  GetBlockTransfersResult GetBlockTransfers(uint64_t block_height);

  /**
   * @brief Returns the block information.
   * @param block_hash Block hash string of the node. Use empty string to get
   * the block info of the latest block.
   * @return GetBlockResult that contains the block info.
   */
  GetBlockResult GetBlock(std::string block_hash = "");

  /**
   * @brief Returns the block information.
   * @param block_height The height of the block as a uint64_t.
   * @return GetBlockResult that contains the block info.
   */
  GetBlockResult GetBlock(uint64_t block_height);

  /**
   * @brief Returns the era information.
   * @param block_hash Block hash string of the node. Use empty string to get
   * the era info of the latest block.
   * @return GetEraInfoBySwitchBlock that contains the era info.
   */
  GetEraInfoResult GetEraInfoBySwitchBlock(std::string block_hash = "");

  /**
   * @brief Returns the era information.
   * @param block_height The height of the block as a uint64_t.
   * @return GetEraInfoBySwitchBlock that contains the era info.
   */
  GetEraInfoResult GetEraInfoBySwitchBlock(uint64_t block_height);

  /**
   * @brief Returns the item information.
   *
   * @param state_root_hash The state root hash of the block.
   * @param key The key of the item.
   * @param path The path of the item.
   * @return GetItemResult that contains the item info.
   */
  GetItemResult GetItem(std::string state_root_hash, std::string key,
                        std::vector<std::string> path = {});

  /**
   * FIXME: It is only a workaround, as GetItem function does
   *        not parse correctly result from json:
   *        https://matterfi.atlassian.net/browse/CD-216
   * @brief Returns the item information in nlohmann::json.
   *
   * @param state_root_hash The state root hash of the block.
   * @param key The key of the item.
   * @param path The path of the item.
   * @return nlohmann::json that contains the item info.
   */
  nlohmann::json GetItem_WA(std::string state_root_hash, std::string key,
                            std::vector<std::string> path = {});

  /**
   * @brief Get the Dictionary Item object
   *
   * @param stateRootHash The hash of the state root.
   * @param dictionaryItem The dictionary item key to get the value of.
   * @return json that contains the dictionary item
   * information.
   */
  nlohmann::json GetDictionaryItem(std::string stateRootHash,
                                   std::string dictionaryItem);

  /**
   * @brief Get the Dictionary Item by Account's named keys.
   *
   * @param stateRootHash The hash of the state root.
   * @param accountKey The account key as a formatted string whose named keys
   * contains the dictionary name.
   * @param dictionaryName The named key under which the dictionary seed URef is
   * stored.
   * @param dictionaryItemKey The dictionary item key to get the value of.
   * @return GetDictionaryItemResult that contains the dictionary item
   * information.
   */
  GetDictionaryItemResult GetDictionaryItemByAccount(
      std::string stateRootHash, std::string accountKey,
      std::string dictionaryName, std::string dictionaryItemKey);

  /**
   * @brief Get the Dictionary Item By Contract object
   *
   * @param stateRootHash The hash of the state root.
   * @param contractKey The contract key as a formatted string whose named keys
   * contains the dictionary name.
   * @param dictionaryName The named key under which the dictionary seed URef is
   * stored.
   * @param dictionaryItemKey The dictionary item key to get the value of.
   * @return GetDictionaryItemResult that contains the dictionary item
   * information.
   */
  GetDictionaryItemResult GetDictionaryItemByContract(
      std::string stateRootHash, std::string contractKey,
      std::string dictionaryName, std::string dictionaryItemKey);

  /**
   * @brief Get the Dictionary Item By U Ref object
   *
   * @param stateRootHash The hash of the state root.
   * @param seedURef The seed URef of the dictionary.
   * @param dictionaryItemKey The dictionary item key to get the value of.
   * @return GetDictionaryItemResult that contains the dictionary item
   * information.
   */
  GetDictionaryItemResult GetDictionaryItemByURef(
      std::string stateRootHash, std::string seedURef,
      std::string dictionaryItemKey);

  /**
   * @brief Returns the balance of the account.
   * @param purseURef The purse URef of the account as a string.
   * @param stateRootHash The hash of the state root.
   * @return GetBalanceResult that contains the balance and merkle proof.
   */
  GetBalanceResult GetAccountBalance(std::string purseURef,
                                     std::string stateRootHash);

  /**
   * @brief Get the Auction Info object
   *
   * @param block_hash Block hash string of the node. Use empty string to get
   * the auction info of the latest block.
   * @return GetAuctionInfoResult that contains the auction information.
   */
  GetAuctionInfoResult GetAuctionInfo(std::string block_hash = "");

  /**
   * @brief Get the Auction Info object
   *
   * @param block_height The height of the block as a uint64_t.
   * @return GetAuctionInfoResult that contains the auction information.
   */
  GetAuctionInfoResult GetAuctionInfo(uint64_t block_height);

  /**
   * @brief Send a deploy to the network to be processed by the network.
   *
   * @param deploy The deploy object to be sent to the network.
   * @return PutDeployResult that contains the deploy information.
   */
  PutDeployResult PutDeploy(Deploy deploy);


  std::vector<std::string> splitPath(std::string path);

  QueryGlobalStateResult QueryGlobalState(std::string key, std::string state_root_hash="", std::string path="");

QueryGlobalStateResult QueryGlobalState(GlobalStateKey key, std::string state_root_hash="", std::string path="");

QueryGlobalStateResult QueryGlobalStateWithBlockHash(std::string key, std::string block_hash, std::string path="");

QueryGlobalStateResult QueryGlobalStateWithBlockHash(GlobalStateKey key, std::string block_hash, std::string path="");

/**
     * @brief Return the results of the execution to the caller
     *
     * @param deploy The deploy object to be sent to the network.
     * @param block_hash Block hash string of the node. Use empty string to get
     * the state root hash of the latest block.
     * @return SpeculativeExecResult that contains the state_root_hash as a
     * string.
     */
    SpeculativeExecResult SpeculativeExec(Deploy deploy, std::string block_hash = "");

    /**
     * @brief Return the results of the execution to the caller
     *
     * @param deploy The deploy object to be sent to the network.
     * @param block_height The height of the block as a uint64_t.
     * @return SpeculativeExecResult that contains the state_root_hash as a
     * string.
     */
    SpeculativeExecResult SpeculativeExec(Deploy deploy, uint64_t block_height);
};

}  // namespace Casper
