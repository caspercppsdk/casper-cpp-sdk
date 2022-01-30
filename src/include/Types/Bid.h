#pragma once
#include <vector>

#include "Definitions.h"
#include "Types/Delegator.h"
#include "Types/PublicKey.h"
#include "Types/URef.h"
#include "Types/VestingSchedule.h"
#include "Types/StoredValueTypeBase.h"

namespace Casper {
/// <summary>
/// An entry in a founding validator map representing a bid.
/// </summary>
struct Bid : public StoredValueTypeBase {
  const StoredValueType type;

  /// <summary>
  /// The purse that was used for bonding.
  /// </summary>
  URef bonding_purse;

  /// <summary>
  /// The delegation rate.
  /// </summary>
  /// <returns></returns>
  unsigned int delegation_rate;

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
  big_int taked_amount;

  /// <summary>
  /// Validator public key
  /// </summary>
  PublicKey validator_public_key;

  /// <summary>
  /// Vesting schedule for a genesis
  /// validator. `None` if non-genesis
  /// validator.
  /// </summary>
  VestingSchedule vesting_schedule;

  Bid () : type(StoredValueType::BID) {}
};
}  // namespace Casper
