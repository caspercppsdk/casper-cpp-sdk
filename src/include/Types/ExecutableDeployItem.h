#pragma once

#include "nlohmann/json.hpp"

namespace Casper {
enum ExecutableDeployItemType {
  MODULEBYTES = 1,
  STOREDCONTRACTBYHASH = 2,
  STOREDCONTRACYBYNAME = 3,
  STOREDVERSIONEDCONTRACTBYHASH = 4,
  STOREDVERSIONEDCONTRACTBYNAME = 5,
  TRANSFER = 6, // Defined below.
};

// Defines the base type for StoredValue types.
struct ExecutableDeployItemBase {
  ExecutableDeployItemType type;
  // TODO: Change default type below
  ExecutableDeployItemBase() {}
  ExecutableDeployItemBase(ExecutableDeployItemType type) : type(type) {}
};

/**
 * @brief Construct a JSON object from a StoredValueTypeBase object.
 *
 * @param j JSON object to construct.
 * @param p StoredValueTypeBase object to construct from.
 */
inline void to_json(nlohmann::json& j, const ExecutableDeployItemBase& p) {
  j = nlohmann::json{{"type", p.type}};
}

/**
 * @brief Construct a ExecutableDeployItemBase object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p ExecutableDeployItemBase object to construct.
 */
inline void from_json(const nlohmann::json& j, ExecutableDeployItemBase& p) {
  j.at("type").get_to(p.type);
}

}  // namespace Casper
