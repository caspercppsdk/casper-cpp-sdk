#pragma once
#include "Base.h"
#include "Types/GlobalStateKey.h"
#include "magic_enum/magic_enum.hpp"
#include "nlohmann/json.hpp"

namespace Casper {
/// <summary>
/// The type of operation performed while executing a deploy.
/// </summary>
enum class OpKind { Read, Write, Add, NoOp };

/// <summary>
/// An operation performed while executing a deploy.
/// </summary>
struct Operation {
  /// <summary>
  /// The formatted string of the `GlobalStateKey`.
  /// </summary>
  GlobalStateKey key;

  /// <summary>
  /// The type of operation.
  /// </summary>
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
