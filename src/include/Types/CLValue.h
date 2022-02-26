#pragma once

#include "Base.h"
#include "nlohmann/json.hpp"

namespace Casper {
struct CLValue {
  // TODO: Fill here
  CLValue() {}
};
// to json
inline void to_json(nlohmann::json& j, const CLValue& p) {
  // fill here
}

// from json
inline void from_json(const nlohmann::json& j, CLValue& p) {
  // fill here
}

}  // namespace Casper
