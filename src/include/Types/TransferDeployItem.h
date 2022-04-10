#pragma once

#include "Base.h"
#include "Types/NamedArg.h"
#include "nlohmann/json.hpp"

namespace Casper {

/// A native transfer which does not contain or reference a WASM code.
struct TransferDeployItem {
  /// Runtime arguments.
  std::vector<NamedArg> args;

  TransferDeployItem() {}
};

/**
 * @brief Construct a JSON object from a TransferDeployItem object.
 *
 * @param j JSON object to construct.
 * @param p TransferDeployItem object to construct from.
 */

inline void to_json(nlohmann::json& j, const TransferDeployItem& p) {
  j["args"] = p.args;
}

/**
 * @brief Construct a TransferDeployItem object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p TransferDeployItem object to construct.
 */

inline void from_json(const nlohmann::json& j, TransferDeployItem& p) {
  j.at("args").get_to(p.args);
}

}  // namespace Casper