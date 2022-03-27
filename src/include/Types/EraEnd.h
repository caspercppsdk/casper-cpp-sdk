#pragma once

#include "Base.h"
#include "Types/PublicKey.h"
#include "Types/ValidatorWeight.h"
#include "nlohmann/json.hpp"
namespace Casper {
/// <summary>
/// A validator reward
/// </summary>
struct Reward {
  /// <summary>
  /// Reward amount
  /// </summary>
  uint64_t amount;

  /// <summary>
  /// Validator public key
  /// </summary>
  PublicKey validator;

  Reward() {}
};

// to_json of Reward
inline void to_json(nlohmann::json& j, const Reward& p) {
  j = nlohmann::json{
      {"amount", p.amount},
      {"validator", p.validator},
  };
}

// from_json of Reward
inline void from_json(const nlohmann::json& j, Reward& p) {
  j.at("amount").get_to(p.amount);
  j.at("validator").get_to(p.validator);
}

/// <summary>
/// Equivocation and reward information to be included in the terminal block.
/// </summary>
struct EraReport {
  /// <summary>
  /// List of public keys of the equivocators
  /// </summary>
  std::vector<PublicKey> equivocators;

  /// <summary>
  /// List of public keys of inactive validators
  /// </summary>
  std::vector<PublicKey> inactive_validators;

  /// <summary>
  /// List of validators with rewards
  /// </summary>
  std::vector<Reward> rewards;

  EraReport() {}
};

// to_json of EraReport
inline void to_json(nlohmann::json& j, const EraReport& p) {
  j = nlohmann::json{
      {"equivocators", p.equivocators},
      {"inactive_validators", p.inactive_validators},
      {"rewards", p.rewards},
  };
}

// from_json of EraReport
inline void from_json(const nlohmann::json& j, EraReport& p) {
  j.at("equivocators").get_to(p.equivocators);
  j.at("inactive_validators").get_to(p.inactive_validators);
  j.at("rewards").get_to(p.rewards);
}

/// <summary>
/// Era end report and list of validator weights for next era
/// </summary>
struct EraEnd {
  /// <summary>
  /// Era report
  /// </summary>
  EraReport era_report;

  /// <summary>
  /// A list of validator weights for the next era
  /// </summary>
  std::vector<ValidatorWeight> next_era_validator_weights;

  EraEnd() {}
};

// to_json of EraEnd
inline void to_json(nlohmann::json& j, const EraEnd& p) {
  j = nlohmann::json{
      {"era_report", p.era_report},
      {"next_era_validator_weights", p.next_era_validator_weights},
  };
}

// from_json of EraEnd
inline void from_json(const nlohmann::json& j, EraEnd& p) {
  j.at("era_report").get_to(p.era_report);
  j.at("next_era_validator_weights").get_to(p.next_era_validator_weights);
}

}  // namespace Casper
