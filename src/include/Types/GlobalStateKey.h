#pragma once
#include <string>
#include <vector>

#include "Types/PublicKey.h"
#include "Types/URef.h"
#include "Utils/CEP57Checksum.h"
#include "Utils/CryptoUtil.h"
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
  ACCOUNT = 0x00,
  /// <summary>
  /// Hash keys store contracts immutably in the global state.
  /// </summary>
  HASH = 0x01,
  /// <summary>
  /// URef keys store values and manage permissions to interact with the value
  /// stored under the URef.
  /// </summary>
  UREF = 0x02,
  /// <summary>
  /// Transfer keys store transfers in the global state.
  /// </summary>
  TRANSFER = 0x03,
  /// <summary>
  /// DeployInfo keys store information related to deploys in the global state.
  /// </summary>
  DEPLOYINFO = 0x04,
  /// <summary>
  /// EraInfo keys store information related to the Auction metadata for a
  /// particular era.
  /// </summary>
  ERAINFO = 0x05,
  /// <summary>
  /// Balance keys store information related to the balance of a given purse.
  /// </summary>
  BALANCE = 0x06,
  /// <summary>
  /// Bid keys store information related to auction bids in the global state.
  /// </summary>
  BID = 0x07,
  /// <summary>
  /// Withdraw keys store information related to auction withdraws in the global
  /// state.
  /// </summary>
  WITHDRAW = 0x08,
  /// <summary>
  /// Dictionary keys store dictionary items.
  /// </summary>
  DICTIONARY = 0x09
};

/// <summary>
/// Base class for the different global state keys.
/// </summary>
class GlobalStateKey {
 protected:
  std::string key;

 public:
  KeyIdentifier key_identifier;
  SecByteBlock raw_bytes;

 protected:
  virtual SecByteBlock _GetRawBytesFromKey(std::string key) {
    return hexDecode(key.substr(key.find_last_of("-") + 1));
  }

  GlobalStateKey() {}
  /// <summary>
  /// Constructor for the GlobalStateKey class.
  /// </summary>
  GlobalStateKey(std::string key_) : key{key_} {}

  /// <summary>
  /// Constructor for the GlobalStateKey class with key prefix.
  /// </summary>
  GlobalStateKey(std::string key_, std::string key_prefix) {
    if (key_.rfind(key_prefix, 0) != 0)
      throw std::invalid_argument(
          "Key not valid. It should start with '{key_prefix}'.");

    SecByteBlock res =
        CEP57Checksum::Decode(key_.substr(key_.find_last_of('-') + 1));
    key = key_prefix + CEP57Checksum::Encode(res);
  }

 public:
  std::string ToHexString() {
    //
    return CEP57Checksum::Encode(raw_bytes);
  }

  /// <summary>
  /// Converts a global state key from string to its specific key object.
  /// </summary>

  static GlobalStateKey FromString(const std::string& value);

  /// <summary>
  /// Converts a global state key from a byte array to its specific key object.
  /// First byte in the array indicates the Key identifier.
  /// </summary>
  static GlobalStateKey FromBytes(const SecByteBlock& bytes);

  virtual SecByteBlock GetBytes() {
    SecByteBlock ms(this->raw_bytes.size() + 1);
    ms[0] = static_cast<uint8_t>(this->key_identifier);
    std::copy(this->raw_bytes.begin(), this->raw_bytes.end(), ms.begin() + 1);
    return ms;
  }

  /// <summary>
  /// Converts a key object to a string with the right prefix
  /// </summary>

  std::string ToString() const { return key; }
};
/// <summary>
/// Stores an account in the global state.
/// Format: 32-byte length with prefix 'account-hash-'.
/// </summary>
struct AccountHashKey : public GlobalStateKey {
  AccountHashKey(std::string key) : GlobalStateKey(key, "account-hash-") {
    key_identifier = KeyIdentifier::ACCOUNT;
  }

  AccountHashKey(PublicKey publicKey)
      : GlobalStateKey(publicKey.GetAccountHash(), "account-hash-") {}
};

/// <summary>
/// Stores a contract inmutably in the global state.
/// Format: 32-byte length with prefix 'hash-'.
/// </summary>
struct HashKey : public GlobalStateKey {
  HashKey(std::string key) : GlobalStateKey(key, "hash-") {
    key_identifier = KeyIdentifier::HASH;
  }

  HashKey(SecByteBlock key) : HashKey("hash-" + CEP57Checksum::Encode(key)) {}
};

/// <summary>
/// Stores information for a transfer in the global state.
/// Format: 32-byte length with prefix 'transfer-'.
/// </summary>
struct TransferKey : public GlobalStateKey {
  TransferKey(std::string key) : GlobalStateKey(key, "transfer-") {
    key_identifier = KeyIdentifier::TRANSFER;
  }

