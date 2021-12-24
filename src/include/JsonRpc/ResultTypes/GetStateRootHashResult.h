#pragma once

#include "RpcResult.h"

/**
 * @brief Result for the "chain_get_state_root_hash" rpc call.
 *
 */
namespace Casper {
struct GetStateRootHashResult : public RpcResult {
 public:
  /**
   * @brief Construct a new GetStateRootHashResult object.
   *
   */
  GetStateRootHashResult() : state_root_hash() {}

  /// The state root hash as a string.
  std::string state_root_hash;
};

/**
 * @brief Construct a JSON object from a GetStateRootHashResult object.
 *
 * @param j JSON object to construct.
 * @param p GetStateRootHash Result object to construct from.
 */
inline void to_json(nlohmann::json& j, const GetStateRootHashResult& p) {
  j = nlohmann::json{{"state_root_hash", p.state_root_hash}};
}

/**
 * @brief Construct a GetStateRootHashResult object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p GetStateRootHashResult object to construct.
 */
inline void from_json(const nlohmann::json& j, GetStateRootHashResult& p) {
  j.at("state_root_hash").get_to(p.state_root_hash);
}
}  // namespace Casper
