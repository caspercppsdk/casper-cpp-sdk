#pragma once
#include "Base.h"
#include "nlohmann/json.hpp"

#include "Types/GlobalStateKey.h"
#include "magic_enum/magic_enum.hpp"

namespace Casper {
enum class OpKind { Read, Write, Add, NoOp };

struct Operation {
  // TODO: Make GlobalStateKey instead of string
  std::string key;
  OpKind kind;

  Operation() {}
};

// to_json of Operation
inline void to_json(nlohmann::json& j, const Operation& p) {
  j = nlohmann::json{{"key", p.key}, {"kind", magic_enum::enum_name(p.kind)}};
}

// from_json of Operation
inline void from_json(const nlohmann::json& j, Operation& p) {
  j.at("key").get_to(p.key);
  j.at("kind").get_to(p.kind);
}

}  // namespace Casper
