#include "Types/GlobalStateKey.h"

namespace Casper {
GlobalStateKey GlobalStateKey::FromString(const std::string& value) {
  if (startsWith(value, "account-hash-")) return AccountHashKey(value);
  if (startsWith(value, "hash-")) return HashKey(value);

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

  if (startsWith(value, "uref-")) return URef(value);
  if (startsWith(value, "transfer-")) return TransferKey(value);
  if (startsWith(value, "deploy-")) return DeployInfoKey(value);
  if (startsWith(value, "era-")) return EraInfoKey(value);
  if (startsWith(value, "balance-")) return BalanceKey(value);
  if (startsWith(value, "bid")) return BidKey(value);
  if (startsWith(value, "withdraw")) return WithdrawKey(value);
  if (startsWith(value, "dictionary")) return DictionaryKey(value);

  throw std::invalid_argument("Key not valid. Unknown key prefix.");
}
}  // namespace Casper