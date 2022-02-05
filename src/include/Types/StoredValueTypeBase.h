#pragma once

#include "nlohmann/json.hpp"

namespace Casper {
enum StoredValueType {
  CLVALUE = 1,
  ACCOUNT = 2,
  CONTRACTWASM = 3,
  CONTRACT = 4,
  CONTRACTPACKAGE = 5,
  TRANSFER = 6,
  DEPLOYINFO = 7,
  ERAINFO = 8,
  BID = 9,
  WITHDRAW = 10
};

// Defines the base type for StoredValue types.
struct StoredValueTypeBase {
  StoredValueType type;
};

/**
 * @brief Construct a JSON object from a StoredValueTypeBase object.
 *
 * @param j JSON object to construct.
 * @param p StoredValueTypeBase object to construct from.
 */
inline void to_json(nlohmann::json& j, const StoredValueTypeBase& p) {
  j = nlohmann::json{{"type", p.type}};
}

/**
 * @brief Construct a StoredValueTypeBase object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p StoredValueTypeBase object to construct.
 */
inline void from_json(const nlohmann::json& j, StoredValueTypeBase& p) {
  j.at("type").get_to(p.type);
}

}  // namespace Casper
