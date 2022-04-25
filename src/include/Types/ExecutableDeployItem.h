#pragma once

#include <optional>

#include "Base.h"
#include "Types/ModuleBytes.h"
#include "Types/StoredContractByHash.h"
#include "Types/StoredContractByName.h"
#include "Types/StoredVersionedContractByHash.h"
#include "Types/StoredVersionedContractByName.h"
#include "Types/TransferDeployItem.h"
#include "magic_enum/magic_enum.hpp"
#include "nlohmann/json.hpp"

namespace Casper {
/// Represents possible variants of an executable deploy.
struct ExecutableDeployItem {
  std::optional<ModuleBytes> module_bytes = std::nullopt;
  std::optional<StoredContractByHash> stored_contract_by_hash = std::nullopt;
  std::optional<StoredContractByName> stored_contract_by_name = std::nullopt;
  std::optional<StoredVersionedContractByHash>
      stored_versioned_contract_by_hash = std::nullopt;
  std::optional<StoredVersionedContractByName>
      stored_versioned_contract_by_name = std::nullopt;
  std::optional<TransferDeployItem> transfer = std::nullopt;

  ExecutableDeployItem() {}

  ExecutableDeployItem(ModuleBytes module_bytes) : module_bytes(module_bytes) {}

  ExecutableDeployItem(StoredContractByHash stored_contract_by_hash)
      : stored_contract_by_hash(stored_contract_by_hash) {}

  ExecutableDeployItem(StoredContractByName stored_contract_by_name)
      : stored_contract_by_name(stored_contract_by_name) {}

  ExecutableDeployItem(
      StoredVersionedContractByHash stored_versioned_contract_by_hash)
      : stored_versioned_contract_by_hash(stored_versioned_contract_by_hash) {}

  ExecutableDeployItem(
      StoredVersionedContractByName stored_versioned_contract_by_name)
      : stored_versioned_contract_by_name(stored_versioned_contract_by_name) {}

  ExecutableDeployItem(TransferDeployItem transfer) : transfer(transfer) {}
};

/**
 * @brief Construct a JSON object from a ExecutableDeployItem object.
 *
 * @param j JSON object to construct.
 * @param p ExecutableDeployItem object to construct from.
 */
inline void to_json(nlohmann::json& j, const ExecutableDeployItem& p) {
  if (p.module_bytes.has_value()) {
    j["ModuleBytes"] = p.module_bytes.value();
  } else if (p.stored_contract_by_hash.has_value()) {
    j["StoredContractByHash"] = p.stored_contract_by_hash.value();
  } else if (p.stored_contract_by_name.has_value()) {
    j["StoredContractByName"] = p.stored_contract_by_name.value();
  } else if (p.stored_versioned_contract_by_hash.has_value()) {
    j["StoredVersionedContractByHash"] =
        p.stored_versioned_contract_by_hash.value();
  } else if (p.stored_versioned_contract_by_name.has_value()) {
    j["StoredVersionedContractByName"] =
        p.stored_versioned_contract_by_name.value();
  } else if (p.transfer.has_value()) {
    j["Transfer"] = p.transfer.value();
  }
  // TODOMS3: maybe return "null" if no value is set?
}

/**
 * @brief Construct a ExecutableDeployItem object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p ExecutableDeployItem object to construct.
 */
inline void from_json(const nlohmann::json& j, ExecutableDeployItem& p) {
  if (j.find("ModuleBytes") != j.end()) {
    p.module_bytes = j["ModuleBytes"].get<ModuleBytes>();
  } else if (j.find("StoredContractByHash") != j.end()) {
    p.stored_contract_by_hash =
        j["StoredContractByHash"].get<StoredContractByHash>();
  } else if (j.find("StoredContractByName") != j.end()) {
    p.stored_contract_by_name =
        j["StoredContractByName"].get<StoredContractByName>();
  } else if (j.find("StoredVersionedContractByHash") != j.end()) {
    p.stored_versioned_contract_by_hash =
        j["StoredVersionedContractByHash"].get<StoredVersionedContractByHash>();
  } else if (j.find("StoredVersionedContractByName") != j.end()) {
    p.stored_versioned_contract_by_name =
        j["StoredVersionedContractByName"].get<StoredVersionedContractByName>();
  } else if (j.find("Transfer") != j.end()) {
    p.transfer = j["Transfer"].get<TransferDeployItem>();
  } else {
    throw std::runtime_error("Invalid ExecutableDeployItem");
  }
  // TODOMS3: maybe not throw if no value is set?
}

}  // namespace Casper
