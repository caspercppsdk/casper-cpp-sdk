#pragma once

#include "Base.h"
#include "Types/EraValidators.h"
#include "Types/ValidatorBid.h"

namespace Casper {
/// <summary>
/// Auction contract data.
/// </summary>
struct AuctionState {
  /// <summary>
  /// Global state hash.
  /// </summary>
  std::string state_root_hash;

  /// <summary>
  /// Block height.
  /// </summary>
  uint64_t block_height;

  /// <summary>
  /// Era validators.
  /// </summary>
  std::vector<EraValidators> era_validators;

  /// <summary>
  /// All bids contained within a vector.
  /// </summary>
  std::vector<ValidatorBid> bids;

  AuctionState() {}
};

/**
 * @brief Construct a JSON object from a AuctionState object.
 *
 * @param j JSON object to construct.
 * @param p AuctionState object to construct from.
 */
inline void to_json(nlohmann::json& j, const AuctionState& p) {
  j = nlohmann::json{{"state_root_hash", p.state_root_hash},
                     {"block_height", p.block_height},
                     {"era_validators", p.era_validators},
                     {"bids", p.bids}};
}

/**
 * @brief Construct a AuctionState object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p AuctionState object to construct.
 */
inline void from_json(const nlohmann::json& j, AuctionState& p) {
  j.at("state_root_hash").get_to(p.state_root_hash);
  j.at("block_height").get_to(p.block_height);
  j.at("era_validators").get_to(p.era_validators);
  j.at("bids").get_to(p.bids);
}
}  // namespace Casper
