#pragma once

#include "JsonRpc/ResultTypes/RpcResult.h"
#include "Types/AuctionState.h"

namespace Casper {

/**
 * @brief Result for the "state_get_auction_info" rpc call.
 *
 */
struct GetAuctionInfoResult : public RpcResult {
  /// The auction state.
  AuctionState auction_state;

  /**
   * @brief Construct a new GetAuctionInfoResult object.
   *
   */
  GetAuctionInfoResult() {}
};

/**
 * @brief Construct a JSON object from a GetAuctionInfoResult object.
 *
 * @param j JSON object to construct.
 * @param p GetAuctionInfoResult Result object to construct from.
 */
inline void to_json(nlohmann::json& j, const GetAuctionInfoResult& p) {
  j = static_cast<RpcResult>(p);
  j["auction_state"] = p.auction_state;
}

/**
 * @brief Construct a GetAuctionInfoResult object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p GetAuctionInfoResult object to construct.
 */
inline void from_json(const nlohmann::json& j, GetAuctionInfoResult& p) {
  nlohmann::from_json(j, static_cast<RpcResult&>(p));
  j.at("auction_state").get_to(p.auction_state);
}

}  // namespace Casper
