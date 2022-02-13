#pragma once
#include <vector>

#include "Types/Definitions.h"
#include "Types/Delegator.h"
#include "Types/PublicKey.h"
#include "Types/StoredValueTypeBase.h"
#include "Types/URef.h"
#include "Types/VestingSchedule.h"

namespace Casper {
/// <summary>
/// An entry in a founding validator map representing a bid.
/// </summary>
struct Bid : public StoredValueTypeBase {
  const StoredValueType type;

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
      : type(StoredValueType::BID),
        validator_public_key(validator_public_key_),
        bonding_purse(bonding_purse_),
        staked_amount(staked_amount_),
        delegation_rate(delegation_rate_),
        vesting_schedule(vesting_schedule_),
        delegators(delegators_),
        inactive(inactive_) {}

  Bid() : type(StoredValueType::BID) {}
};
}  // namespace Casper
