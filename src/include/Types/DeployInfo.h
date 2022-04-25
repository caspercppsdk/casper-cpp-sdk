#pragma once

#include "Base.h"
#include "Types/GlobalStateKey.h"
#include "Types/URef.h"
#include "nlohmann/json.hpp"

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
  /// Transfer addresses performed by the Deploy.
  /// </summary>
  // TODOMS3: make TransferKey instead of std::string
  std::vector<std::string> transfers;

  /// <summary>
  /// Account identifier of the creator of the Deploy.
  /// </summary>
  // TODOMS3: make AccountHashKey  instead of std::string
  std::string from;

  /// <summary>
  /// Source purse used for payment of the Deploy.
  /// </summary>
  URef source;

  /// <summary>
  /// Gas cost of executing the Deploy.
  /// </summary>
  uint512_t gas;

  DeployInfo() {}
};

// from_json of DeployInfo
inline void from_json(const nlohmann::json& j, DeployInfo& p) {
  j.at("deploy_hash").get_to(p.deploy_hash);
  j.at("transfers").get_to(p.transfers);
  j.at("from").get_to(p.from);
  j.at("source").get_to(p.source);
  j.at("gas").get_to(p.gas);
}

// to_json of DeployInfo
inline void to_json(nlohmann::json& j, const DeployInfo& p) {
  j = {{"deploy_hash", p.deploy_hash},
       {"transfers", p.transfers},
       {"from", p.from},
       {"source", p.source},
       {"gas", p.gas}};
}
}  // namespace Casper
