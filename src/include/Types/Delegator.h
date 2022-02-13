#pragma once

#include "nlohmann/json.hpp"

namespace Casper {
struct Delegator {
  // TODO: fill this in
};
/**
 * @brief Construct a JSON object from a Delegator object.
 *
 * @param j JSON object to construct.
 * @param p Delegator object to construct from.
 */
inline void to_json(nlohmann::json& j, const Delegator& p) {
  // TODO: fill this in
  j = nlohmann::json{};
}

/**
 * @brief Construct a Delegator object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p Delegator object to construct.
 */
inline void from_json(const nlohmann::json& j, Delegator& p) {
  // fill this in
  p = Delegator();
}
}  // namespace Casper
