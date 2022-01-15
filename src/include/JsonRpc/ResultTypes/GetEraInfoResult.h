#pragma once

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
  GetEraInfoResult() {}

  /// The state root hash as a string.
  std::string api_version;
  EraSummary era_summary;  // Optional.
};

/**
 * @brief Construct a JSON object from a GetEraInfoResult object.
 *
 * @param j JSON object to construct.
 * @param p GetStateRootHash Result object to construct from.
 */
inline void to_json(nlohmann::json& j, const GetEraInfoResult& p) {
  j = nlohmann::json{{"api_version", p.api_version}};
}

/**
 * @brief Construct a GetEraInfoResult object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p GetEraInfoResult object to construct.
 */
inline void from_json(const nlohmann::json& j, GetEraInfoResult& p) {
  j.at("api_version").get_to(p.api_version);

  if (!j.at("era_summary").is_null())
    from_json(j.at("era_summary"), p.era_summary);
}
}  // namespace Casper
