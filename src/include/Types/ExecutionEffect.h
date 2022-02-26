#pragma once

#include "Base.h"
#include "Types/Operation.h"
#include "Types/TransformEntry.h"
#include "nlohmann/json.hpp"

namespace Casper {
/// <summary>
/// The journal of execution transforms from a single deploy.
/// </summary>
struct ExecutionEffect {
  /// <summary>
  /// The resulting operations.
  /// </summary>
  std::vector<Operation> operations;

  /// <summary>
  /// The journal of execution transforms.
  /// </summary>
  std::vector<TransformEntry> transforms;

  ExecutionEffect() {}
};

// to_json of ExecutionEffect
inline void to_json(nlohmann::json& j, const ExecutionEffect& p) {
  j = nlohmann::json{{"operations", p.operations},
                     {"transforms", p.transforms}};
}

// from_json of ExecutionEffect
inline void from_json(const nlohmann::json& j, ExecutionEffect& p) {
  j.at("operations").get_to(p.operations);
  j.at("transforms").get_to(p.transforms);
}

}  // namespace Casper
