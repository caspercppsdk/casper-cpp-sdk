#pragma once

#include "Base.h"
#include "nlohmann/json.hpp"

namespace Casper {

/// Base struct for all RPC result types.
struct RpcResult {
  /// <summary>
  /// The RPC API version.
  /// </summary>
  std::string api_version;

  RpcResult() {}
};

/**
 * @brief Construct a JSON object from a RpcResult object.
 *
 * @param j JSON object to construct.
 * @param p RpcResult Result object to construct from.
 */
inline void to_json(nlohmann::json& j, const RpcResult& p) {
  j = nlohmann::json{{"api_version", p.api_version}};
}

/**
 * @brief Construct a RpcResult object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p RpcResult object to construct.
 */
inline void from_json(const nlohmann::json& j, RpcResult& p) {
  if (!j.is_null() && j.find("api_version") != j.end() &&
      !j.at("api_version").is_null()) {
    j.at("api_version").get_to(p.api_version);
  }
}

}  // namespace Casper
