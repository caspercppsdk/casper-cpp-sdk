#pragma once

#include <vector>

#include "Types/Bid.h"
#include "nlohmann/json.hpp"

namespace Casper {
struct ValidatorBid {
  /// <summary>
  /// Public key of the validator.
  /// </summary>
  PublicKey public_key;

  /// <summary>
  /// Bid of the validator.
  /// </summary>
  Bid bid;

  ValidatorBid() {}
};

/**
 * @brief Construct a JSON object from a ValidatorBid object.
 *
 * @param j JSON object to construct.
 * @param p ValidatorBid object to construct from.
 */
inline void to_json(nlohmann::json& j, const ValidatorBid& p) {
  j = nlohmann::json{{"public_key", p.public_key}, {"bid", p.bid}};
}

/**
 * @brief Construct a ValidatorBid object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p ValidatorBid object to construct.
 */
inline void from_json(const nlohmann::json& j, ValidatorBid& p) {
  if (j.find("public_key") != j.end()) {
    j.at("public_key").get_to(p.public_key);
  } else {
    throw std::runtime_error("ValidatorBid: public_key not found");
  }
  if (j.find("bid") != j.end()) {
    j.at("bid").get_to(p.bid);
  } else {
    throw std::runtime_error("ValidatorBid: Bid not found");
  }
  p.bid.validator_public_key = p.public_key;
}

}  // namespace Casper