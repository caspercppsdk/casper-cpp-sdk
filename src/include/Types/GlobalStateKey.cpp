#include "Types/GlobalStateKey.h"

#include <sstream>

#include "Types/URef.h"
#include "Utils/CEP57Checksum.h"
#include "Utils/CryptoUtil.h"
#include "Utils/StringUtil.h"

namespace Casper {

CBytes GlobalStateKey::_GetRawBytesFromKey(std::string key) {
  return CryptoUtil::hexDecode(key.substr(key.find_last_of("-") + 1));
}

GlobalStateKey::GlobalStateKey() {}
/// <summary>
/// Constructor for the GlobalStateKey class.
/// </summary>
GlobalStateKey::GlobalStateKey(std::string key_)
    : key{key_}, raw_bytes{_GetRawBytesFromKey(key_)} {}

/// <summary>
/// Constructor for the GlobalStateKey class with key prefix.
/// </summary>
GlobalStateKey::GlobalStateKey(std::string key_, std::string key_prefix) {
  if (key_.rfind(key_prefix, 0) != 0)
    throw std::invalid_argument(
        "Key not valid. It should start with '{key_prefix}'.");
  CBytes res = CEP57Checksum::Decode(key_.substr(key_.find_last_of('-') + 1));
  key = key_prefix + CEP57Checksum::Encode(res);
  raw_bytes = _GetRawBytesFromKey(key);
}

std::string GlobalStateKey::ToHexString() {
  //
  return CEP57Checksum::Encode(raw_bytes);
}

GlobalStateKey GlobalStateKey::FromString(std::string value) {
  if (StringUtil::startsWith(value, "account-hash-"))
    return AccountHashKey(value);
  if (StringUtil::startsWith(value, "hash-")) return HashKey(value);

  if (StringUtil::startsWith(value, "contract-package-wasm")) {
    std::string new_value = value;
    std::string prefix = "contract-package-wasm";
    size_t pos = new_value.find(prefix);
    new_value.replace(pos, prefix.length(), "hash-");
    return HashKey(new_value);
  }
  if (StringUtil::startsWith(value, "contract-wasm-")) {
    std::string new_value = value;
    std::string prefix = "contract-wasm-";
    size_t pos = new_value.find(prefix);
    new_value.replace(pos, prefix.length(), "hash-");
    return HashKey(new_value);
  }
  if (StringUtil::startsWith(value, "contract-")) {
    std::string new_value = value;
    std::string prefix = "contract-";
    size_t pos = new_value.find(prefix);
    new_value.replace(pos, prefix.length(), "hash-");
    return HashKey(new_value);
  }

  if (StringUtil::startsWith(value, "uref-")) return URef(value);
  if (StringUtil::startsWith(value, "transfer-")) return TransferKey(value);
  if (StringUtil::startsWith(value, "deploy-")) return DeployInfoKey(value);
  if (StringUtil::startsWith(value, "era-")) return EraInfoKey(value);
  if (StringUtil::startsWith(value, "balance-")) return BalanceKey(value);
  if (StringUtil::startsWith(value, "bid")) return BidKey(value);
  if (StringUtil::startsWith(value, "withdraw")) return WithdrawKey(value);
  if (StringUtil::startsWith(value, "dictionary")) return DictionaryKey(value);

  throw std::invalid_argument("Key not valid. Unknown key prefix.");
}

GlobalStateKey GlobalStateKey::FromBytes(const CBytes& bytes) {
  CBytes new_bytes(bytes.size() - 1);
  std::copy(bytes.begin() + 1, bytes.end(), new_bytes.begin());
  uint64_t era_number = *(uint64_t*)new_bytes.begin();

  switch (bytes[0]) {
    case 0x00:
      return AccountHashKey("account-hash-" + CryptoUtil::hexEncode(new_bytes));
    case 0x01:
      return HashKey("hash-" + CryptoUtil::hexEncode(new_bytes));
    case 0x02:
      return URef("uref-" + CEP57Checksum::Encode(new_bytes));
    case 0x03:
      return TransferKey("transfer-" + CEP57Checksum::Encode(new_bytes));
    case 0x04:
      return DeployInfoKey("deploy-" + CEP57Checksum::Encode(new_bytes));
    case 0x05:
      return EraInfoKey("era-" + std::to_string(era_number));
    case 0x06:
      return BalanceKey("balance-" + CEP57Checksum::Encode(new_bytes));
    case 0x07:
      return BidKey("bid-" + CEP57Checksum::Encode(new_bytes));
    case 0x08:
      return WithdrawKey("withdraw-" + CEP57Checksum::Encode(new_bytes));
    case 0x09:
      return DictionaryKey("dictionary-" + CEP57Checksum::Encode(new_bytes));
    default:
      throw std::invalid_argument("Key not valid. Unknown key prefix.");
  }
}

CBytes GlobalStateKey::GetBytes() {
  CBytes ms(this->raw_bytes.size() + 1);
  ms[0] = static_cast<uint8_t>(this->key_identifier);
  std::copy(this->raw_bytes.begin(), this->raw_bytes.end(), ms.begin() + 1);
  return ms;
}

std::string GlobalStateKey::ToString() { return this->key; }
// GlobalStateKey

bool GlobalStateKey::operator<(const GlobalStateKey& other) const {
  return this->key < other.key;
}

bool GlobalStateKey::operator==(const GlobalStateKey& other) const {
  return this->key == other.key;
}

bool GlobalStateKey::operator!=(const GlobalStateKey& other) const {
  return this->key != other.key;
}

AccountHashKey::AccountHashKey(std::string key)
    : GlobalStateKey::GlobalStateKey(key, "account-hash-") {
  key_identifier = KeyIdentifier::Account;
}

AccountHashKey::AccountHashKey(PublicKey publicKey)
    : GlobalStateKey::GlobalStateKey(publicKey.GetAccountHash(),
                                     "account-hash-") {}

HashKey::HashKey(std::string key)
    : GlobalStateKey::GlobalStateKey(key, "hash-") {
  key_identifier = KeyIdentifier::Hash;
}

HashKey::HashKey(CBytes key)
    : HashKey::HashKey("hash-" + CEP57Checksum::Encode(key)) {}

TransferKey::TransferKey(std::string key)
    : GlobalStateKey::GlobalStateKey(key, "transfer-") {
  key_identifier = KeyIdentifier::Transfer;
}

TransferKey::TransferKey(CBytes key)
    : TransferKey::TransferKey("transfer-" + CEP57Checksum::Encode(key)) {}

DeployInfoKey::DeployInfoKey(std::string key)
    : GlobalStateKey::GlobalStateKey(key, "deploy-") {
  key_identifier = KeyIdentifier::DeployInfo;
}

DeployInfoKey::DeployInfoKey(CBytes key)
    : DeployInfoKey::DeployInfoKey("deploy-" + CEP57Checksum::Encode(key)) {}

EraInfoKey::EraInfoKey(std::string key) : GlobalStateKey::GlobalStateKey(key) {
  key_identifier = KeyIdentifier::EraInfo;
  if (!StringUtil::startsWith(key, "era-"))
    throw std::invalid_argument("EraInfoKey must start with 'era-'");

  int64_t era_num;
  try {
    std::istringstream iss(key.substr(4));
    iss >> era_num;
  } catch (std::exception& e) {
    throw std::invalid_argument("Key not valid. Cannot parse era number.");
  }
}

CBytes EraInfoKey::GetBytes() {
  CBytes ms(9);
  ms[0] = uint8_t(this->key_identifier);
  std::copy(ms.begin() + 1, ms.end(), raw_bytes.begin());
  return ms;
}

CBytes EraInfoKey::_GetRawBytesFromKey(std::string key) {
  uint64_t u64;
  std::istringstream iss(key.substr(4));
  iss >> u64;

  CBytes bytes(8);
  std::copy(reinterpret_cast<uint8_t*>(&u64),
            reinterpret_cast<uint8_t*>(&u64) + 8, bytes.begin());

  // TODOMS3: Check endianness
  // if (!BitConverter.IsLittleEndian) Array.Reverse(bytes);

  return bytes;
}

BalanceKey::BalanceKey(std::string key)
    : GlobalStateKey::GlobalStateKey(key, "balance-") {
  key_identifier = KeyIdentifier::Balance;
}

BalanceKey::BalanceKey(CBytes key)
    : BalanceKey::BalanceKey("balance-" + CEP57Checksum::Encode(key)) {}

BidKey::BidKey(std::string key) : GlobalStateKey::GlobalStateKey(key, "bid-") {
  key_identifier = KeyIdentifier::Bid;
}

BidKey::BidKey(CBytes key)
    : BidKey::BidKey("bid-" + CEP57Checksum::Encode(key)) {}

WithdrawKey::WithdrawKey(std::string key)
    : GlobalStateKey::GlobalStateKey(key, "withdraw-") {
  key_identifier = KeyIdentifier::Withdraw;
}

WithdrawKey::WithdrawKey(CBytes key)
    : WithdrawKey::WithdrawKey("withdraw-" + CEP57Checksum::Encode(key)) {}

DictionaryKey::DictionaryKey(std::string key)
    : GlobalStateKey::GlobalStateKey(key, "dictionary-") {
  key_identifier = KeyIdentifier::Dictionary;
}
DictionaryKey::DictionaryKey(CBytes key)
    : DictionaryKey::DictionaryKey("dictionary-" + CEP57Checksum::Encode(key)) {
}

}  // namespace Casper