#pragma once

#include "Base.h"

// libs
#include "magic_enum/magic_enum.hpp"
#include "nlohmann/json.hpp"

// Types
#include "Types/Transform.h"

namespace Casper {
/// Intermediary structure for a transform.
struct TransformEntry {
  std::string key;
  Transform transform;

  TransformEntry() {}
};

// to_json of TransformEntry
inline void to_json(nlohmann::json& j, const TransformEntry& p) {
  j = nlohmann::json{};
  j["key"] = p.key;

  if (p.transform.Identity.has_value()) {
    j["transform"] = p.transform.Identity.value();
  } else {
    j["transform"] = p.transform;
  }
}

// from_json of TransformEntry
inline void from_json(const nlohmann::json& j, TransformEntry& p) {
  j.at("key").get_to(p.key);
  if (j.at("transform").is_string() &&
      j.at("transform").get<std::string>() == "Identity") {
    p.transform.Identity = "Identity";
  } else {
    j.at("transform").get_to(p.transform);
  }
}

}  // namespace Casper
