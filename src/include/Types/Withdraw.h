#pragma once

#include <vector>

#include "Types/StoredValueTypeBase.h"
#include "Types/UnbondingPurse.h"

namespace Casper {
struct Withdraw : public StoredValueTypeBase {
  const StoredValueType type;

  std::vector<UnbondingPurse> list;

  Withdraw() : type(StoredValueType::WITHDRAW) {}
};
}  // namespace Casper