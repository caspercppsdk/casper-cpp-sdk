#pragma once
#include <string>
#include <vector>

#include "nlohmann/json.hpp"

using bytes = std::vector<std::byte>;

namespace Casper {
/// <summary>
/// Keys in the global state store information about different data types.
/// <see
/// cref="https://casper.network/docs/design/serialization-standard#serialization-standard-state-keys"/>
/// </summary>

enum KeyIdentifier {
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
class GlobalStateKey {
 protected:
  const std::string key;

 public:
  KeyIdentifier key_identifier;
  bytes raw_bytes;  // TODO: rawbytes ->  return _GetRawBytesFromKey(Key);

 protected:
  virtual bytes _GetRawBytesFromKey(std::string key) {
    return {};
    // return Hex.Decode(key.Substring(key.LastIndexOf('-') + 1));
  }
  /// <summary>
  /// Constructor for the GlobalStateKey class.
  /// </summary>
  GlobalStateKey(std::string key_) : key{key_} {}

  /// <summary>
  /// Constructor for the GlobalStateKey class with key prefix.
  /// </summary>
  GlobalStateKey(std::string key_, std::string key_prefix) {
    if (!key_.StartsWith(key_prefix))
      throw new ArgumentException(
          $ "Key not valid. It should start with '{key_prefix}'.",
          nameof(key_));

    bytes res = CEP57Checksum.Decode(key_.Substring(key_.LastIndexOf('-') + 1),
                                     out int checksumResult);
    if (checksumResult == CEP57Checksum.InvalidChecksum)
      throw new ArgumentException("Global State Key checksum mismatch.");

    key = key_prefix + CEP57Checksum.Encode(res);
  }
};
}  // namespace Casper