#pragma once

#include "Base.h"
#include "JsonRpc/ResultTypes/RpcResult.h"
#include "Types/JsonBlock.h"
#include "Types/Transfer.h"
#include "nlohmann/json.hpp"

/**
 * @brief Result for the "chain_get_block" rpc call.
 *
 */
namespace Casper {
struct GetBlockResult : public RpcResult {
  /**
   * @brief Construct a new GetBlockResult object.
   *
   */
  GetBlockResult(JsonBlock block_) : block(block_) {}

  GetBlockResult() {}

  JsonBlock block;
};

/**
 * @brief Construct a JSON object from a GetBlockResult object.
 *
 * @param j JSON object to construct.
 * @param p GetBlockResult Result object to construct from.
 */
inline void to_json(nlohmann::json& j, const GetBlockResult& p) {
  j = static_cast<RpcResult>(p);
  j["block"] = p.block;
}

/**
 * @brief Construct a GetBlockResult object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p GetBlockResult object to construct.
 */
inline void from_json(const nlohmann::json& j, GetBlockResult& p) {
  nlohmann::from_json(j, static_cast<RpcResult&>(p));
  j.at("block").get_to(p.block);
}
}  // namespace Casper
