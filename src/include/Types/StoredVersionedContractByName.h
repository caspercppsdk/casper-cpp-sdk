#pragma once

#include <string>

#include "Types/Definitions.h"
#include "Types/ExecutableDeployItem.h"
#include "Types/URef.h"
#include "nlohmann/json.hpp"

namespace Casper {

struct StoredVersionedContractByName : public ExecutableDeployItemBase {
  StoredVersionedContractByName(std::string name_, std::string version_, std::string entry_point_, std::string args_)
      : ExecutableDeployItemBase(ExecutableDeployItemType::STOREDVERSIONEDCONTRACTBYNAME),
      name(name_),
      version(version_),
      entry_point(entry_point_),
      args(args_) {}

  StoredVersionedContractByName() : ExecutableDeployItemBase(ExecutableDeployItemType::STOREDVERSIONEDCONTRACTBYNAME) {}

  std::string name;
  std::string version;
  std::string entry_point;
  std::string args;
};

/**
 * @brief Construct a JSON object from a StoredVersionedContractByName object.
 *
 * @param j JSON object to construct.
 * @param p StoredVersionedContractByName object to construct from.
 */

inline void to_json(nlohmann::json& j, const StoredVersionedContractByName& p) {
  j = static_cast<ExecutableDeployItemBase>(p);
  j["name"] = p.name;
  j["version"] = p.version;
  j["entry_point"] = p.entry_point;
  j["args"] = p.args;
}

/**
 * @brief Construct a StoredVersionedContractByName object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p StoredVersionedContractByName object to construct.
 */

inline void from_json(const nlohmann::json& j, StoredVersionedContractByName& p) {
  nlohmann::from_json(j, static_cast<ExecutableDeployItemBase&>(p));
  j.at("name").get_to(p.name);
  j.at("version").get_to(p.version);
  j.at("entry_point").get_to(p.entry_point);
  j.at("args").get_to(p.args);
}

}  // namespace Casper