#pragma once

#include "JsonRpc/ResultTypes/RpcResult.h"
#include "Types/Definitions.h"  // big_int

/**
 * @brief Result for the "state_get_balance" rpc call.
 *
 */
namespace Casper {

struct GetBalanceResult : public RpcResult {
  /**
   * @brief Construct a new GetBalanceResult object.
   *
   */

  GetBalanceResult(big_int balanceValue, std::string merkleProof)
      : balance_value{balanceValue}, merkle_proof{merkleProof} {}

  GetBalanceResult() {}

  /// The balance value as a big integer.
  big_int balance_value;

  /// The merkle proof as a string
  std::string merkle_proof;
};

/**
 * @brief Construct a JSON object from a GetBalanceResult object.
 *
 * @param j JSON object to construct.
 * @param p GetBalanceResult Result object to construct from.
 */
inline void to_json(nlohmann::json& j, const GetBalanceResult& p) {
  j = static_cast<RpcResult>(p);
  j["balance_value"] = p.balance_value.toString();
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
