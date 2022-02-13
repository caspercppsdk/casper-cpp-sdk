#pragma once
#include <vector>

#include "Types/Definitions.h"
#include "Types/Delegator.h"
#include "Types/PublicKey.h"
#include "Types/StoredValueTypeBase.h"
#include "Types/URef.h"
#include "Types/VestingSchedule.h"

#include "Utils/CryptoUtil.h"
namespace Casper {
/// <summary>
/// An entry in a founding validator map representing a bid.
/// </summary>
struct Bid : public StoredValueTypeBase {
  /// <summary>
  /// Validator public key
  /// </summary>
  // TODO: [JsonConverter(typeof(PublicKey.PublicKeyConverter))]
  PublicKey validator_public_key;

  /// <summary>
  /// The purse that was used for bonding.
  /// </summary>
  URef bonding_purse;

  /// <summary>
  /// The amount of tokens staked by a validator (not including
  /// delegators).
  /// </summary>
  // TODO: [JsonConverter(typeof(BigIntegerConverter))]
  big_int staked_amount;

  /// <summary>
  /// The delegation rate.
  /// </summary>
  /// <returns></returns>
  unsigned int delegation_rate;

  /// <summary>
  /// Vesting schedule for a genesis
  /// validator. `None` if non-genesis
  /// validator.
  /// </summary>
  VestingSchedule vesting_schedule;

  /// <summary>
  /// The delegators.
  /// </summary>

  std::vector<Delegator> delegators;

  /// <summary>
  /// `true` if validator has been "evicted"
  /// </summary>
  bool inactive;

  Bid(PublicKey validator_public_key_,
      URef bonding_purse_,
      big_int staked_amount_,
      unsigned int delegation_rate_,
      VestingSchedule vesting_schedule_,
      std::vector<Delegator> delegators_,
      bool inactive_)
      : StoredValueTypeBase::StoredValueTypeBase(StoredValueType::BID),
        validator_public_key(validator_public_key_),
        bonding_purse(bonding_purse_),
        staked_amount(staked_amount_),
        delegation_rate(delegation_rate_),
        vesting_schedule(vesting_schedule_),
        delegators(delegators_),
        inactive(inactive_) {}

  Bid() : StoredValueTypeBase::StoredValueTypeBase(StoredValueType::BID) {}
};

/**
 * @brief Construct a JSON object from a Bid object.
 *
 * @param j JSON object to construct.
 * @param p Bid object to construct from.
 */
inline void to_json(nlohmann::json& j, const Bid& p) {
  j = nlohmann::json{
      {"validator_public_key", p.validator_public_key.ToAccountHex()},  // done
      {"bonding_purse", p.bonding_purse.ToString()},                    // done
      {"staked_amount", p.staked_amount.toString()},                    // done
      {"delegation_rate", p.delegation_rate},                           // done
      {"vesting_schedule", p.vesting_schedule},
      {"delegators", p.delegators},
      {"inactive", p.inactive},  // done
  };
  // TODO:[JsonConverter(typeof(BidsListConverter))]
}

/**
 * @brief Construct a Bid object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p Bid object to construct.
 */
inline void from_json(const nlohmann::json& j, Bid& p) {
  /*
  p.validator_public_key =
      PublicKey::FromHexString(j.at("validator_public_key"));

  p.bonding_purse = URef(j.at("bonding_purse").get<std::string>());

  p.staked_amount = j.at("staked_amount").get<std::string>();

  p.delegation_rate = j.at("delegation_rate").get<unsigned int>();

  p.vesting_schedule = j.at("vesting_schedule");
  p.delegators = j.at("delegators");

  p.inactive = j.at("inactive").get<bool>();
  */
  // TODO:[JsonConverter(typeof(BidsListConverter))]
}

}  // namespace Casper
