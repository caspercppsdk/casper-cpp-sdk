#pragma once

#include <string>

#include "Types/Definitions.h"
#include "Types/ExecutableDeployItem.h"
#include "Types/URef.h"
#include "nlohmann/json.hpp"

namespace Casper {

struct StoredVersionedContractByHash : public ExecutableDeployItemBase {
  StoredVersionedContractByHash(std::string hash_, std::string version_, std::string entry_point_, std::string args_)
      : ExecutableDeployItemBase(ExecutableDeployItemType::STOREDVERSIONEDCONTRACTBYHASH),
      hash(hash_),
      version(version_),
      entry_point(entry_point_),
      args(args_) {}

  StoredVersionedContractByHash() : ExecutableDeployItemBase(ExecutableDeployItemType::STOREDVERSIONEDCONTRACTBYHASH) {}

  std::string hash;
  std::string version;
  std::string entry_point;
  std::string args;
};

/**
 * @brief Construct a JSON object from a StoredVersionedContractByHash object.
 *
 * @param j JSON object to construct.
 * @param p StoredVersionedContractByHash object to construct from.
 */

inline void to_json(nlohmann::json& j, const StoredVersionedContractByHash& p) {
  j = static_cast<ExecutableDeployItemBase>(p);
  j["hash"] = p.hash;
  j["version"] = p.version;
  j["entry_point"] = p.entry_point;
  j["args"] = p.args;
}

/**
 * @brief Construct a StoredVersionedContractByHash object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p StoredVersionedContractByHash object to construct.
 */

inline void from_json(const nlohmann::json& j, StoredVersionedContractByHash& p) {
  nlohmann::from_json(j, static_cast<ExecutableDeployItemBase&>(p));
  j.at("hash").get_to(p.hash);
  j.at("version").get_to(p.version);
  j.at("entry_point").get_to(p.entry_point);
  j.at("args").get_to(p.args);
}

}  // namespace Casper