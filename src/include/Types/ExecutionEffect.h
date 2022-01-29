#pragma once

#include <vector>

#include "Types/Operation.h"
#include "Types/Transform.h"

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
  std::vector<Transform> transforms;
};
}  // namespace Casper
