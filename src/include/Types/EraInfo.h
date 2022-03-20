#pragma once

#include "Base.h"
#include "Types/SeigniorageAllocation.h"
#include "nlohmann/json.hpp"

namespace Casper {
/// <summary>
/// Auction metadata. Intended to be recorded at each era.
/// </summary>
struct EraInfo {
  /// <summary>
  /// List of rewards allocated to delegators and validators.
  /// </summary>
  std::vector<SeigniorageAllocation> seigniorage_allocations;

  EraInfo() {}
};

// to_json of EraInfo
inline void to_json(nlohmann::json& j, const EraInfo& p) {
  j = {{"seigniorage_allocations", p.seigniorage_allocations}};
}

// from_json of EraInfo
inline void from_json(const nlohmann::json& j, EraInfo& p) {
  j.at("seigniorage_allocations").get_to(p.seigniorage_allocations);
}

}  // namespace Casper
