#pragma once

#include <cstdint>
#include <vector>

#include "nlohmann/json.hpp"

namespace Casper {
/// <summary>
/// Vesting schedule for a genesis validator. `None` if non-genesis validator.
/// </summary>
struct VestingSchedule {
  /// <summary>
  /// Timestamp as milliseconds since epoch.
  /// </summary>
  uint64_t initial_release_timestamp_millis;

  /// <summary>
  /// Amount of locked tokens.
  /// </summary>
  std::vector<uint512_t> locked_amounts;

  VestingSchedule() {}
};

/**
 * @brief Construct a JSON object from a VestingSchedule object.
 *
 * @param j JSON object to construct.
 * @param p VestingSchedule object to construct from.
 */
inline void to_json(nlohmann::json& j, const VestingSchedule& p) {
  j = nlohmann::json{"initial_release_timestamp_millis",
                     p.initial_release_timestamp_millis, "locked_amounts",
                     nlohmann::json::array()};
  for (const auto& amount : p.locked_amounts) {
    j["locked_amounts"].push_back(u512ToDec(amount));
  }
}

/**
 * @brief Construct a VestingSchedule object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p VestingSchedule object to construct.
 */
inline void from_json(const nlohmann::json& j, VestingSchedule& p) {
  j.at("initial_release_timestamp_millis")
      .get_to(p.initial_release_timestamp_millis);
  j.at("locked_amounts").get_to(p.locked_amounts);
}
}  // namespace Casper
