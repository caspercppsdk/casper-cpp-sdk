#pragma once

#include "RpcResult.h"

namespace Casper {
/**
 * @brief Result for the "chain_get_state_root_hash" rpc call.
 *
 */
struct PutDeployResult : public RpcResult {
 public:
  /**
   * @brief Construct a new PutDeployResult object.
   *
   */
  PutDeployResult() {}
  PutDeployResult(std::string api_version_, std::string deploy_hash_) : api_version(api_version_), deploy_hash(deploy_hash_) {}
  /// The state root hash as a string.
  std::string api_version;
  std::string deploy_hash;
};

/**
 * @brief Construct a JSON object from a PutDeployResult object.
 *
 * @param j JSON object to construct.
 * @param p GetStateRootHash Result object to construct from.
 */
inline void to_json(nlohmann::json& j, const PutDeployResult& p) {
  j = static_cast<RpcResult>(p);
  j["api_version"] = p.api_version;
  j["deploy_hash"] = p.deploy_hash;
}

/**
 * @brief Construct a PutDeployResult object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p PutDeployResult object to construct.
 */
inline void from_json(const nlohmann::json& j, PutDeployResult& p) {
  nlohmann::from_json(j, static_cast<RpcResult&>(p));
  j.at("api_version").get_to(p.api_version);
  j.at("deploy_hash").get_to(p.deploy_hash);
}

}  // namespace Casper
