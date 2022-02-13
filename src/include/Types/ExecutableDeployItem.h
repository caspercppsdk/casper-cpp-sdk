#pragma once

#include "magic_enum/magic_enum.hpp"
#include "nlohmann/json.hpp"

namespace Casper {

enum class ExecutableDeployItemType {
  MODULEBYTES = 1,
  STOREDCONTRACTBYHASH = 2,
  STOREDCONTRACYBYNAME = 3,
  STOREDVERSIONEDCONTRACTBYHASH = 4,
  STOREDVERSIONEDCONTRACTBYNAME = 5,
  TRANSFER = 6,  // Defined below.
};

std::ostream& operator<<(std::ostream& os,
                         const ExecutableDeployItemType& obj) {
  os << magic_enum::enum_name(obj);
  return os;
}

// Defines the base type for StoredValue types.
struct ExecutableDeployItemBase {
  ExecutableDeployItemType type;

  ExecutableDeployItemBase(ExecutableDeployItemType type) : type(type) {}
  ExecutableDeployItemBase() {}
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
  if (!j.at("type").is_null())
    j.at("type").get_to(p.type);
}

}  // namespace Casper
