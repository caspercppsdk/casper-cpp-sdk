#pragma once

#include "Base.h"
#include "Types/GlobalStateKey.h"
#include "nlohmann/json.hpp"

namespace Casper {
/**
 * @brief A named key in an Account or Contract.
 *
 */
struct NamedKey {
  /// The name of the entry.
  std::string name;

  /// The value of the entry: a Casper GlobalStateKey type.
  GlobalStateKey key;

  NamedKey() {}
};

/**
 * @brief Construct a JSON object from a NamedKey object.
 *
 * @param j JSON object to construct.
 * @param p NamedKey object to construct from.
 */
inline void to_json(nlohmann::json& j, const NamedKey& p) {
  j = {{"name", p.name}, {"key", p.key}};
}

/**
 * @brief Construct a NamedKey object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p NamedKey object to construct.
 */
inline void from_json(const nlohmann::json& j, NamedKey& p) {
  j.at("name").get_to(p.name);
  j.at("key").get_to(p.key);
}
}  // namespace Casper