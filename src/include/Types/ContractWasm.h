#pragma once
#include "Types/StoredValueTypeBase.h"
#include <string>

namespace Casper
{
struct CLValue : public StoredValueTypeBase
{
    const StoredValueType type;
    std::string contract_wasm;

    CLValue (std::string contract_wasm_) : type(StoredValueType::CONTRACTWASM) {
        contract_wasm = contract_wasm_;
    }
};

} // namespace Casper
