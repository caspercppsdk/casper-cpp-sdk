#pragma once

#include "Base.h"
#include "nlohmann/json.hpp"

namespace Casper {
struct CLTypeInfo {
  std::string temp;

  CLTypeInfo(std::string temp_) { temp = temp_; }
  CLTypeInfo() {}
};

// to_json
inline void to_json(nlohmann::json& j, const CLTypeInfo& p) {
  j = nlohmann::json{{"temp", p.temp}};
}

// from_json
inline void from_json(const nlohmann::json& j, CLTypeInfo& p) {
  j.at("temp").get_to(p.temp);
}

}  // namespace Casper
