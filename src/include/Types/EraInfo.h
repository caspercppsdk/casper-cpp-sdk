#pragma once

#include <vector>

#include "Types/SeigniorageAllocation.h"
#include "Types/StoredValueTypeBase.h"

namespace Casper {
/// <summary>
/// Auction metadata. Intended to be recorded at each era.
/// </summary>
struct EraInfo {
  /// <summary>
  /// List of rewards allocated to delegators and validators.
  /// </summary>
  std::vector<SeigniorageAllocation> seigniorage_allocations;
  EraInfo(std::vector<SeigniorageAllocation> seigniorage_allocations_)
      : seigniorage_allocations(seigniorage_allocations_) {}
  EraInfo() {}
};

// from_json of EraInfo
inline void from_json(const nlohmann::json& j, EraInfo& p) {
  j.at("seigniorage_allocations").get_to(p.seigniorage_allocations);
}

// to_json of EraInfo
inline void to_json(nlohmann::json& j, const EraInfo& p) {
  j = {{"seigniorage_allocations", p.seigniorage_allocations}};
}

}  // namespace Casper
