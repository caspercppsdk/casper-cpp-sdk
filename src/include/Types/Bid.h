#pragma once

#include "Base.h"
#include "Types/Delegator.h"
#include "Types/PublicKey.h"
#include "Types/URef.h"
#include "Types/VestingSchedule.h"
#include "Utils/CryptoUtil.h"
namespace Casper {
/// <summary>
/// An entry in a founding validator map representing a bid.
/// </summary>
struct Bid {
  /// <summary>
  /// The purse that was used for bonding.
  /// </summary>
  URef bonding_purse;

  /// <summary>
  /// The delegation rate.
  /// </summary>
  /// <returns></returns>
  uint8_t delegation_rate;

  /// <summary>
  /// The delegators.
  /// </summary>
  std::vector<Delegator> delegators;

  /// <summary>
  /// `true` if validator has been "evicted"
  /// </summary>
  bool inactive;

  /// <summary>
  /// The amount of tokens staked by a validator (not including
  /// delegators).
  /// </summary>
  uint512_t staked_amount;

  /// <summary>
  /// Validator public key
  /// </summary>
  PublicKey validator_public_key;

  /// <summary>
  /// Vesting schedule for a genesis
  /// validator. `None` if non-genesis
  /// validator.
  /// </summary>
  std::optional<VestingSchedule> vesting_schedule = std::nullopt;

  Bid() {}
};

/**
 * @brief Construct a JSON object from a Bid object.
 *
 * @param j JSON object to construct.
 * @param p Bid object to construct from.
 */
inline void to_json(nlohmann::json& j, const Bid& p) {
  j = {{"validator_public_key", p.validator_public_key},
       {"bonding_purse", p.bonding_purse},
       {"staked_amount", p.staked_amount},
       {"delegation_rate", p.delegation_rate},
       {"delegators", p.delegators},
       {"inactive", p.inactive}};
  if (p.vesting_schedule.has_value()) {
    j["vesting_schedule"] = p.vesting_schedule.value();
  }
}

/**
 * @brief Construct a Bid object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p Bid object to construct.
 */
inline void from_json(const nlohmann::json& j, Bid& p) {
  if (j.count("delegator_public_key") != 0) {
    j.at("validator_public_key").get_to(p.validator_public_key);
  } else if (j.count("public_key") != 0) {
    j.at("public_key").get_to(p.validator_public_key);
  }

  j.at("bonding_purse").get_to(p.bonding_purse);
  j.at("staked_amount").get_to(p.staked_amount);

  p.delegation_rate = j.at("delegation_rate").get<uint8_t>();

  if (j.find("vesting_schedule") != j.end() &&
      !j.at("vesting_schedule").is_null()) {
    p.vesting_schedule = j.at("vesting_schedule").get<VestingSchedule>();
  }

  j.at("delegators").get_to(p.delegators);
  j.at("inactive").get_to(p.inactive);
}

}  // namespace Casper
