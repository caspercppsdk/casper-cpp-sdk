#pragma once

#include <vector>

#include "Types/SeigniorageAllocation.h"
#include "Types/StoredValueTypeBase.h"

namespace Casper {
/// <summary>
/// Auction metadata. Intended to be recorded at each era.
/// </summary>
struct EraInfo : public StoredValueTypeBase {
  const StoredValueType type;

  /// <summary>
  /// List of rewards allocated to delegators and validators.
  /// </summary>
  std::vector<SeigniorageAllocation> seigniorage_allocations;

  EraInfo () : type(StoredValueType::ERAINFO) {}
};
}  // namespace Casper
