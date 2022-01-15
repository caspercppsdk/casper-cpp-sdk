#pragma once
#include <optional>
#include <string>
#include <vector>

#include "nlohmann/json.hpp"

namespace Casper {
struct CLValue;
struct Account;
struct Contract;
struct ContractPackage;
struct Transfer;
struct DeployInfo;
struct EraInfo;
struct UnbondingPurse;
struct Bid;
/**
 * @brief
 *
 */
struct StoredValue {
 public:
  /**
   * @brief
   *
   */
  StoredValue() {}

  // TODO: add to_json and from_json for all the classes given below
  std::optional<CLValue> cl_value = std::nullopt;
  std::optional<Account> account = std::nullopt;
  std::optional<std::string> contract_wasm = std::nullopt;
  std::optional<Contract> contract = std::nullopt;
  std::optional<ContractPackage> contract_package = std::nullopt;
  std::optional<Transfer> transfer = std::nullopt;
  std::optional<DeployInfo> deploy_info = std::nullopt;
  std::optional<EraInfo> era_info = std::nullopt;
  std::optional<Bid> bid = std::nullopt;
  std::optional<std::vector<UnbondingPurse>> withdraw = std::nullopt;
};

/**
 * @brief Construct a JSON object from a StoredValue object.
 *
 * @param j JSON object to construct.
 * @param p StoredValue object to construct from.
 */
inline void to_json(nlohmann::json& j, const StoredValue& p) {
  j = nlohmann::json{};

  if (p.cl_value != std::nullopt) {
    j["CLValue"] = p.cl_value.value();
  }

  if (p.account != std::nullopt) {
    j["Account"] = p.account.value();
  }

  if (p.contract_wasm != std::nullopt) {
    j["ContractWasm"] = p.contract_wasm.value();
  }

  if (p.contract_package != std::nullopt) {
    j["ContractPackage"] = p.contract_package.value();
  }

  if (p.transfer != std::nullopt) {
    j["Transfer"] = p.transfer.value();
  }

  if (p.deploy_info != std::nullopt) {
    j["DeployInfo"] = p.deploy_info.value();
  }

  if (p.era_info != std::nullopt) {
    j["EraInfo"] = p.era_info.value();
  }

  if (p.bid != std::nullopt) {
    j["Bid"] = p.bid.value();
  }

  if (p.withdraw != std::nullopt) {
    j["Withdraw"] = p.withdraw.value();
  }
}

/**
 * @brief Construct a StoredValue object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p StoredValue object to construct.
 */
inline void from_json(const nlohmann::json& j, StoredValue& p) {
  if (j.count("CLValue") != 0) {
    p.cl_value = j.at("CLValue").get<CLValue>();
  }

  if (j.count("Account") != 0) {
    p.account = j.at("Account").get<Account>();
  }

  if (j.count("ContractWasm") != 0) {
    p.contract_wasm = j.at("ContractWasm").get<std::string>();
  }

  if (j.count("Contract") != 0) {
    p.contract = j.at("Contract").get<Contract>();
  }

  if (j.count("ContractPackage") != 0) {
    p.contract_package = j.at("ContractPackage").get<ContractPackage>();
  }

  if (j.count("Transfer") != 0) {
    p.transfer = j.at("Transfer").get<Transfer>();
  }

  if (j.count("DeployInfo") != 0) {
    p.deploy_info = j.at("DeployInfo").get<DeployInfo>();
  }

  if (j.count("EraInfo") != 0) {
    p.era_info = j.at("EraInfo").get<EraInfo>();
  }

  if (j.count("Bid") != 0) {
    p.bid = j.at("Bid").get<Bid>();
  }

  if (j.count("Withdraw") != 0) {
    p.withdraw = j.at("Withdraw").get<std::vector<UnbondingPurse>>();
  }
}
}  // namespace Casper