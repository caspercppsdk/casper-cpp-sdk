#pragma once
#include <vector>

#include "Utils/CEP57Checksum.h"
#include "nlohmann/json.hpp"

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
  SecByteBlock
      raw_bytes;  // TODO: rawbytes ->  return _GetRawBytesFromKey(Key);

 protected:
  virtual SecByteBlock _GetRawBytesFromKey(std::string key) {
    return CEP57Checksum::Decode(key.substr(key.find_last_of("-") + 1));
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
    if (key_.rfind(key_prefix, 0) != 0)
      throw std::invalid_argument(
          "Key not valid. It should start with '{key_prefix}'.");

    SecByteBlock res =
        CEP57Checksum::Decode(key_.substr(key_.find_last_of('-') + 1));
    key = key_prefix + CEP57Checksum::Encode(res);
  }
};
}  // namespace Casper