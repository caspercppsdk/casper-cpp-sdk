#pragma once
#include <string>
#include <vector>

#include "GlobalStateKey.h"
#include "nlohmann/json.hpp"

namespace Casper {
struct NamedKey {
  std::string name;
  GlobalStateKey key;
};
}  // namespace Casper