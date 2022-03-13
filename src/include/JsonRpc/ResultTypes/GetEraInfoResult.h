#pragma once

#include <optional>
#include "RpcResult.h"
#include "Types/EraSummary.h"

/**
 * @brief Result for the "chain_get_era_info_by_switch_block" rpc call.
 *
 */
namespace Casper {

struct GetEraInfoResult : public RpcResult {
 public:
  /**
   * @brief Construct a new GetEraInfoResult object.
   *
   */
  GetEraInfoResult(EraSummary era_summary_) : era_summary(era_summary_) {}
  GetEraInfoResult() {}

  std::optional<EraSummary> era_summary = std::nullopt;  // Optional.
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

  if (j.count("era_summary") != 0) {
    p.era_summary = j.at("era_summary").get<EraSummary>();
  }
}

}  // namespace Casper
