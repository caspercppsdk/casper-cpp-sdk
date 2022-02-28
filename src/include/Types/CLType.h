#pragma once

#include "Base.h"
#include "Types/CLTypeInfo.h"
#include "nlohmann/json.hpp"

namespace Casper {
/// <summary>
/// Casper types, i.e. types which can be stored and manipulated by smart
/// contracts. Provides a description of the underlying data type of a
/// `CLValue`.
/// </summary>

struct CLType {
  std::optional<CLTypeInfo> type_info = std::nullopt;
  std::optional<CLMapTypeInfo> map_type_info = std::nullopt;
  operator CLTypeEnum() const { return CLTypeEnum::Map; }

  CLType() {}
};

// to_json of CLType
inline void to_json(nlohmann::json& j, const CLType& p) {
  j = nlohmann::json{};

  if (p.type_info.has_value()) {
    j = p.type_info.value();
  } else if (p.map_type_info.has_value()) {
    j["Map"] = p.map_type_info.value();
  }
}

// from_json of CLType
inline void from_json(const nlohmann::json& j, CLType& p) {
  if (j.find("Map") != j.end()) {
    p.map_type_info = j.at("Map").get<CLMapTypeInfo>();
  } else if (j.is_string()) {
    j.get_to(p.type_info);
  }
}

}  // namespace Casper
