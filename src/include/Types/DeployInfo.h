#pragma once

#include <string>
#include <vector>

#include "Types/Definitions.h"
#include "Types/GlobalStateKey.h"
#include "Types/URef.h"

namespace Casper {
/// <summary>
/// Information relating to the given Deploy.
/// </summary>
struct DeployInfo {
  /// <summary>
  /// The Deploy hash.
  /// </summary>
  std::string deploy_hash;

  /// <summary>
  /// Account identifier of the creator of the Deploy.
  /// </summary>
  std::string from;

  /// <summary>
  /// Gas cost of executing the Deploy.
  /// </summary>
  big_int gas;

  /// <summary>
  /// Source purse used for payment of the Deploy.
  /// </summary>
  URef source;

  /// <summary>
  /// Transfer addresses performed by the Deploy.
  /// </summary>
  std::vector<std::string> transfers;
};
}  // namespace Casper
