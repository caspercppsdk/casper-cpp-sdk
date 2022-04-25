#pragma once

#include "Types/PublicKey.h"
#include "Types/URef.h"

namespace Casper {
/// <summary>
/// Information of an unbonding or delegation withdrawal
/// </summary>
struct UnbondingPurse {
  URef bonding_purse;

  /// <summary>
  /// Validators public key.
  /// </summary>
  PublicKey validator_public_key;

  /// <summary>
  /// Unbonder public key.
  /// </summary>
  PublicKey unbonder_public_key;

  /// <summary>
  /// Era in which this unbonding request was created.
  /// </summary>
  uint64_t era_of_creation;

  /// <summary>
  /// Unbonding Amount.
  /// </summary>
  uint512_t amount;

  UnbondingPurse() {}
};

// to_json of UnbondingPurse
inline void to_json(nlohmann::json& j, const UnbondingPurse& p) {
  j = {{"bonding_purse", p.bonding_purse},
       {"validator_public_key", p.validator_public_key},
       {"unbonder_public_key", p.unbonder_public_key},
       {"era_of_creation", p.era_of_creation},
       {"amount", p.amount}};
}

// from_json of UnbondingPurse
inline void from_json(const nlohmann::json& j, UnbondingPurse& p) {
  j.at("bonding_purse").get_to(p.bonding_purse);
  j.at("validator_public_key").get_to(p.validator_public_key);
  j.at("unbonder_public_key").get_to(p.unbonder_public_key);
  j.at("era_of_creation").get_to(p.era_of_creation);
  j.at("amount").get_to(p.amount);
}

}  // namespace Casper
