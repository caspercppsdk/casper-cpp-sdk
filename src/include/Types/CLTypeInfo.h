#pragma once

#include "Base.h"
#include "nlohmann/json.hpp"

namespace Casper {
struct CLTypeInfo {
  // TODO:
  CLTypeInfo() {}
};

// to_json
inline void to_json(nlohmann::json& j, const CLTypeInfo& p) {
  // TODO:
}

// from_json
inline void from_json(const nlohmann::json& j, CLTypeInfo& p) {
  // TODO:
}

}  // namespace Casper