  TransferKey(SecByteBlock key)
      : TransferKey("transfer-" + CEP57Checksum::Encode(key)) {}
};

/// <summary>
/// Stores information for a Deploy in the global state.
/// Format: 32-byte length with prefix 'deploy-'.
/// </summary>
struct DeployInfoKey : public GlobalStateKey {
  DeployInfoKey(std::string key) : GlobalStateKey(key, "deploy-") {
    key_identifier = KeyIdentifier::DEPLOYINFO;
  }

  DeployInfoKey(SecByteBlock key)
      : DeployInfoKey("deploy-" + CEP57Checksum::Encode(key)) {}
};

/// <summary>
/// Stores information related to the Auction metadata for a particular era..
/// Format: u64 number with prefix 'era-' (e.g. 'era-3407').
/// </summary>
struct EraInfoKey : public GlobalStateKey {
  EraInfoKey(std::string key) : GlobalStateKey(key) {
    key_identifier = KeyIdentifier::ERAINFO;
    if (!startsWith(key, "era-"))
      throw std::invalid_argument("EraInfoKey must start with 'era-'");

    int64_t era_num;
    try {
      std::istringstream iss(key.substr(4));
      iss >> era_num;
    } catch (std::exception& e) {
      throw std::invalid_argument("Key not valid. Cannot parse era number.");
    }
  }

  SecByteBlock GetBytes() override {
    SecByteBlock ms(9);
    ms[0] = uint8_t(this->key_identifier);
    std::copy(ms.begin() + 1, ms.end(), raw_bytes.begin());
    return ms;
  }

 protected:
  SecByteBlock _GetRawBytesFromKey(std::string key) override {
    uint64_t u64;
    std::istringstream iss(key.substr(4));
    iss >> u64;

    SecByteBlock bytes(8);
    std::copy(reinterpret_cast<uint8_t*>(&u64),
              reinterpret_cast<uint8_t*>(&u64) + 8, bytes.begin());

    // TODO: Check endianness
    // if (!BitConverter.IsLittleEndian) Array.Reverse(bytes);

    return bytes;
  }
};

/// <summary>
/// Stores information related to the balance of a given purse.
/// Format: 32-byte length with prefix 'balance-'.
/// </summary>
struct BalanceKey : public GlobalStateKey {
  BalanceKey(std::string key) : GlobalStateKey(key, "balance-") {
    key_identifier = KeyIdentifier::BALANCE;
  }

  BalanceKey(SecByteBlock key)
      : BalanceKey("balance-" + CEP57Checksum::Encode(key)) {}
};

/// <summary>
/// Stores information related to auction bids in the global state.
/// Format: 32-byte length with prefix 'bid-'.
/// </summary>
struct BidKey : public GlobalStateKey {
  BidKey(std::string key) : GlobalStateKey(key, "bid-") {
    key_identifier = KeyIdentifier::BID;
  }

  BidKey(SecByteBlock key) : BidKey("bid-" + CEP57Checksum::Encode(key)) {}
};

/// <summary>
/// Stores information related to auction withdraws in the global state.
/// Format: 32-byte length with prefix 'withdraw-'.
/// </summary>
struct WithdrawKey : public GlobalStateKey {
  WithdrawKey(std::string key) : GlobalStateKey(key, "withdraw-") {
    key_identifier = KeyIdentifier::WITHDRAW;
  }

  WithdrawKey(SecByteBlock key)
      : WithdrawKey("withdraw-" + CEP57Checksum::Encode(key)) {}
};

/// <summary>
/// Stores dictionary items in the global state.
/// Format: 32-byte length with prefix 'dictionary-'.
/// </summary>
struct DictionaryKey : public GlobalStateKey {
  DictionaryKey(std::string key) : GlobalStateKey(key, "dictionary-") {
    key_identifier = KeyIdentifier::DICTIONARY;
  }

  DictionaryKey(SecByteBlock key)
      : DictionaryKey("dictionary-" + CEP57Checksum::Encode(key)) {}
};

/**
 * @brief Construct a JSON object from a GlobalStateKey object.
 *
 * @param j JSON object to construct.
 * @param p GlobalStateKey object to construct from.
 */
inline void to_json(nlohmann::json& j, const GlobalStateKey& p) {
  // j = nlohmann::json{{"node_id", p.node_id}, {"address", p.address}};
  j = nlohmann::json{{"key", p.ToString()}};
  // TODO:
}

/**
 * @brief Construct a GlobalStateKey object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p GlobalStateKey object to construct.
 */
inline void from_json(const nlohmann::json& j, GlobalStateKey& p) {
  p = GlobalStateKey::FromString(j.at("key").get<std::string>());
  //  j.at("node_id").get_to(p.node_id);
  // TODO:
}
}  // namespace Casper