#pragma once

#include <cstdint>
#include <vector>

#include "Types/Definitions.h"
#include "nlohmann/json.hpp"

namespace Casper {
struct VestingSchedule {
  uint64_t initial_release_timestamp_millis;
  std::vector<big_int> locked_amounts;

  VestingSchedule() {}
};

/**
 * @brief Construct a JSON object from a VestingSchedule object.
 *
 * @param j JSON object to construct.
 * @param p VestingSchedule object to construct from.
 */
inline void to_json(nlohmann::json& j, const VestingSchedule& p) {
  // TODO: fill this in
  j = nlohmann::json{"initial_release_timestamp_millis",
                     p.initial_release_timestamp_millis, "locked_amounts",
                     nlohmann::json::array()};
  for (const auto& amount : p.locked_amounts) {
    j["locked_amounts"].push_back(amount.toString());
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
