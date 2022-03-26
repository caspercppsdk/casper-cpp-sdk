#pragma once

#include "Base.h"
#include "Types/ValidatorWeight.h"
#include "nlohmann/json.hpp"

namespace Casper {
/// <summary>
/// Validator and weights for an Era.
/// </summary>
struct EraValidators {
  /// <summary>
  /// The Era Id.
  /// </summary>
  uint64_t era_id;

  /// <summary>
  /// List with each validator weight in the Era
  /// </summary>
  std::vector<ValidatorWeight> validator_weights;

  EraValidators() {}
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