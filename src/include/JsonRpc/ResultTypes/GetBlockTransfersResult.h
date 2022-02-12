#pragma once

#include "Base.h"
#include "JsonRpc/ResultTypes/RpcResult.h"
#include "Types/Transfer.h"

/**
 * @brief Result for the "chain_get_block_transfers" rpc call.
 *
 */
namespace Casper {
struct GetBlockTransfersResult : public RpcResult {
 public:
  /**
   * @brief Construct a new GetBlockTransfersResult object.
   *
   */
  GetBlockTransfersResult(std::string blockHash,
                          std::vector<Transfer> transfers)
      : block_hash(blockHash), transfers(transfers) {}

  GetBlockTransfersResult() {}

  std::string block_hash;
  std::vector<Transfer> transfers;
};

/**
 * @brief Construct a JSON object from a GetBlockTransfersResult object.
 *
 * @param j JSON object to construct.
 * @param p GetBlockTransfersResult Result object to construct from.
 */
inline void to_json(nlohmann::json& j, const GetBlockTransfersResult& p) {
  j = static_cast<RpcResult>(p);
  j["block_hash"] = p.block_hash;
  j["transfers"] = p.transfers;
}

/**
 * @brief Construct a GetBlockTransfersResult object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p GetBlockTransfersResult object to construct.
 */
inline void from_json(const nlohmann::json& j, GetBlockTransfersResult& p) {
  nlohmann::from_json(j, static_cast<RpcResult&>(p));
  j.at("block_hash").get_to(p.block_hash);
  j.at("transfers").get_to(p.transfers);
}
}  // namespace Casper
