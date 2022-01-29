#pragma once

#include <boost/multiprecision/cpp_int.hpp>

#include "Types/PublicKey.h"
#include "Types/URef.h"

namespace Casper {
/// <summary>
/// Information of an unbonding or delegation withdrawal
/// </summary>
struct UnbondingPurse {
  /// <summary>
  /// Unbonding Amount.
  /// </summary>

  boost::multiprecision::uint512_t amount;

  URef bonding_purse;

  /// <summary>
  /// Era in which this unbonding request was created.
  /// </summary>
  uint64_t era_of_creation;

  /// <summary>
  /// Unbonder public key.
  /// </summary>
  PublicKey unbonder_public_key;

  /// <summary>
  /// Validators public key.
  /// </summary>
  PublicKey validator_public_key;
};
}  // namespace Casper
