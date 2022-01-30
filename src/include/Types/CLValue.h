#pragma once
#include "Types/StoredValueTypeBase.h"
#include <string>

namespace Casper
{
struct CLValue : public StoredValueTypeBase
{
    const StoredValueType type;
    std::string temp;

    CLValue (std::string temp_) : type(StoredValueType::CLVALUE) {
        temp = temp_;
    }
};

} // namespace Casper
