#pragma once

#include <boost/multiprecision/cpp_int.hpp>
#include <cstdint>
#include <vector>

namespace Casper {
struct VestingSchedule {
  uint64_t initial_release_timestamp_millis;

  std::vector<boost::multiprecision::uint512_t> locked_amounts;
};
}  // namespace Casper
