#pragma once

#include <string>
#include <vector>

#include "Types/PublicKey.h"

namespace Casper {
/// <summary>
/// Header information of a Deploy.
/// </summary>
struct DeployHeader {
  /// <summary>
  /// Public Key from the Account owning the Deploy.
  /// </summary>
  PublicKey account;

  /// <summary>
  /// Timestamp formatted as per RFC 3339
  /// </summary>
  uint64_t timestamp;

  /// <summary>
  /// Duration of the Deploy in milliseconds (from timestamp).
  /// </summary>
  uint64_t ttl;

  /// <summary>
  /// List of Deploy hashes.
  /// </summary>
  std::vector<std::string> dependencies;

  /// <summary>
  /// Gas price
  /// </summary>
  uint64_t gas_price;

  /// <summary>
  /// Hash of the body part of this Deploy.
  /// </summary>
  std::string body_hash;

  /// <summary>
  /// Name of the chain where the deploy is executed.
  /// </summary>
  std::string chain_name;
};
}  // namespace Casper
