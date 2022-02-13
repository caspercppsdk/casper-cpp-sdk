#pragma once

#include "Definitions.h"
#include "nlohmann/json.hpp"

namespace Casper {
struct ValidatorWeight {
  PublicKey public_key;
  big_int weight;
  // TODO: Fill in this class
};

/**
 * @brief Construct a JSON object from a ValidatorWeight object.
 *
 * @param j JSON object to construct.
 * @param p ValidatorWeight object to construct from.
 */
inline void to_json(nlohmann::json& j, const ValidatorWeight& p) {
  j = nlohmann::json{};
  // TODO: Fill in this function
}

/**
 * @brief Construct a ValidatorWeight object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p ValidatorWeight object to construct.
 */
inline void from_json(const nlohmann::json& j, ValidatorWeight& p) {
  // TODO: Fill in this function
}
}  // namespace Casper