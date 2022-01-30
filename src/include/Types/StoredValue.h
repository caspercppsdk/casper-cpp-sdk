#pragma once
#include <optional>
#include <string>
#include <vector>

#include "Types/Contract.h"
#include "Types/Transfer.h"
#include "Types/Account.h"
#include "Types/StoredValueTypeBase.h"
#include "nlohmann/json.hpp"
#include "Types/UnbondingPurse.h"
#include "Types/Withdraw.h"

namespace Casper {

struct StoredValue {
  StoredValue() {}

  StoredValueTypeBase value;
};

/**
 * @brief Construct a JSON object from a StoredValue object.
 *
 * @param j JSON object to construct.
 * @param p StoredValue object to construct from.
 */
inline void to_json(nlohmann::json& j, const StoredValue& p) {
  j = nlohmann::json{};

  p.value.to_json(j);
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