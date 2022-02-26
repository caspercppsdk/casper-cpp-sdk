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
};

/**
 * @brief Construct a JSON object from a ExecutableDeployItem object.
 *
 * @param j JSON object to construct.
 * @param p ExecutableDeployItem object to construct from.
 */
inline void to_json(nlohmann::json& j, const ExecutableDeployItem& p) {
  
}

/**
 * @brief Construct a ExecutableDeployItem object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p ExecutableDeployItem object to construct.
 */
inline void from_json(const nlohmann::json& j, ExecutableDeployItem& p) {
  // TODO:
}

}  // namespace Casper
