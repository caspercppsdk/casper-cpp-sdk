#pragma once
#include "Base.h"
#include "Definitions.h"
#include "nlohmann/json.hpp"

namespace Casper {
struct SeigniorageAllocation {
  bool is_delegator;

  // TODO: make public key instead of string
  std::string delegator_public_key;
  std::string validator_public_key;
  big_int amount;

  SeigniorageAllocation() {}
};

// to_json of SeigniorageAllocation
inline void to_json(nlohmann::json& j, const SeigniorageAllocation& p) {
  if (p.is_delegator) {
    j = nlohmann::json{{"is_delegator", p.is_delegator},
                       {"delegator_public_key", p.delegator_public_key},
                       {"validator_public_key", p.validator_public_key},
                       {"amount", p.amount.toString()}};
  } else {
    j = nlohmann::json{{"is_delegator", p.is_delegator},
                       {"validator_public_key", p.validator_public_key},
                       {"amount", p.amount.toString()}};
  }
}

// from_json of SeigniorageAllocation
inline void from_json(const nlohmann::json& j, SeigniorageAllocation& p) {
  if (j.find("is_delegator") != j.end()) {
    j.at("is_delegator").get_to(p.is_delegator);
  } else {
    p.is_delegator = false;
  }

  if (p.is_delegator) {
    if (j.find("delegator_public_key") != j.end()) {
      j.at("delegator_public_key").get_to(p.delegator_public_key);
    } else {
      throw std::runtime_error("delegator_public_key not found");
    }
  }

  if (j.find("validator_public_key") != j.end()) {
    j.at("validator_public_key").get_to(p.validator_public_key);
  } else {
    throw std::runtime_error("validator_public_key not found");
  }

  if (j.find("amount") != j.end()) {
    j.at("amount").get_to(p.amount);
  } else {
    throw std::runtime_error("amount not found");
  }
}

}  // namespace Casper
