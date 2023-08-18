#pragma once

#include "Base.h"
#include "JsonRpc/ResultTypes/RpcResult.h"
#include "Types/ExecutionResult.h"

namespace Casper {

/// Result for the "speculative-exec" rpc call.
struct SpeculativeExecResult : public RpcResult {
  /// <summary>
  /// The block hash
  /// </summary>
  std::string block_hash;

  /// <summary>
  /// Execution result.
  /// </summary>
  ExecutionResult execution_result;

  SpeculativeExecResult() {}
};

/**
 * @brief Construct a JSON object from a SpeculativeExecResult object.
 *
 * @param j JSON object to construct.
 * @param p SpeculativeExecResult Result object to construct from.
 */
inline void to_json(nlohmann::json& j, const SpeculativeExecResult& p) {
  j = static_cast<RpcResult>(p);
  j["block_hash"] = p.block_hash;
  j["execution_result"] = p.execution_result;
}

/**
 * @brief Construct a SpeculativeExecResult object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p SpeculativeExecResult object to construct.
 */
inline void from_json(const nlohmann::json& j, SpeculativeExecResult& p) {
  nlohmann::from_json(j, static_cast<RpcResult&>(p));
  j.at("block_hash").get_to(p.block_hash);
  j.at("execution_result").get_to(p.execution_result);
}

}  // namespace Casper
