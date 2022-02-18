#pragma once

#include <vector>

#include "Types/StoredValueTypeBase.h"
#include "Types/UnbondingPurse.h"

namespace Casper {
struct Withdraw {

  std::vector<UnbondingPurse> list;

  Withdraw() {}
};
}  // namespace Casper