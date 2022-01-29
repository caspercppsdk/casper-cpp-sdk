#pragma once

#include <string>
#include <vector>

#include "Types/PublicKey.h"
#include "Types/ValidatorWeight.h"

namespace Casper {
/// <summary>
/// A validator reward
/// </summary>
struct Reward {
  /// <summary>
  /// Reward amount
  /// </summary>
  uint64_t amount;

  /// <summary>
  /// Validator public key
  /// </summary>
  PublicKey validator;
};

/// <summary>
/// Equivocation and reward information to be included in the terminal block.
/// </summary>
struct EraReport {
  /// <summary>
  /// List of public keys of the equivocators
  /// </summary>
  std::vector<PublicKey> equivocators;

  /// <summary>
  /// List of public keys of inactive validators
  /// </summary>
  std::vector<PublicKey> inactive_validators;

  /// <summary>
  /// List of validators with rewards
  /// </summary>
  std::vector<Reward> rewards;
};

/// <summary>
/// Era end report and list of validator weights for next era
/// </summary>
struct EraEnd {
  /// <summary>
  /// Era report
  /// </summary>
  EraReport era_report;

  /// <summary>
  /// A list of validator weights for the next era
  /// </summary>
  std::vector<ValidatorWeight> next_era_validator_weights;
};
}  // namespace Casper
