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
 * @brief Construct a JSON object from a EraValidators object.
 *
 * @param j JSON object to construct.
 * @param p EraValidators object to construct from.
 */
inline void to_json(nlohmann::json& j, const EraValidators& p) {
  j = nlohmann::json{{"era_id", p.era_id},
                     {"validator_weights", p.validator_weights}};
  // j = nlohmann::json{{"node_id", p.node_id}, {"address", p.address}};
}

/**
 * @brief Construct a EraValidators object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p EraValidators object to construct.
 */
inline void from_json(const nlohmann::json& j, EraValidators& p) {
  j.at("era_id").get_to(p.era_id);
  j.at("validator_weights").get_to(p.validator_weights);
}

}  // namespace Casper