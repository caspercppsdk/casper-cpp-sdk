#pragma once

#include "JsonRpc/ResultTypes/RpcResult.h"

namespace Casper {

/// Result for the "state_get_balance" rpc call.
struct GetBalanceResult : public RpcResult {
  /// <summary>
  /// The balance value as a big integer.
  /// </summary>
  uint512_t balance_value;

  /// <summary>
  /// The merkle proof as a string
  /// </summary>
  std::string merkle_proof;

  GetBalanceResult() {}
};

/**
 * @brief Construct a JSON object from a GetBalanceResult object.
 *
 * @param j JSON object to construct.
 * @param p GetBalanceResult Result object to construct from.
 */
inline void to_json(nlohmann::json& j, const GetBalanceResult& p) {
  j = static_cast<RpcResult>(p);
  j["balance_value"] = p.balance_value;
  j["merkle_proof"] = p.merkle_proof;
}

/**
 * @brief Construct a GetBalanceResult object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p GetBalanceResult object to construct.
 */
inline void from_json(const nlohmann::json& j, GetBalanceResult& p) {
  nlohmann::from_json(j, static_cast<RpcResult&>(p));
  j.at("balance_value").get_to(p.balance_value);
  j.at("merkle_proof").get_to(p.merkle_proof);
}

}  // namespace Casper
