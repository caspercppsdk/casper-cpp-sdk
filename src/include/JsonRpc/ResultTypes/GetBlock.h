#pragma once

#include <vector>

#include "RpcResult.h"
#include "Types/JsonBlock.h"
#include "Types/Transfer.h"

/**
 * @brief Result for the "chain_get_block" rpc call.
 *
 */
namespace Casper {
struct GetBlockResult : public RpcResult {
 public:
  /**
   * @brief Construct a new GetBlockResult object.
   *
   */
  GetBlockResult(std::string api_version_, JsonBlock block_)
      : api_version(api_version_), block(block_) {}
  GetBlockResult() {}

  std::string api_version;
  JsonBlock block;  // Optional.
};

/**
 * @brief Construct a JSON object from a GetBlockResult object.
 *
 * @param j JSON object to construct.
 * @param p GetBlockResult Result object to construct from.
 */
inline void to_json(nlohmann::json& j, const GetBlockResult& p) {
  j = nlohmann::json{{"api_version", p.api_version}, {"block", p.block}};
}

/**
 * @brief Construct a GetBlockResult object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p GetBlockResult object to construct.
 */
inline void from_json(const nlohmann::json& j, GetBlockResult& p) {
  j.at("api_version").get_to(p.api_version);

  if (!j.at("block").is_null()) from_json(j.at("block"), p.block);
}
}  // namespace Casper
