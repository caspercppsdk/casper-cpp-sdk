#pragma once

#include <vector>

#include "ValidatorWeight.h"
#include "nlohmann/json.hpp"

namespace Casper {
struct EraValidators {
  uint64_t era_id;
  std::vector<ValidatorWeight> validator_weights;
};

/**
 * @brief Construct a JSON object from a Peer object.
 *
 * @param j JSON object to construct.
 * @param p Peer object to construct from.
 */
inline void to_json(nlohmann::json& j, const EraValidators& p) {
  // j = nlohmann::json{{"node_id", p.node_id}, {"address", p.address}};
}

/**
 * @brief Construct a Peer object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p Peer object to construct.
 */
inline void from_json(const nlohmann::json& j, EraValidators& p) {
  // j.at("node_id").get_to(p.node_id);
  // j.at("address").get_to(p.address);
}

}  // namespace Casper