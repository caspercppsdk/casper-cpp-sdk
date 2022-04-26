#pragma once

#include "Base.h"
#include "Types/NamedArg.h"
#include "nlohmann/json.hpp"

namespace Casper {

/// Stored contract referenced by its [`ContractHash`], entry point and an
/// instance of [`RuntimeArgs`].
struct StoredContractByHash {
  /// Contract hash.
  std::string hash;
  /// Name of an entry point.
  std::string entry_point;
  /// Runtime arguments.
  std::vector<NamedArg> args;

  StoredContractByHash() {}

  StoredContractByHash(const std::string& hash, const std::string& entry_point,
                       const std::vector<NamedArg>& args = {})
      : hash(hash), entry_point(entry_point), args(args) {}
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
  // std::cout << "entry point enter" << std::endl;
  p.entry_point = j.at("entry_point").get<std::string>();
  // std::cout << "entry point exit" << std::endl;
  j.at("args").get_to(p.args);
}

}  // namespace Casper