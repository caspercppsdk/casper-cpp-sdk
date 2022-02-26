#pragma once

#include "Base.h"
#include "Types/PublicKey.h"
#include "nlohmann/json.hpp"

namespace Casper {
/// <summary>
/// Header information of a Deploy.
/// </summary>
struct DeployHeader {
  /// <summary>
  /// Public Key from the Account owning the Deploy.
  /// </summary>
  // TODO: Make PublicKey instead of std::string
  std::string account;

  /// <summary>
  /// Timestamp formatted as per RFC 3339
  /// </summary>
  uint64_t timestamp;

  /// <summary>
  /// Duration of the Deploy in milliseconds (from timestamp).
  /// </summary>
  // TODO: [JsonConverter(typeof(HumanizeTTLConverter))]
  uint64_t ttl;

  /// <summary>
  /// Gas price
  /// </summary>
  uint64_t gas_price;

  /// <summary>
  /// Hash of the body part of this Deploy.
  /// </summary>
  // TODO: [JsonConverter(typeof(CEP57Checksum.HashWithChecksumConverter))]
  std::string body_hash;

  /// <summary>
  /// List of Deploy hashes.
  /// </summary>
  std::vector<std::string> dependencies;

  /// <summary>
  /// Name of the chain where the deploy is executed.
  /// </summary>
  std::string chain_name;

  DeployHeader() {}
};

// to_json of DeployHeader
inline void to_json(nlohmann::json& j, const DeployHeader& p) {
  j = nlohmann::json{{"account", p.account},
                     {"timestamp", p.timestamp},
                     {"ttl", p.ttl},
                     {"gas_price", p.gas_price},
                     {"body_hash", p.body_hash},
                     {"dependencies", p.dependencies},
                     {"chain_name", p.chain_name}};
}

// from_json of DeployHeader
inline void from_json(const nlohmann::json& j, DeployHeader& p) {
  j.at("account").get_to(p.account);
  j.at("timestamp").get_to(p.timestamp);
  j.at("ttl").get_to(p.ttl);
  j.at("gas_price").get_to(p.gas_price);
  j.at("body_hash").get_to(p.body_hash);
  j.at("dependencies").get_to(p.dependencies);
  j.at("chain_name").get_to(p.chain_name);
}

}  // namespace Casper
