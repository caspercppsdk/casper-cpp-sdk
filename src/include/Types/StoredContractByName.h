#pragma once

#include <string>

#include "Types/Definitions.h"
#include "Types/ExecutableDeployItem.h"
#include "Types/URef.h"
#include "nlohmann/json.hpp"

namespace Casper {

struct StoredContractByName : public ExecutableDeployItemBase {
  StoredContractByName(std::string name_, std::string entry_point_, std::string args_)
      : ExecutableDeployItemBase(ExecutableDeployItemType::STOREDCONTRACYBYNAME), name(name_), entry_point(entry_point_), args(args_) {}

  StoredContractByName() : ExecutableDeployItemBase(ExecutableDeployItemType::STOREDCONTRACYBYNAME) {}

  std::string name;
  std::string entry_point;
  std::string args;
};

/**
 * @brief Construct a JSON object from a StoredContractByName object.
 *
 * @param j JSON object to construct.
 * @param p StoredContractByName object to construct from.
 */

inline void to_json(nlohmann::json& j, const StoredContractByName& p) {
  j = static_cast<ExecutableDeployItemBase>(p);
  j["name"] = p.name;
  j["entry_point"] = p.entry_point;
  j["args"] = p.args;
}

/**
 * @brief Construct a StoredContractByName object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p StoredContractByName object to construct.
 */

inline void from_json(const nlohmann::json& j, StoredContractByName& p) {
  nlohmann::from_json(j, static_cast<ExecutableDeployItemBase&>(p));
  j.at("name").get_to(p.name);
  j.at("entry_point").get_to(p.entry_point);
  j.at("args").get_to(p.args);
}

}  // namespace Casper