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
  /**
   * @brief Construct a new Casper Client object
   *
   * @param address is a URL of the node like 'http://127.0.0.1:7777'. Default
   * endpoint is '/rpc'.
   */
  Client(const std::string& address);

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
  GetDeployInfoResult GetDeployInfo(std::string deploy_hash);

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
};

}  // namespace Casper