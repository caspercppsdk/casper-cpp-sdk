#pragma once

#include "Base.h"
#include "Types/StoredValue.h"
#include "nlohmann/json.hpp"

namespace Casper {

/// <summary>
/// The summary of an era
/// </summary>
struct EraSummary {
  /// <summary>
  /// The block hash
  /// </summary>
  std::string block_hash;

  /// <summary>
  /// The Era Id
  /// </summary>
  uint64_t era_id;

  /// <summary>
  /// The StoredValue containing era information.
  /// </summary>
  StoredValue stored_value;

  /// <summary>
  /// Hex-encoded hash of the state root.
  /// </summary>
  std::string state_root_hash;

  /// <summary>
  /// The merkle proof.
  /// </summary>
  std::string merkle_proof;

  EraSummary() {}
};

/**
 * @brief Construct a JSON object from a EraSummary object.
 *
 * @param j JSON object to construct.
 * @param p EraSummary object to construct from.
 */
inline void to_json(nlohmann::json& j, const EraSummary& p) {
  j = nlohmann::json{
      {"block_hash", p.block_hash},     {"era_id", p.era_id},
      {"stored_value", p.stored_value}, {"state_root_hash", p.state_root_hash},
      {"merkle_proof", p.merkle_proof},
  };
}

/**
 * @brief Construct a EraSummary object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p EraSummary object to construct.
 */
inline void from_json(const nlohmann::json& j, EraSummary& p) {
  j.at("block_hash").get_to(p.block_hash);
  j.at("era_id").get_to(p.era_id);
  j.at("stored_value").get_to(p.stored_value);
  j.at("state_root_hash").get_to(p.state_root_hash);
  j.at("merkle_proof").get_to(p.merkle_proof);
}

}  // namespace Casper