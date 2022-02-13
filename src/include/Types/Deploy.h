#pragma once

#include <string>
#include <vector>

#include "Types/PublicKey.h"
#include "Types/ExecutableDeployItem.h"

namespace Casper {
/// <summary>
/// Header information of a Deploy.
/// </summary>
struct Deploy {
  /// <summary>
  /// Timestamp formatted as per RFC 3339
  /// </summary>
  uint64_t timestamp;

  /// <summary>
  ///
  /// </summary>
  uint64_t ttl;

  /// <summary>
  /// Gas price
  /// </summary>
  uint64_t gas_price;

  /// <summary>
  /// List of Deploy hashes.
  /// </summary>
  std::vector<std::string> dependencies;

  /// <summary>
  /// Name of the chain where the deploy is executed.
  /// </summary>
  std::string chain_name;

  ExecutableDeployItemBase payment;

  ExecutableDeployItemBase session;

  std::string secret_key; // optional

  /// <summary>
  /// Public Key from the Account owning the Deploy.
  /// </summary>
  PublicKey account;
};
}  // namespace Casper
