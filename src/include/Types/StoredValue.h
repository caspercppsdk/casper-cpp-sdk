#pragma once
#include <optional>
#include <string>
#include <vector>

#include "Types/Account.h"
#include "Types/Contract.h"
#include "Types/StoredValueTypeBase.h"
#include "Types/Transfer.h"
#include "Types/UnbondingPurse.h"
#include "Types/Withdraw.h"
#include "nlohmann/json.hpp"

namespace Casper {

struct StoredValue {
  StoredValueTypeBase value;

  StoredValue() {}
  StoredValue(StoredValueTypeBase value_) : value(value_) {}
};

/**
 * @brief Construct a JSON object from a StoredValue object.
 *
 * @param j JSON object to construct.
 * @param p StoredValue object to construct from.
 */
inline void to_json(nlohmann::json& j, const StoredValue& p) {
  j = nlohmann::json{"value", p.value};
}

/**
 * @brief Construct a StoredValue object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p StoredValue object to construct.
 */
inline void from_json(const nlohmann::json& j, StoredValue& p) {
  j.at("value").get_to(p.value);
}

}  // namespace Casper