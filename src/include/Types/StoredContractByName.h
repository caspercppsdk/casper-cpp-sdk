#pragma once

#include "Base.h"
#include "Types/NamedArg.h"
#include "nlohmann/json.hpp"

namespace Casper {
/// Stored contract referenced by a named key existing in the signer's account
/// context, entry point and an instance of [`RuntimeArgs`].
struct StoredContractByName {
  /// Named key.
  std::string name;
  /// Name of an entry point.
  std::string entry_point;
  /// Runtime arguments.
  std::vector<NamedArg> args;

  StoredContractByName() {}

  StoredContractByName(const std::string& name, const std::string& entry_point,
                       const std::vector<NamedArg>& args = {})
      : name(name), entry_point(entry_point), args(args) {}
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
  p.entry_point = j.at("entry_point").get<std::string>();
  j.at("args").get_to(p.args);
}

}  // namespace Casper