#pragma once
#include <string>
#include <vector>

#include "nlohmann/json.hpp"

namespace Casper {
struct Contract {
  Contract()
      : contract_package_hash{}, contract_wasm_hash{}, protocol_version{} {}

  std::string contract_package_hash;
  std::string contract_wasm_hash;
  std::vector<NamedKey> named_keys;
  std::string protocol_version;
};
}  // namespace Casper
