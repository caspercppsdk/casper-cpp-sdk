#pragma once

#include "Base.h"
#include "Types/NamedArg.h"
#include "nlohmann/json.hpp"

namespace Casper {

struct StoredContractByName {
  std::string name;
  std::string entry_point;
  std::vector<NamedArg> args;

  StoredContractByName() {}
};

/**
 * @brief Construct a JSON object from a StoredContractByName object.
 *
 * @param j JSON object to construct.
 * @param p StoredContractByName object to construct from.
 */

inline void to_json(nlohmann::json& j, const StoredContractByName& p) {
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
  j.at("name").get_to(p.name);
  j.at("entry_point").get_to(p.entry_point);
  j.at("args").get_to(p.args);
}

}  // namespace Casper