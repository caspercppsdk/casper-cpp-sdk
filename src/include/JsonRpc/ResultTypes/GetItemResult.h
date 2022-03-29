#pragma once

#include "JsonRpc/ResultTypes/RpcResult.h"
#include "Types/StoredValue.h"

namespace Casper {

/// Result for the "state_get_item" rpc call.
struct GetItemResult : public RpcResult {
  /// <summary>
  /// The stored value.
  /// </summary>
  StoredValue stored_value;

  /// <summary>
  /// The merkle proof.
  /// </summary>
  std::string merkle_proof;

  GetItemResult() {}
};

/**
 * @brief Construct a JSON object from a GetItemResult object.
 *
 * @param j JSON object to construct.
 * @param p GetStateRootHash Result object to construct from.
 */
inline void to_json(nlohmann::json& j, const GetItemResult& p) {
  j = static_cast<RpcResult>(p);
  j["stored_value"] = p.stored_value;
  j["merkle_proof"] = p.merkle_proof;
}

/**
 * @brief Construct a GetItemResult object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p GetItemResult object to construct.
 */
inline void from_json(const nlohmann::json& j, GetItemResult& p) {
  nlohmann::from_json(j, static_cast<RpcResult&>(p));
  j.at("stored_value").get_to(p.stored_value);
  j.at("merkle_proof").get_to(p.merkle_proof);
}

}  // namespace Casper
