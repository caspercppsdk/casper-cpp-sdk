#pragma once

#include "RpcResult.h"

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
  GetDeployInfoResult() : deploy_info() {}

  /// The deploy info as a string.
  std::string deploy_info;
};

/**
 * @brief Construct a JSON object from a GetDeployInfoResult object.
 *
 * @param j JSON object to construct.
 * @param p GetDeployInfoResult Result object to construct from.
 */
inline void to_json(nlohmann::json& j, const GetDeployInfoResult& p) {
  j = nlohmann::json{{"deploy_info", p.deploy_info}};
}

/**
 * @brief Construct a GetDeployInfoResult object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p GetDeployInfoResult object to construct.
 */
inline void from_json(const nlohmann::json& j, GetDeployInfoResult& p) {
  j.at("deploy_info").get_to(p.deploy_info);
}
}  // namespace Casper
