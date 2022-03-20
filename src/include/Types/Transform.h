#pragma once

#include <optional>
#include "Base.h"

// libs
#include "nlohmann/json.hpp"

// Types
#include "Definitions.h"
#include "Types/Bid.h"
#include "Types/CLValue.h"
#include "Types/DeployInfo.h"
#include "Types/EraInfo.h"
#include "Types/NamedKey.h"
#include "Types/Transfer.h"
#include "Types/UnbondingPurse.h"

namespace Casper {
struct Transform {
  std::optional<std::string> Identity = std::nullopt;
  std::optional<CLValue> WriteCLValue = std::nullopt;
  std::optional<std::string> WriteAccount = std::nullopt;
  std::optional<std::string> WriteContractWasm = std::nullopt;
  std::optional<std::string> WriteContract = std::nullopt;
  std::optional<std::string> WriteContractPackage = std::nullopt;
  std::optional<DeployInfo> WriteDeployInfo = std::nullopt;
  std::optional<EraInfo> WriteEraInfo = std::nullopt;
  std::optional<Transfer> WriteTransfer = std::nullopt;
  std::optional<Bid> WriteBid = std::nullopt;
  std::optional<std::vector<UnbondingPurse>> WriteWithdraw = std::nullopt;
  std::optional<int32_t> AddInt32 = std::nullopt;
  std::optional<uint64_t> AddUInt64 = std::nullopt;
  std::optional<big_int> AddUInt128 = std::nullopt;
  std::optional<big_int> AddUInt256 = std::nullopt;
  std::optional<big_int> AddUInt512 = std::nullopt;
  std::optional<std::vector<NamedKey>> AddKeys = std::nullopt;
  std::optional<std::string> Failure = std::nullopt;
};

// to_json of Transform
inline void to_json(nlohmann::json& j, const Transform& p) {
  if (p.WriteCLValue.has_value()) {
    j["WriteCLValue"] = p.WriteCLValue.value();
  }

  if (p.WriteAccount.has_value()) {
    j["WriteAccount"] = p.WriteAccount.value();
  }

  if (p.WriteContractWasm.has_value()) {
    j["WriteContractWasm"] = p.WriteContractWasm.value();
  }

  if (p.WriteContract.has_value()) {
    j["WriteContract"] = p.WriteContract.value();
  }

  if (p.WriteContractPackage.has_value()) {
    j["WriteContractPackage"] = p.WriteContractPackage.value();
  }

  if (p.WriteDeployInfo.has_value()) {
    j["WriteDeployInfo"] = p.WriteDeployInfo.value();
  }

  if (p.WriteEraInfo.has_value()) {
    j["WriteEraInfo"] = p.WriteEraInfo.value();
  }

  if (p.WriteTransfer.has_value()) {
    j["WriteTransfer"] = p.WriteTransfer.value();
  }

  if (p.WriteBid.has_value()) {
    j["WriteBid"] = p.WriteBid.value();
  }

  if (p.WriteWithdraw.has_value()) {
    j["WriteWithdraw"] = p.WriteWithdraw.value();
  }

  if (p.AddInt32.has_value()) {
    j["AddInt32"] = p.AddInt32.value();
  }

  if (p.AddUInt64.has_value()) {
    j["AddUInt64"] = p.AddUInt64.value();
  }

  if (p.AddUInt128.has_value()) {
    j["AddUInt128"] = p.AddUInt128.value().toString();
  }

  if (p.AddUInt256.has_value()) {
    j["AddUInt256"] = p.AddUInt256.value().toString();
  }

  if (p.AddUInt512.has_value()) {
    j["AddUInt512"] = p.AddUInt512.value().toString();
  }

  if (p.AddKeys.has_value()) {
    j["AddKeys"] = p.AddKeys.value();
  }

  if (p.Failure.has_value()) {
    j["Failure"] = p.Failure.value();
  }
}

// from_json of Transform
inline void from_json(const nlohmann::json& j, Transform& p) {
  if (j.find("WriteCLValue") != j.end()) {
    p.WriteCLValue = j["WriteCLValue"].get<CLValue>();
  }

  if (j.find("WriteAccount") != j.end()) {
    p.WriteAccount = j.at("WriteAccount").get<std::string>();
  }

  if (j.find("WriteContractWasm") != j.end()) {
    p.WriteContractWasm = j.at("WriteContractWasm").get<std::string>();
  }

  if (j.find("WriteContract") != j.end()) {
    p.WriteContract = j.at("WriteContract").get<std::string>();
  }

  if (j.find("WriteContractPackage") != j.end()) {
    p.WriteContractPackage = j.at("WriteContractPackage").get<std::string>();
  }

  if (j.find("WriteDeployInfo") != j.end()) {
    p.WriteDeployInfo = j.at("WriteDeployInfo").get<DeployInfo>();
  }

  if (j.find("WriteEraInfo") != j.end()) {
    p.WriteEraInfo = j.at("WriteEraInfo").get<EraInfo>();
  }

  if (j.find("WriteTransfer") != j.end()) {
    p.WriteTransfer = j.at("WriteTransfer").get<Transfer>();
  }

  if (j.find("WriteBid") != j.end()) {
    p.WriteBid = j.at("WriteBid").get<Bid>();
  }

  if (j.find("WriteWithdraw") != j.end()) {
    p.WriteWithdraw = j.at("WriteWithdraw").get<std::vector<UnbondingPurse>>();
  }

  if (j.find("AddInt32") != j.end()) {
    p.AddInt32 = j.at("AddInt32").get<int32_t>();
  }

  if (j.find("AddUInt64") != j.end()) {
    p.AddUInt64 = j.at("AddUInt64").get<uint64_t>();
  }

  if (j.find("AddUInt128") != j.end()) {
    p.AddUInt128 = j.at("AddUInt128").get<std::string>();
  }

  if (j.find("AddUInt256") != j.end()) {
    p.AddUInt256 = j.at("AddUInt256").get<std::string>();
  }

  if (j.find("AddUInt512") != j.end()) {
    p.AddUInt512 = j.at("AddUInt512").get<std::string>();
  }

  if (j.find("AddKeys") != j.end()) {
    p.AddKeys = j.at("AddKeys").get<std::vector<NamedKey>>();
  }

  if (j.find("Failure") != j.end()) {
    p.Failure = j.at("Failure").get<std::string>();
  }
}
}  // namespace Casper
