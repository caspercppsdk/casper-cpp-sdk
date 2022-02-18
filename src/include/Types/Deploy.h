#pragma once

#include "Base.h"
#include "nlohmann/json.hpp"

#include "Types/ExecutableDeployItem.h"
#include "Types/PublicKey.h"

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

  std::string secret_key;  // optional

  /// <summary>
  /// Public Key from the Account owning the Deploy.
  /// </summary>
  PublicKey account;
};

/**
 * @brief Construct a JSON object from a BlockIdentifier object.
 *
 * @param j JSON object to construct.
 * @param p BlockIdentifier object to construct from.
 */
inline void to_json(nlohmann::json& j, const Deploy& p) {
  j = nlohmann::json{
      {"chain_name", p.chain_name},
  };
}

/**
 * @brief Construct a Deploy object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p Deploy object to construct.
 */
inline void from_json(const nlohmann::json& j, Deploy& p) {
  j.at("chain_name").get_to(p.chain_name);
}

}  // namespace Casper
