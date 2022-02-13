#include <CasperClient.h>

namespace Casper {
/**
 * @brief Construct a new Casper Client object
 *
 * @param address is a URL of the node like 'http://127.0.0.1:7777'. Default
 * endpoint is '/rpc'.
 */
Client::Client(const std::string& address)
    : mAddress{address},
      mHttpConnector{mAddress},
      mRpcClient{mHttpConnector, jsonrpccxx::version::v2} {}

/**
 * @brief Get a list of the nodes.
 *
 * @return InfoGetPeersResult that is a struct contains a Peer vector.
 */
InfoGetPeersResult Client::GetNodePeers() {
  return mRpcClient.CallMethod<InfoGetPeersResult>(1, "info_get_peers", {});
}

/**
 * @brief Returns the state root hash at a given Block
 *
 * @param block_hash Block hash string of the node. Use empty string to get the
 * state root hash of the latest block.
 * @return GetStateRootHashResult that contains the state_root_hash as a string.
 */
GetStateRootHashResult Client::GetStateRootHash(std::string block_hash) {
  nlohmann::json hashJSON{{"Hash", block_hash}};
  nlohmann::json block_identifier{{"block_identifier", hashJSON}};

  return mRpcClient.CallMethodNamed<GetStateRootHashResult>(
      1, "chain_get_state_root_hash", block_identifier);
}

/**
 * @brief Returns the state root hash at a given height
 *
 * @param block_height The height of the block as a uint64_t.
 * @return GetStateRootHashResult that contains the state_root_hash as a string.
 */
GetStateRootHashResult Client::GetStateRootHash(uint64_t block_height) {
  nlohmann::json heightJSON{{"Height", block_height}};
  nlohmann::json block_identifier{{"block_identifier", heightJSON}};

  return mRpcClient.CallMethodNamed<GetStateRootHashResult>(
      1, "chain_get_state_root_hash", block_identifier);
}

/**
 * @brief Returns the deploy info.
 *
 * @param deploy_hash Hash string of the smart contract.
 * @return GetDeployInfoResult that contains the deploy info as a string.
 */
GetDeployInfoResult Client::GetDeployInfo(std::string deploy_hash) {
  nlohmann::json hashJSON{{"deploy_hash", deploy_hash}};

  return mRpcClient.CallMethodNamed<GetDeployInfoResult>(1, "info_get_deploy",
                                                         hashJSON);
}

/**
 * @brief Returns the status info.
 *
 * @return GetStatusInfoResult that contains the status info as a string.
 */
GetStatusInfoResult Client::GetStatusInfo() {
  return mRpcClient.CallMethodNamed<GetStatusInfoResult>(1, "info_get_status");
}

/**
 * @brief Returns the transfers infotmation.
 *
 * @return GetBlockTransfersResult that contains the transfers info.
 */
GetBlockTransfersResult Client::GetBlockTransfers() {
  return mRpcClient.CallMethodNamed<GetBlockTransfersResult>(
      1, "chain_get_block_transfers");
}

/**
 * @brief Returns the transfers information.
 *
 * @return GetBlockTransfersResult that contains the transfers info.
 */
GetBlockTransfersResult Client::GetBlockTransfers(BlockIdentifier identifier) {
  nlohmann::json identifierJSON{{"Hash", identifier.hash},
                                {"Height", identifier.height}};

  return mRpcClient.CallMethodNamed<GetBlockTransfersResult>(
      1, "chain_get_block_transfers", identifierJSON);
}

/**
 * @brief Returns the block information.
 *
 * @return GetBlockResult that contains the block info.
 */
GetBlockResult Client::GetBlock(std::string block_hash) {
  nlohmann::json hashJSON{{"Hash", block_hash}};
  nlohmann::json block_identifier{{"block_identifier", hashJSON}};

  return mRpcClient.CallMethodNamed<GetBlockResult>(1, "chain_get_block",
                                                    block_identifier);
}

/**
 * @brief Returns the block information.
 *
 * @return GetBlockResult that contains the block info.
 */
GetBlockResult Client::GetBlock(uint64_t block_height) {
  nlohmann::json heightJSON{{"Height", block_height}};
  nlohmann::json block_identifier{{"block_identifier", heightJSON}};

  return mRpcClient.CallMethodNamed<GetBlockResult>(1, "chain_get_block",
                                                    block_identifier);
}

/**
 * @brief Returns the era information.
 *
 * @return GetEraInfoBySwitchBlock that contains the era info.
 */
GetEraInfoResult Client::GetEraInfoBySwitchBlock(std::string block_hash) {
  nlohmann::json hashJSON{{"Hash", block_hash}};
  nlohmann::json block_identifier{{"block_identifier", hashJSON}};

  return mRpcClient.CallMethodNamed<GetEraInfoResult>(
      1, "chain_get_era_info_by_switch_block", block_identifier);
}

/**
 * @brief Returns the era information.
 *
 * @return GetEraInfoBySwitchBlock that contains the era info.
 */
GetEraInfoResult Client::GetEraInfoBySwitchBlock(uint64_t block_height) {
  nlohmann::json heightJSON{{"Height", block_height}};
  nlohmann::json block_identifier{{"block_identifier", heightJSON}};

  return mRpcClient.CallMethodNamed<GetEraInfoResult>(
      1, "chain_get_era_info_by_switch_block", block_identifier);
}

GetItemResult Client::GetItem(std::string state_root_hash,
                              std::string key,
                              std::vector<std::string> path) {
  nlohmann::json paramsJSON{
      {"state_root_hash", state_root_hash}, {"key", key}, {"path", path}};

  return mRpcClient.CallMethodNamed<GetItemResult>(1, "state_get_item",
                                                   paramsJSON);
}

PutDeployResult Client::PutDeploy(Deploy deploy) {
  nlohmann::json deploy_json;
  to_json(deploy_json, deploy);
  nlohmann::json paramsJSON{"deploy", deploy_json};

  return mRpcClient.CallMethodNamed<PutDeployResult>(1, "account_put_deploy",
                                                     paramsJSON);
}

/**
 * @brief Returns the balance of the account.
 *
 * @return GetBalanceResult that contains the balance and merkle_proof.
 */

GetBalanceResult Client::GetAccountBalance(std::string purseURef,
                                           std::string stateRootHash) {
  /*
// TODO:
if (!purseURef.StartsWith("uref-"))
            {
                var response = await GetAccountInfo(purseURef);
                purseURef = response.Result.GetProperty("account")
                    .GetProperty("main_purse").GetString();
            }


  if (stateRootHash.empty()) {
    stateRootHash = GetStateRootHash().state_root_hash;
  }
*/
  nlohmann::json paramsJSON{{"state_root_hash", stateRootHash},
                            {"purse_uref", purseURef}};

  return mRpcClient.CallMethodNamed<GetBalanceResult>(1, "state_get_balance",
                                                      paramsJSON);
}

}  // namespace Casper
