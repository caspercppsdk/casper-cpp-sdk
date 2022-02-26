#pragma once

#include "Base.h"
#include "nlohmann/json.hpp"

namespace Casper {
struct NamedArg {
  std::string name;
  // TODO: Uncomment this
  // CLValue value;

  NamedArg() {}
};

// to_json of NamedArg
inline void to_json(nlohmann::json& j, const NamedArg& p) {
  // TODO: Fill this in
}

// from_json of NamedArg
inline void from_json(const nlohmann::json& j, NamedArg& p) {
  // TODO: Fill this in
}

}  // namespace Casper
