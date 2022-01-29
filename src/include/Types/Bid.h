#pragma once
#include <boost/multiprecision/cpp_int.hpp>
#include <vector>

#include "Types/Delegator.h"
#include "Types/PublicKey.h"
#include "Types/URef.h"
#include "Types/VestingSchedule.h"

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
  boost::multiprecision::uint512_t taked_amount;

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
};
}  // namespace Casper
