#pragma once

#include "Base.h"
#include "JsonRpc/ResultTypes/RpcResult.h"
#include "Types/Deploy.h"
#include "Types/ExecutionResult.h"
/**
 * @brief Result for the "info_get_deploy" rpc call.
 *
 */
namespace Casper {
struct GetDeployInfoResult : public RpcResult {
 public:
  /**
   * @brief Construct a new GetDeployResult object.
   *
   */
  Deploy deploy;
  std::vector<ExecutionResult> execution_results;

  GetDeployInfoResult() {}
};

/**
 * @brief Construct a JSON object from a GetDeployInfoResult object.
 *
 * @param j JSON object to construct.
 * @param p GetDeployInfoResult Result object to construct from.
 */
inline void to_json(nlohmann::json& j, const GetDeployInfoResult& p) {
  j = static_cast<RpcResult>(p);
  j["deploy"] = p.deploy;
  j["execution_results"] = p.execution_results;
}

/**
 * @brief Construct a GetDeployInfoResult object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p GetDeployInfoResult object to construct.
 */
inline void from_json(const nlohmann::json& j, GetDeployInfoResult& p) {
  nlohmann::from_json(j, static_cast<RpcResult&>(p));
  j.at("deploy").get_to(p.deploy);
  j.at("execution_results").get_to(p.execution_results);
}
}  // namespace Casper
