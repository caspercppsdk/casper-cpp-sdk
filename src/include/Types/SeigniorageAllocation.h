#pragma once
#include "Base.h"
#include "nlohmann/json.hpp"

namespace Casper {
/// <summary>
/// Information about a seigniorage allocation
/// </summary>
struct SeigniorageAllocation {
  /// <summary>
  /// True if a delegator reward allocation.
  /// </summary>
  bool is_delegator;

  /// <summary>
  /// Public key of the delegator.
  /// </summary>
  PublicKey delegator_public_key;

  /// <summary>
  /// Public key of the validator
  /// </summary>
  PublicKey validator_public_key;

  /// <summary>
  /// Amount allocated as a reward
  /// </summary>
  uint512_t amount;

  SeigniorageAllocation() {}
};

// to_json of SeigniorageAllocation
inline void to_json(nlohmann::json& j, const SeigniorageAllocation& p) {
  if (p.is_delegator) {
    j = nlohmann::json{{"delegator_public_key", p.delegator_public_key},
                       {"validator_public_key", p.validator_public_key},
                       {"amount", p.amount}};
  } else {
    j = nlohmann::json{{"validator_public_key", p.validator_public_key},
                       {"amount", p.amount}};
  }
}

// from_json of SeigniorageAllocation
inline void from_json(const nlohmann::json& j, SeigniorageAllocation& p) {
  nlohmann::json typeJSON;

  if (j.count("Delegator") != 0) {
    p.is_delegator = true;
    typeJSON = j.at("Delegator");
    if (typeJSON.find("delegator_public_key") != typeJSON.end()) {
      typeJSON.at("delegator_public_key").get_to(p.delegator_public_key);
    } else {
      throw std::runtime_error("delegator_public_key not found");
    }
  } else {
    p.is_delegator = false;
    typeJSON = j.at("Validator");
  }

  if (typeJSON.find("validator_public_key") != typeJSON.end()) {
    typeJSON.at("validator_public_key").get_to(p.validator_public_key);
  } else {
    throw std::runtime_error("validator_public_key not found");
  }

  if (typeJSON.find("amount") != typeJSON.end()) {
    typeJSON.at("amount").get_to(p.amount);
  } else {
    throw std::runtime_error("amount not found");
  }
}

}  // namespace Casper
