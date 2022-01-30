#pragma once
#include <string>
#include <vector>

#include "Types/Bid.h"
#include "Types/EraValidators.h"

namespace Casper {
struct AuctionState {
  /// <summary>
  /// All bids contained within a vector.
  /// </summary>
  std::vector<Bid> bids;

  /// <summary>
  /// Block height.
  /// </summary>
  uint64_t block_height;

  /// <summary>
  /// Era validators.
  /// </summary>
  std::vector<EraValidators> era_validators;

  /// <summary>
  /// Global state hash.
  /// </summary>
  std::string state_root_hash;
};
}  // namespace Casper
