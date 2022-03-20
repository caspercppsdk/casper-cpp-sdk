#pragma once

#include "Base.h"
#include "Types/NamedArg.h"
#include "nlohmann/json.hpp"

namespace Casper {

struct StoredContractByHash {
  std::string hash;
  std::string entry_point;
  std::vector<NamedArg> args;

  StoredContractByHash() {}
};

/**
 * @brief Construct a JSON object from a StoredContractByHash object.
 *
 * @param j JSON object to construct.
 * @param p StoredContractByHash object to construct from.
 */

inline void to_json(nlohmann::json& j, const StoredContractByHash& p) {
  j["hash"] = p.hash;
  j["entry_point"] = p.entry_point;
  j["args"] = p.args;
}

/**
 * @brief Construct a StoredContractByHash object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p StoredContractByHash object to construct.
 */

inline void from_json(const nlohmann::json& j, StoredContractByHash& p) {
  j.at("hash").get_to(p.hash);
  j.at("entry_point").get_to(p.entry_point);
  j.at("args").get_to(p.args);
}

}  // namespace Casper