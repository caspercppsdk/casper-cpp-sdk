#pragma once

#include <cstdint>
#include <vector>

#include "Types/PublicKey.h"

namespace Casper {
/// <summary>
/// A change to a validator's status between two eras.
/// </summary>
enum ValidatorChange {
  /// <summary>
  /// The validator got newly added to the validator set.
  /// </summary>
  Added,
  /// <summary>
  /// The validator was removed from the validator set.
  /// </summary>
  Removed,
  /// <summary>
  /// The validator was banned from this era.
  /// </summary>
  Banned,
  /// <summary>
  /// The validator was excluded from proposing new blocks in this era.
  /// </summary>
  CannotPropose,
  /// <summary>
  /// We saw the validator misbehave in this era.
  /// </summary>
  SeenAsFaulty
};

/// <summary>
/// A single change to a validator's status in the given era.
/// </summary>
struct ValidatorStatusChange {
  /// <summary>
  /// The era in which the change occurred.
  /// </summary>
  uint64_t era_id;

  /// <summary>
  /// The change in validator status.
  /// </summary>
  ValidatorChange validator_change;
};

/// <summary>
/// The changes in a validator's status.
/// </summary>

struct ValidatorChanges {
  /// <summary>
  /// The public key of the validator.
  /// </summary>
  PublicKey public_key;

  /// <summary>
  /// The set of changes to the validator's status.
  /// </summary>
  /// <returns></returns>
  std::vector<ValidatorStatusChange> status_changes;
};
}  // namespace Casper
