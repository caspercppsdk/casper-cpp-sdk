#pragma once

#include "Base.h"
#include "Types/PublicKey.h"
#include "magic_enum/magic_enum.hpp"
// Crypto
#include <cryptopp/secblock.h>

// JSON
#include "nlohmann/json.hpp"

namespace Casper {
/// <summary>
/// Keys in the global state store information about different data types.
/// <see
/// cref="https://casper.network/docs/design/serialization-standard#serialization-standard-state-keys"/>
/// </summary>

enum class KeyIdentifier {
  /// <summary>
  /// AccountHash keys store accounts in the global state.
  /// </summary>
  Account = 0x00,
  /// <summary>
  /// Hash keys store contracts immutably in the global state.
  /// </summary>
  Hash = 0x01,
  /// <summary>
  /// URef keys store values and manage permissions to interact with the value
  /// stored under the URef.
  /// </summary>
  URef = 0x02,
  /// <summary>
  /// Transfer keys store transfers in the global state.
  /// </summary>
  Transfer = 0x03,
  /// <summary>
  /// DeployInfo keys store information related to deploys in the global state.
  /// </summary>
  DeployInfo = 0x04,
  /// <summary>
  /// EraInfo keys store information related to the Auction metadata for a
  /// particular era.
  /// </summary>
  EraInfo = 0x05,
  /// <summary>
  /// Balance keys store information related to the balance of a given purse.
  /// </summary>
  Balance = 0x06,
  /// <summary>
  /// Bid keys store information related to auction bids in the global state.
  /// </summary>
  Bid = 0x07,
  /// <summary>
  /// Withdraw keys store information related to auction withdraws in the global
  /// state.
  /// </summary>
  Withdraw = 0x08,
  /// <summary>
  /// Dictionary keys store dictionary items.
  /// </summary>
  Dictionary = 0x09
};

/// <summary>
/// Base class for the different global state keys.
/// </summary>
struct GlobalStateKey {
  std::string key;

 public:
  KeyIdentifier key_identifier;
  CBytes raw_bytes;

 protected:
  virtual CBytes _GetRawBytesFromKey(std::string key);

 public:
  GlobalStateKey();

  /// <summary>
  /// Constructor for the GlobalStateKey class.
  /// </summary>
  GlobalStateKey(std::string key_);

  /// <summary>
  /// Constructor for the GlobalStateKey class with key prefix.
  /// </summary>
  GlobalStateKey(std::string key_, std::string key_prefix);

  std::string ToHexString();

  /// <summary>
  /// Converts a global state key from string to its specific key object.
  /// </summary>

  static GlobalStateKey FromString(std::string value);

  /// <summary>
  /// Converts a global state key from a byte array to its specific key object.
  /// First byte in the array indicates the Key identifier.
  /// </summary>
  static GlobalStateKey FromBytes(const CBytes& bytes);

  virtual CBytes GetBytes();

  /// <summary>
  /// Converts a key object to a string with the right prefix
  /// </summary>

  std::string ToString();

  bool operator<(const GlobalStateKey& other) const;

  bool operator==(const GlobalStateKey& other) const;

  bool operator!=(const GlobalStateKey& other) const;
};

/// <summary>
/// Stores an account in the global state.
/// Format: 32-byte length with prefix 'account-hash-'.
/// </summary>
struct AccountHashKey : public GlobalStateKey {
  AccountHashKey(std::string key);
  AccountHashKey() { key_identifier = KeyIdentifier::Account; }
  AccountHashKey(PublicKey publicKey);
};

/// <summary>
/// Stores a contract inmutably in the global state.
/// Format: 32-byte length with prefix 'hash-'.
/// </summary>
struct HashKey : public GlobalStateKey {
  HashKey(std::string key);

  HashKey(CBytes key);
};

/// <summary>
/// Stores information for a transfer in the global state.
/// Format: 32-byte length with prefix 'transfer-'.
/// </summary>
struct TransferKey : public GlobalStateKey {
  TransferKey(std::string key);

  TransferKey(CBytes key);
};

/// <summary>
/// Stores information for a Deploy in the global state.
/// Format: 32-byte length with prefix 'deploy-'.
/// </summary>
struct DeployInfoKey : public GlobalStateKey {
  DeployInfoKey(std::string key);

  DeployInfoKey(CBytes key);
};

/// <summary>
/// Stores information related to the Auction metadata for a particular era..
/// Format: u64 number with prefix 'era-' (e.g. 'era-3407').
/// </summary>
struct EraInfoKey : public GlobalStateKey {
  EraInfoKey(std::string key);

  CBytes GetBytes() override;

 protected:
  CBytes _GetRawBytesFromKey(std::string key) override;
};

/// <summary>
/// Stores information related to the balance of a given purse.
/// Format: 32-byte length with prefix 'balance-'.
/// </summary>
struct BalanceKey : public GlobalStateKey {
  BalanceKey(std::string key);

  BalanceKey(CBytes key);
};

/// <summary>
/// Stores information related to auction bids in the global state.
/// Format: 32-byte length with prefix 'bid-'.
/// </summary>
struct BidKey : public GlobalStateKey {
  BidKey(std::string key);

  BidKey(CBytes key);
};

/// <summary>
/// Stores information related to auction withdraws in the global state.
/// Format: 32-byte length with prefix 'withdraw-'.
/// </summary>
struct WithdrawKey : public GlobalStateKey {
  WithdrawKey(std::string key);

  WithdrawKey(CBytes key);
};

/// <summary>
/// Stores dictionary items in the global state.
/// Format: 32-byte length with prefix 'dictionary-'.
/// </summary>
struct DictionaryKey : public GlobalStateKey {
  DictionaryKey(std::string key);

  DictionaryKey(CBytes key);
};

/**
 * @brief Construct a JSON object from a GlobalStateKey object.
 *
 * @param j JSON object to construct.
 * @param p GlobalStateKey object to construct from.
 */
inline void to_json(nlohmann::json& j, const GlobalStateKey& p) {
  /*std::string key_identifier_str{magic_enum::enum_name(p.key_identifier)};

  j[key_identifier_str] = p.key;
  */

  j = p.key;
}
/**
 * @brief Construct a GlobalStateKey object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p GlobalStateKey object to construct.
 */
inline void from_json(const nlohmann::json& j, GlobalStateKey& p) {
  std::string jKey = j.at("key");

  p = GlobalStateKey::FromString(j.at("key").get<std::string>());
}
}  // namespace Casper
