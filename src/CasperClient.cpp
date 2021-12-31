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
 * @param block_height The height of the block as a uint64_t.
 * @return GetStateRootHashResult that contains the state_root_hash as a string.
 */
GetStateRootHashResult Client::GetStateRootHash(uint64_t block_height) {
  nlohmann::json height{std::make_pair("Height", block_height)};
  nlohmann::json block_identifier{std::make_pair("block_identifier", height)};

  return mRpcClient.CallMethodNamed<GetStateRootHashResult>(
      1, "chain_get_state_root_hash", block_identifier);
}

/**
 * @brief Returns the state root hash at a given Block
 *
 * @param block_hash Block hash string of the node. Use empty string to get the
 * state root hash of the latest block.
 * @return GetStateRootHashResult that contains the state_root_hash as a string.
 */
GetStateRootHashResult Client::GetStateRootHash(const std::string& block_hash) {
  nlohmann::json hash{std::make_pair("Hash", block_hash)};
  nlohmann::json block_identifier{std::make_pair("block_identifier", hash)};

  return mRpcClient.CallMethodNamed<GetStateRootHashResult>(
      1, "chain_get_state_root_hash", block_identifier);
}

/**
 * @brief Returns the deploy info.
 *
 * @param deploy_hash Hash string of the smart contract.
 * @return GetDeployInfoResult that contains the deploy info as a string.
 */
GetDeployInfoResult Client::GetDeployInfo(const std::string& deploy_hash) {
  nlohmann::json hash{std::make_pair("deploy_hash", deploy_hash)};

  return mRpcClient.CallMethodNamed<GetDeployInfoResult>(
      1, "info_get_deploy", hash);
}

/**
 * @brief Returns the status info.
 *
 * @return GetStatusInfoResult that contains the status info as a string.
 */
GetStatusInfoResult Client::GetStatusInfo() {

  return mRpcClient.CallMethodNamed<GetStatusInfoResult>(1, "info_get_status");
}

}  // namespace Casper
