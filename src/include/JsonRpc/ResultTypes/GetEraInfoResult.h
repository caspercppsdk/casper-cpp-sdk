#pragma once

#include <optional>

#include "RpcResult.h"
#include "Types/EraSummary.h"

namespace Casper {

/// Result for the "chain_get_era_info_by_switch_block" rpc call.
struct GetEraInfoResult : public RpcResult {
  /// <summary>
  /// The era summary.
  /// </summary>
  std::optional<EraSummary> era_summary = std::nullopt;

  GetEraInfoResult() {}
};

/**
 * @brief Construct a JSON object from a GetEraInfoResult object.
 *
 * @param j JSON object to construct.
 * @param p GetStateRootHash Result object to construct from.
 */
inline void to_json(nlohmann::json& j, const GetEraInfoResult& p) {
  j = static_cast<RpcResult>(p);
  if (p.era_summary.has_value()) {
    j["era_summary"] = p.era_summary.value();
  }
}

/**
 * @brief Construct a GetEraInfoResult object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p GetEraInfoResult object to construct.
 */
inline void from_json(const nlohmann::json& j, GetEraInfoResult& p) {
  nlohmann::from_json(j, static_cast<RpcResult&>(p));

  if (j.find("era_summary") != j.end() && !j.at("era_summary").is_null()) {
    p.era_summary = j.at("era_summary").get<EraSummary>();
  }
}

}  // namespace Casper
