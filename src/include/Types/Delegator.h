#pragma once

#include <optional>

#include "Base.h"
#include "Types/URef.h"
#include "Types/VestingSchedule.h"
#include "nlohmann/json.hpp"

namespace Casper {
/// <summary>
/// A delegator associated with the given validator.
/// </summary>
struct Delegator {
  /// <summary>
  /// Public Key of the delegator
  /// </summary>
  PublicKey delegator_public_key;

  /// <summary>
  /// Amount of Casper token delegated
  /// </summary>
  uint512_t staked_amount;

  /// <summary>
  /// The purse that was used for delegating.
  /// </summary>
  URef bonding_purse;

  /// <summary>
  /// Public key of the validator
  /// </summary>
  PublicKey validator_public_key;

  std::optional<VestingSchedule> vesting_schedule = std::nullopt;

  Delegator() {}
};
/**
 * @brief Construct a JSON object from a Delegator object.
 *
 * @param j JSON object to construct.
 * @param p Delegator object to construct from.
 */
inline void to_json(nlohmann::json& j, const Delegator& p) {
  j = nlohmann::json{{"delegator_public_key", p.delegator_public_key},
                     {"staked_amount", p.staked_amount},
                     {"bonding_purse", p.bonding_purse},
                     {"validator_public_key", p.validator_public_key}};

  if (p.vesting_schedule.has_value()) {
    j["vesting_schedule"] = p.vesting_schedule.value();
  }
}

/**
 * @brief Construct a Delegator object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p Delegator object to construct.
 */
inline void from_json(const nlohmann::json& j, Delegator& p) {
  if (j.count("delegator_public_key") != 0) {
    j.at("delegator_public_key").get_to(p.delegator_public_key);
  } else if (j.count("public_key") != 0) {
    j.at("public_key").get_to(p.delegator_public_key);
  }

  if (j.count("staked_amount") != 0) {
    j.at("staked_amount").get_to(p.staked_amount);
  }

  if (j.count("bonding_purse") != 0) {
    j.at("bonding_purse").get_to(p.bonding_purse);
  }

  if (j.count("validator_public_key") != 0) {
    j.at("validator_public_key").get_to(p.validator_public_key);
  } else if (j.count("delegatee") != 0) {
    j.at("delegatee").get_to(p.validator_public_key);
  }

  if (j.find("vesting_schedule") != j.end() &&
      !j.at("vesting_schedule").is_null()) {
    p.vesting_schedule = j.at("vesting_schedule").get<VestingSchedule>();
  }
}
}  // namespace Casper
