#pragma once

#include "Definitions.h"
#include <cstdint>
#include <vector>

namespace Casper {
struct VestingSchedule {
  uint64_t initial_release_timestamp_millis;

  big_int locked_amounts;
};
}  // namespace Casper
