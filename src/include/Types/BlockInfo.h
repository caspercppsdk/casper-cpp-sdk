#pragma once

#include "Base.h"
#include "Types/PublicKey.h"
#include "nlohmann/json.hpp"

namespace Casper {
/// <summary>
/// Minimal info of a `Block`.
/// </summary>
struct BlockInfo {
  /// <summary>
  /// Validator node's public key
  /// </summary>
  PublicKey creator;

  /// <summary>
  /// The block era id.
  /// </summary>
  uint64_t era_id;

  /// <summary>
  /// Block hash
  /// </summary>
  std::string hash;

  /// <summary>
  /// Height of the block
  /// </summary>
  uint64_t height;

  /// <summary>
  /// The state root hash.
  /// </summary>
  std::string state_root_hash;

  /// <summary>
  /// The block timestamp.
  /// </summary>
  std::string timestamp;

  BlockInfo() {}
};

/**
 * @brief Construct a JSON object from a BlockInfo object.
 *
 * @param j JSON object to construct.
 * @param p BlockInfo object to construct from.
 */
inline void to_json(nlohmann::json& j, const BlockInfo& p) {
  j = nlohmann::json{{"creator", p.creator},
                     {"era_id", p.era_id},
                     {"hash", p.hash},
                     {"height", p.height},
                     {"state_root_hash", p.state_root_hash},
                     {"timestamp", p.timestamp}};
}

/**
 * @brief Construct a BlockInfo object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p BlockInfo object to construct.
 */
inline void from_json(const nlohmann::json& j, BlockInfo& p) {
  j.at("creator").get_to(p.creator);
  j.at("era_id").get_to(p.era_id);
  j.at("hash").get_to(p.hash);
  j.at("height").get_to(p.height);
  j.at("state_root_hash").get_to(p.state_root_hash);
  j.at("timestamp").get_to(p.timestamp);
}

}  // namespace Casper