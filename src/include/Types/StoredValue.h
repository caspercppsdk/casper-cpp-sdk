#pragma once
#include <optional>

#include "Base.h"
#include "Types/Account.h"
#include "Types/Bid.h"
#include "Types/CLValue.h"
#include "Types/Contract.h"
#include "Types/ContractPackage.h"
#include "Types/DeployInfo.h"
#include "Types/EraInfo.h"
#include "Types/Transfer.h"
#include "Types/UnbondingPurse.h"
#include "Utils/StringUtil.h"
#include "nlohmann/json.hpp"

/*
Example
{
  "api_version": "1.0.0",
  "stored_value": {
    "CLValue": {
      "bytes": "0b000000e280984d65646861e28099",
      "cl_type": "String"
    }
  }
}
*/
namespace Casper {
/// StoredValue represents all possible variants of values stored in Global
/// State.
struct StoredValue {
  /// Variant that stores [`CLValue`].
  std::optional<CLValue> cl_value = std::nullopt;
  /// Variant that stores [`Account`].
  std::optional<Account> account = std::nullopt;
  /// Variant that stores [`ContractWasm`].
  std::optional<std::string> contract_wasm = std::nullopt;
  /// Variant that stores [`Contract`].
  std::optional<Contract> contract = std::nullopt;
  /// Variant that stores [`ContractPackage`].
  std::optional<ContractPackage> contract_package = std::nullopt;
  /// Variant that stores [`Transfer`].
  std::optional<Transfer> transfer = std::nullopt;
  /// Variant that stores [`DeployInfo`].
  std::optional<DeployInfo> deploy_info = std::nullopt;
  /// Variant that stores [`EraInfo`].
  std::optional<EraInfo> era_info = std::nullopt;
  /// Variant that stores [`Bid`].
  std::optional<Bid> bid = std::nullopt;
  /// Variant that stores unbonding information.
  std::optional<std::vector<UnbondingPurse>> withdraw = std::nullopt;

  StoredValue() {}
  StoredValue(CLValue cl_value_) : cl_value(cl_value_) {}
  StoredValue(Account account_) : account(account_) {}
  StoredValue(std::string contract_wasm_) : contract_wasm(contract_wasm_) {}
  StoredValue(Contract contract_) : contract(contract_) {}
  StoredValue(ContractPackage contract_package_)
      : contract_package(contract_package_) {}
  StoredValue(Transfer transfer_) : transfer(transfer_) {}
  StoredValue(DeployInfo deploy_info_) : deploy_info(deploy_info_) {}
  StoredValue(EraInfo era_info_) : era_info(era_info_) {}
  StoredValue(Bid bid_) : bid(bid_) {}
  StoredValue(std::vector<UnbondingPurse> withdraw_) : withdraw(withdraw_) {}
};

/**
 * @brief Construct a JSON object from a StoredValue object.
 *
 * @param j JSON object to construct.
 * @param p StoredValue object to construct from.
 */
inline void to_json(nlohmann::json& j, const StoredValue& p) {
  j = nlohmann::json{};

  if (p.cl_value.has_value()) {
    j["CLValue"] = p.cl_value.value();
  } else if (p.account.has_value()) {
    j["Account"] = p.account.value();
  } else if (p.contract_wasm.has_value()) {
    j["ContractWasm"] = p.contract_wasm.value();
  } else if (p.contract.has_value()) {
    j["Contract"] = p.contract.value();
  } else if (p.contract_package.has_value()) {
    j["ContractPackage"] = p.contract_package.value();
  } else if (p.transfer.has_value()) {
    j["Transfer"] = p.transfer.value();
  } else if (p.deploy_info.has_value()) {
    j["DeployInfo"] = p.deploy_info.value();
  } else if (p.era_info.has_value()) {
    j["EraInfo"] = p.era_info.value();
  } else if (p.bid.has_value()) {
    j["Bid"] = p.bid.value();
  } else if (p.withdraw.has_value()) {
    j["Withdraw"] = p.withdraw.value();
  } else {
    j = {{"error", "STORED_VALUE_NOT_FOUND"}};
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
  } else if (j.count("Account") != 0) {
    p.account = j.at("Account").get<Account>();
  } else if (j.count("ContractWasm") != 0) {
    p.contract_wasm = j.at("ContractWasm").get<std::string>();
  } else if (j.count("Contract") != 0) {
    p.contract = j.at("Contract").get<Contract>();
  } else if (j.count("ContractPackage") != 0) {
    p.contract_package = j.at("ContractPackage").get<ContractPackage>();
  } else if (j.count("Transfer") != 0) {
    p.transfer = j.at("Transfer").get<Transfer>();
  } else if (j.count("DeployInfo") != 0) {
    p.deploy_info = j.at("DeployInfo").get<DeployInfo>();
  } else if (j.count("EraInfo") != 0) {
    p.era_info = j.at("EraInfo").get<EraInfo>();
  } else if (j.count("Bid") != 0) {
    p.bid = j.at("Bid").get<Bid>();
  } else if (j.count("Withdraw") != 0) {
    p.withdraw = j.at("Withdraw").get<std::vector<UnbondingPurse>>();
  } else {
    throw std::runtime_error("Unknown type of StoredValue");
  }
}

}  // namespace Casper