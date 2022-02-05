#pragma once

#include <string>
#include <vector>

#include "Types/GlobalStateKey.h"
#include "Types/NamedKey.h"
#include "Types/StoredValue.h"
#include "Types/URef.h"

namespace Casper {
struct ActionThresholds {
  /// <summary>
  /// Threshold that has to be met for a deployment action
  /// </summary>
  unsigned int deployment;  // deployment

  /// <summary>
  /// Threshold that has to be met for a key management action
  /// </summary>
  unsigned int key_management;  // key_management
};

/// <summary>
/// public key allowed to provide signatures on deploys for the account
/// </summary>
struct AssociatedKey {
  /// <summary>
  /// Hash derived from the public key
  /// </summary>
  std::string account_hash;

  /// <summary>
  /// Weight of the associated key
  /// </summary>
  unsigned int weight;
};

/// <summary>
/// Structure representing a user's account, stored in global state.
/// </summary>
struct Account : public StoredValueTypeBase {
  const StoredValueType type;

  Account() : type(StoredValueType::ACCOUNT) {}

  /// <summary>
  /// Account identity key
  /// </summary>
  std::string account_hash;

  /// <summary>
  /// Thresholds that have to be met when executing an action of a certain type.
  /// </summary>
  ActionThresholds action_thresholds;

  /// <summary>
  /// Set of public keys allowed to provide signatures on deploys for the
  /// account
  /// </summary>
  std::vector<AssociatedKey> associated_keys;

  /// <summary>
  /// Purse that can hold Casper tokens
  /// </summary>
  URef main_purse;

  /// <summary>
  /// Collection of named keys
  /// </summary>
  std::vector<NamedKey> named_keys;
};
}  // namespace Casper
