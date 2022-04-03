#pragma once

#include "Base.h"
#include "Types/CLType.h"
#include "nlohmann/json.hpp"

namespace Casper {

struct CLMapType {
  CLType key;
  CLType value;
};

// to json
inline void to_json(nlohmann::json& j, const CLMapType& p) {
  j = nlohmann::json{};

  to_json(j["key"], p.key_type);
  to_json(j["value"], p.value_type);
}

// from json
inline void from_json(const nlohmann::json& j, CLMapType& p) {
    nlohmann::detail::
  from_json(j.at("key"), p.key_type);
  from_json(j.at("value"), p.value_type);
}

}  // namespace Casper