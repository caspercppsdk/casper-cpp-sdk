#pragma once

#include <optional>

#include "Base.h"
#include "Types/NamedArg.h"
#include "nlohmann/json.hpp"

namespace Casper {

struct StoredVersionedContractByName {
  std::string name;
  std::optional<uint32_t> version = std::nullopt;
  std::string entry_point;
  std::vector<NamedArg> args;

  StoredVersionedContractByName() {}
};

/**
 * @brief Construct a JSON object from a StoredVersionedContractByName object.
 *
 * @param j JSON object to construct.
 * @param p StoredVersionedContractByName object to construct from.
 */

inline void to_json(nlohmann::json& j, const StoredVersionedContractByName& p) {
  j = nlohmann::json{
      {"name", p.name},
      {"entry_point", p.entry_point},
      {"args", p.args},
  };

  if (p.version.has_value()) {
    j["version"] = p.version.value();
  }
}

/**
 * @brief Construct a StoredVersionedContractByName object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p StoredVersionedContractByName object to construct.
 */

inline void from_json(const nlohmann::json& j,
                      StoredVersionedContractByName& p) {
  j.at("name").get_to(p.name);
  j.at("entry_point").get_to(p.entry_point);
  j.at("args").get_to(p.args);

  if (j.find("version") != j.end()) {
    p.version = j.at("version").get<uint32_t>();
  }
}

}  // namespace Casper