#pragma once

#include <vector>

#include "RpcResult.h"
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
  GetBlockTransfersResult() {}

  std::string api_version;
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
  j = nlohmann::json{{"api_version", p.api_version},
                     {"block_hash", p.block_hash},
                     {"transfers", p.transfers}};
}

/**
 * @brief Construct a GetBlockTransfersResult object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p GetBlockTransfersResult object to construct.
 */
inline void from_json(const nlohmann::json& j, GetBlockTransfersResult& p) {
  j.at("api_version").get_to(p.api_version);

  if (!j.at("block_hash").is_null()) j.at("block_hash").get_to(p.block_hash);

  if (j.at("transfers").is_array()) {
    auto t = j.at("transfers").begin();

    while (t != j.at("transfers").end()) {
      Transfer rec = Transfer();
      rec.deploy_hash = (*t).at("deploy_hash");
      rec.from = (*t).at("from");

      if (!(*t).at("to").is_null()) rec.to = (*t).at("to");

      rec.source = (*t).at("source");
      rec.target = (*t).at("target");
      rec.amount = (*t).at("amount");
      rec.gas = (*t).at("gas");

      if (!(*t).at("id").is_null()) rec.id = (*t).at("id");

      p.transfers.push_back(rec);
      ++t;
    }
  }
}
}  // namespace Casper
