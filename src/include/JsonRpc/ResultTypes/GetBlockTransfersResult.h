#pragma once

#include "Base.h"
#include "JsonRpc/ResultTypes/RpcResult.h"
#include "Types/Transfer.h"

namespace Casper {

/// Result for the "chain_get_block_transfers" rpc call.
struct GetBlockTransfersResult : public RpcResult {
  /// <summary>
  /// The block hash, if found.
  /// </summary>
  std::optional<std::string> block_hash = std::nullopt;

  /// <summary>
  /// The block's transfers, if found.
  /// </summary>
  std::optional<std::vector<Transfer>> transfers = std::nullopt;

  GetBlockTransfersResult() {}
};

/**
 * @brief Construct a JSON object from a GetBlockTransfersResult object.
 *
 * @param j JSON object to construct.
 * @param p GetBlockTransfersResult Result object to construct from.
 */
inline void to_json(nlohmann::json& j, const GetBlockTransfersResult& p) {
  j = static_cast<RpcResult>(p);

  if (p.block_hash.has_value()) {
    j["block_hash"] = p.block_hash.value();
  }

  if (p.transfers.has_value()) {
    j["transfers"] = p.transfers.value();
  }
}

/**
 * @brief Construct a GetBlockTransfersResult object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p GetBlockTransfersResult object to construct.
 */
inline void from_json(const nlohmann::json& j, GetBlockTransfersResult& p) {
  nlohmann::from_json(j, static_cast<RpcResult&>(p));
  if (j.find("block_hash") != j.end() && !j.at("block_hash").is_null()) {
    j.at("block_hash").get_to(p.block_hash);
  }

  if (j.find("transfers") != j.end() && !j.at("transfers").is_null()) {
    p.transfers = j.at("transfers").get<std::vector<Transfer>>();
  }
}

}  // namespace Casper
