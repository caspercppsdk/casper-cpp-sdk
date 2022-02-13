#pragma once

#include <cstdint>
#include <vector>
#include "Types/Definitions.h"

namespace Casper {
struct VestingSchedule {
  uint64_t initial_release_timestamp_millis;

  big_int locked_amounts;

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
  j = nlohmann::json{};
}

/**
 * @brief Construct a VestingSchedule object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p VestingSchedule object to construct.
 */
inline void from_json(const nlohmann::json& j, VestingSchedule& p) {
  // fill this in
  p = VestingSchedule();
}
}  // namespace Casper
