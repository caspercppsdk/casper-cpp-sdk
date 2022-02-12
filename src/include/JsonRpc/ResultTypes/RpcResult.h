#pragma once

#include "Base.h"
#include "nlohmann/json.hpp"

/**
 * @brief Base struct for all RPC result types.
 *
 */
namespace Casper {
struct RpcResult {
 public:
  /**
   * @brief Construct a new Rpc Result object
   *
   */
  RpcResult() {}
  RpcResult(std::string api_version_) : api_version(api_version_) {}
  /// The API version as a string.
  std::string api_version;
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
  j.at("api_version").get_to(p.api_version);
}
}  // namespace Casper
