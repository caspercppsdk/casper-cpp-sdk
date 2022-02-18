#pragma once

#include "Base.h"

namespace Casper {
struct ContractWasm {
  std::string contract_wasm;

  ContractWasm(std::string contract_wasm_) : contract_wasm(contract_wasm_) {}
  ContractWasm() {}
};

}  // namespace Casper
