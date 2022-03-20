#pragma once

#include "Base.h"
#include "Types/StoredValue.h"
#include "nlohmann/json.hpp"

namespace Casper {

struct EraSummary {
  std::string block_hash;
  uint64_t era_id;
  StoredValue stored_value;
  std::string state_root_hash;
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