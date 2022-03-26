#pragma once

#include "Base.h"
#include "Types/GlobalStateKey.h"
#include "Types/NamedKey.h"
#include "Types/StoredValue.h"
#include "Types/URef.h"

namespace Casper {

/// <summary>
/// Thresholds that have to be met when executing an action of a certain type.
/// </summary>
struct ActionThresholds {
  /// <summary>
  /// Threshold that has to be met for a deployment action
  /// </summary>
  uint8_t deployment;

  /// <summary>
  /// Threshold that has to be met for a key management action
  /// </summary>
  uint8_t key_management;

  ActionThresholds() {}
};

/**
 * @brief Construct a JSON object from a ActionThresholds object.
 *
 * @param j JSON object to construct.
 * @param p ActionThresholds object to construct from.
 */
inline void to_json(nlohmann::json& j, const ActionThresholds& p) {
  j = {{"deployment", p.deployment}, {"key_management", p.key_management}};
}

/**
 * @brief Construct a ActionThresholds object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p ActionThresholds object to construct.
 */
inline void from_json(const nlohmann::json& j, ActionThresholds& p) {
  j.at("deployment").get_to(p.deployment);
  j.at("key_management").get_to(p.key_management);
}

/// <summary>
/// Public Key allowed to provide signatures on deploys for the account
/// </summary>
struct AssociatedKey {
  /// <summary>
  /// Hash derived from the public key
  /// </summary>
  std::string account_hash;

  /// <summary>
  /// Weight of the associated key
  /// </summary>
  uint8_t weight;

  AssociatedKey() {}
};

/**
 * @brief Construct a JSON object from a AssociatedKey object.
 *
 * @param j JSON object to construct.
 * @param p AssociatedKey object to construct from.
 */
inline void to_json(nlohmann::json& j, const AssociatedKey& p) {
  j = {{"account_hash", p.account_hash}, {"weight", p.weight}};
}

/**
 * @brief Construct a AssociatedKey object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p AssociatedKey object to construct.
 */
inline void from_json(const nlohmann::json& j, AssociatedKey& p) {
  j.at("account_hash").get_to(p.account_hash);
  j.at("weight").get_to(p.weight);
}

/// <summary>
/// Structure representing a user's account, stored in global state.
/// </summary>
struct Account {
  /// <summary>
  /// Account identity key
  /// </summary>
  std::string account_hash;

  /// <summary>
  /// Collection of named keys
  /// </summary>
  std::vector<NamedKey> named_keys;

  /// <summary>
  /// Purse that can hold Casper tokens
  /// </summary>
  URef main_purse;

  /// <summary>
  /// Set of public keys allowed to provide signatures on deploys for the
  /// account
  /// </summary>
  std::vector<AssociatedKey> associated_keys;

  /// <summary>
  /// Thresholds that have to be met when executing an action of a certain
  /// type.
  /// </summary>
  ActionThresholds action_thresholds;

  Account() {}
};

/**
 * @brief Construct a JSON object from a Account object.
 *
 * @param j JSON object to construct.
 * @param p Account object to construct from.
 */
inline void to_json(nlohmann::json& j, const Account& p) {
  j = nlohmann::json{
      {"account_hash", p.account_hash},
      {"named_keys", p.named_keys},
      {"main_purse", p.main_purse},
      {"associated_keys", p.associated_keys},
      {"action_thresholds", p.action_thresholds},
  };
}

/**
 * @brief Construct a Account object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p Account object to construct.
 */
inline void from_json(const nlohmann::json& j, Account& p) {
  j.at("account_hash").get_to(p.account_hash);
  j.at("named_keys").get_to(p.named_keys);
  j.at("main_purse").get_to(p.main_purse);
  j.at("associated_keys").get_to(p.associated_keys);
  j.at("action_thresholds").get_to(p.action_thresholds);
}

}  // namespace Casper
