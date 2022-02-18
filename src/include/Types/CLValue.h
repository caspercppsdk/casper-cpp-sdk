#pragma once
#include <string>
#include "Types/StoredValueTypeBase.h"

namespace Casper {
struct CLValue {
  std::string temp;

  CLValue(std::string temp_) { temp = temp_; }
};
// to json
inline void to_json(nlohmann::json& j, const CLValue& p) {
  j = nlohmann::json{{"temp", p.temp}};
}

// from json
inline void from_json(const nlohmann::json& j, CLValue& p) {
  j.at("temp").get_to(p.temp);
}

}  // namespace Casper
