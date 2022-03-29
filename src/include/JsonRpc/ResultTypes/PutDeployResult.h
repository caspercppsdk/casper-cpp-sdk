#pragma once

#include "RpcResult.h"

namespace Casper {

/// Result for "account_put_deploy" RPC response.
struct PutDeployResult : public RpcResult {
  /// <summary>
  /// The deploy hash.
  /// </summary>
  std::string deploy_hash;

  PutDeployResult() {}
};

/**
 * @brief Construct a JSON object from a PutDeployResult object.
 *
 * @param j JSON object to construct.
 * @param p PutDeployResult Result object to construct from.
 */
inline void to_json(nlohmann::json& j, const PutDeployResult& p) {
  j = static_cast<RpcResult>(p);
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
  j.at("deploy_hash").get_to(p.deploy_hash);
}

}  // namespace Casper
