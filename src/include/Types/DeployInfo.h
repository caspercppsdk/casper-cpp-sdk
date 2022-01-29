#pragma once

#include <boost/multiprecision/cpp_int.hpp>
#include <string>
#include <vector>

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
  AccountHashKey from;

  /// <summary>
  /// Gas cost of executing the Deploy.
  /// </summary>
  boost::multiprecision::uint512_t gas;

  /// <summary>
  /// Source purse used for payment of the Deploy.
  /// </summary>
  URef source;

  /// <summary>
  /// Transfer addresses performed by the Deploy.
  /// </summary>
  std::vector<TransferKey> transfers;
};
}  // namespace Casper
