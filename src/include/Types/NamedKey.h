#pragma once
#include <string>
#include <vector>

#include "GlobalStateKey.h"
#include "nlohmann/json.hpp"

namespace Casper {
struct NamedKey {
  std::string name;
  GlobalStateKey key;
};

/**
 * @brief Construct a JSON object from a NamedKey object.
 *
 * @param j JSON object to construct.
 * @param p Peer object to construct from.
 */
inline void to_json(nlohmann::json& j, const NamedKey& p) {
  j = nlohmann::json{{"name", p.name}, {"key", p.key}};
  // j = nlohmann::json{{"node_id", p.node_id}, {"address", p.address}};
}

/**
 * @brief Construct a NamedKey object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p Peer object to construct.
 */
inline void from_json(const nlohmann::json& j, NamedKey& p) {
  // j.at("node_id").get_to(p.node_id);
  // j.at("address").get_to(p.address);
}
}  // namespace Casper