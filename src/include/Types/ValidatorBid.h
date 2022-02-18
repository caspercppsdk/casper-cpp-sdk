#pragma once

#include <vector>

#include "Types/Bid.h"
#include "nlohmann/json.hpp"

namespace Casper {
struct ValidatorBid {
  // TODO: Make public key instead of string
  std::string public_key;
  Bid bid;

  ValidatorBid() {}
  ValidatorBid(std::string public_key_, Bid bid_)
      : public_key(public_key_), bid(bid_) {}
};

/**
 * @brief Construct a JSON object from a ValidatorBid object.
 *
 * @param j JSON object to construct.
 * @param p ValidatorBid object to construct from.
 */
inline void to_json(nlohmann::json& j, const ValidatorBid& p) {
  if (p.public_key.empty()) {
    j = nlohmann::json{{"bid", p.bid}};
  } else {
    j = nlohmann::json{{"public_key", p.public_key}};
  }
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
    j.at("bid").get_to(p.bid);
  }
}

}  // namespace Casper