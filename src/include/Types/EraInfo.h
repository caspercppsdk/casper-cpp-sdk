#pragma once

#include <vector>

#include "Types/SeigniorageAllocation.h"

namespace Casper {
/// <summary>
/// Auction metadata. Intended to be recorded at each era.
/// </summary>
struct EraInfo {
  /// <summary>
  /// List of rewards allocated to delegators and validators.
  /// </summary>
  std::vector<SeigniorageAllocation> seigniorage_allocations;
};
}  // namespace Casper
