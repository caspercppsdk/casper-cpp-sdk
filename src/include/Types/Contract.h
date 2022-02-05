#pragma once
#include <string>
#include <vector>

#include "Types/EntryPoint.h"
#include "Types/NamedKey.h"
#include "Types/StoredValueTypeBase.h"
#include "nlohmann/json.hpp"

namespace Casper {
struct Contract : public StoredValueTypeBase {
  const StoredValueType type;

  Contract() : type(StoredValueType::CONTRACT) {}

  std::string contract_package_hash;
  std::string contract_wasm_hash;
  std::vector<EntryPoint> entry_points;
  std::vector<NamedKey> named_keys;
  std::string protocol_version;
};
}  // namespace Casper
