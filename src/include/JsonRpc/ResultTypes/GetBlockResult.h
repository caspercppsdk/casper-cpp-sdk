#pragma once

#include <optional>

#include "Base.h"
#include "JsonRpc/ResultTypes/RpcResult.h"
#include "Types/Block.h"
#include "Types/Transfer.h"
#include "nlohmann/json.hpp"

namespace Casper {

/// Result for the "chain_get_block" rpc call.
struct GetBlockResult : public RpcResult {
  /// <summary>
  /// The block as a JSON-friendly object.
  /// </summary>
  std::optional<Block> block = std::nullopt;

  GetBlockResult() {}
};

/**
 * @brief Construct a JSON object from a GetBlockResult object.
 *
 * @param j JSON object to construct.
 * @param p GetBlockResult Result object to construct from.
 */
inline void to_json(nlohmann::json& j, const GetBlockResult& p) {
  j = static_cast<RpcResult>(p);
  if (p.block.has_value()) {
    j["block"] = p.block.value();
  }
}

/**
 * @brief Construct a GetBlockResult object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p GetBlockResult object to construct.
 */
inline void from_json(const nlohmann::json& j, GetBlockResult& p) {
  nlohmann::from_json(j, static_cast<RpcResult&>(p));
  if (j.find("block") != j.end() && !j.at("block").is_null()) {
    p.block = j.at("block").get<Block>();
  }
}

}  // namespace Casper
