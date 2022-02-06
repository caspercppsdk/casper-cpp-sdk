#include "Types/GlobalStateKey.h"

namespace Casper {
GlobalStateKey GlobalStateKey::FromString(const std::string& value) {
  if (startsWith(value, "account-hash-"))
    return AccountHashKey(value);
  if (startsWith(value, "hash-"))
    return HashKey(value);

  if (startsWith(value, "contract-package-wasm")) {
    std::string new_value = value;
    std::string prefix = "contract-package-wasm";
    size_t pos = new_value.find(prefix);
    new_value.replace(pos, prefix.length(), "hash-");
    return HashKey(new_value);
  }
  if (startsWith(value, "contract-wasm-")) {
    std::string new_value = value;
    std::string prefix = "contract-wasm-";
    size_t pos = new_value.find(prefix);
    new_value.replace(pos, prefix.length(), "hash-");
    return HashKey(new_value);
  }
  if (startsWith(value, "contract-")) {
    std::string new_value = value;
    std::string prefix = "contract-";
    size_t pos = new_value.find(prefix);
    new_value.replace(pos, prefix.length(), "hash-");
    return HashKey(new_value);
  }

  if (startsWith(value, "uref-"))
    return URef(value);
  if (startsWith(value, "transfer-"))
    return TransferKey(value);
  if (startsWith(value, "deploy-"))
    return DeployInfoKey(value);
  if (startsWith(value, "era-"))
    return EraInfoKey(value);
  if (startsWith(value, "balance-"))
    return BalanceKey(value);
  if (startsWith(value, "bid"))
    return BidKey(value);
  if (startsWith(value, "withdraw"))
    return WithdrawKey(value);
  if (startsWith(value, "dictionary"))
    return DictionaryKey(value);

  throw std::invalid_argument("Key not valid. Unknown key prefix.");
}

GlobalStateKey GlobalStateKey::FromBytes(const SecByteBlock& bytes) {
  SecByteBlock new_bytes(bytes.size() - 1);
  std::copy(bytes.begin() + 1, bytes.end(), new_bytes.begin());
  uint64_t era_number = *(uint64_t*)new_bytes.begin();

  switch (bytes[0]) {
    case 0x00:
      return AccountHashKey("account-hash-" + CEP57Checksum::Encode(new_bytes));
    case 0x01:
      return HashKey("hash-" + CEP57Checksum::Encode(new_bytes));
    case 0x02:
      return URef("uref-" + CEP57Checksum::Encode(new_bytes));
    case 0x03:
      return TransferKey("transfer-" + CEP57Checksum::Encode(new_bytes));
    case 0x04:
      return DeployInfoKey("deploy-" + CEP57Checksum::Encode(new_bytes));
    case 0x05:
      return EraInfoKey("era-" + std::to_string(era_number));
      // TODO: check era number
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

}  // namespace Casper