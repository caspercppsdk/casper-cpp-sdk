#pragma once

#include <optional>

#include "Base.h"
#include "Types/ModuleBytes.h"
#include "magic_enum/magic_enum.hpp"
#include "nlohmann/json.hpp"
namespace Casper {

struct StoredContractByHashDeployItem {
  // TODO:
};

/**
 * @brief Construct a JSON object from a StoredContractByHashDeployItem object.
 *
 * @param j JSON object to construct.
 * @param p StoredContractByHashDeployItem object to construct from.
 */
inline void to_json(nlohmann::json& j,
                    const StoredContractByHashDeployItem& p) {
  // TODO:
}

/**
 * @brief Construct a StoredContractByHashDeployItem object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p StoredContractByHashDeployItem object to construct.
 */
inline void from_json(const nlohmann::json& j,
                      StoredContractByHashDeployItem& p) {
  // TODO: fill here
}

struct StoredContractByNameDeployItem {
  // TODO:
};

/**
 * @brief Construct a JSON object from a StoredContractByNameDeployItem object.
 *
 * @param j JSON object to construct.
 * @param p StoredContractByNameDeployItem object to construct from.
 */
inline void to_json(nlohmann::json& j,
                    const StoredContractByNameDeployItem& p) {
  // TODO:
}

/**
 * @brief Construct a StoredContractByNameDeployItem object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p StoredContractByNameDeployItem object to construct.
 */
inline void from_json(const nlohmann::json& j,
                      StoredContractByNameDeployItem& p) {
  // TODO:
}

struct StoredVersionedContractByHashDeployItem {
  // TODO:
};

/**
 * @brief Construct a JSON object from a StoredVersionedContractByHashDeployItem
 * object.
 *
 * @param j JSON object to construct.
 * @param p StoredVersionedContractByHashDeployItem object to construct from.
 */
inline void to_json(nlohmann::json& j,
                    const StoredVersionedContractByHashDeployItem& p) {
  // TODO:
}

/**
 * @brief Construct a StoredVersionedContractByHashDeployItem object from a JSON
 * object.
 *
 * @param j JSON object to construct the object from.
 * @param p StoredVersionedContractByHashDeployItem object to construct.
 */
inline void from_json(const nlohmann::json& j,
                      StoredVersionedContractByHashDeployItem& p) {
  // TODO:
}

struct StoredVersionedContractByNameDeployItem {
  // TODO:
};

/**
 * @brief Construct a JSON object from a StoredVersionedContractByNameDeployItem
 * object.
 *
 * @param j JSON object to construct.
 * @param p StoredVersionedContractByNameDeployItem object to construct from.
 */
inline void to_json(nlohmann::json& j,
                    const StoredVersionedContractByNameDeployItem& p) {
  // TODO:
}

/**
 * @brief Construct a StoredVersionedContractByNameDeployItem object from a JSON
 * object.
 *
 * @param j JSON object to construct the object from.
 * @param p StoredVersionedContractByNameDeployItem object to construct.
 */
inline void from_json(const nlohmann::json& j,
                      StoredVersionedContractByNameDeployItem& p) {
  // TODO:
}

struct TransferDeployItem {
  // TODO:
};

/**
 * @brief Construct a JSON object from a TransferDeployItem
 * object.
 *
 * @param j JSON object to construct.
 * @param p TransferDeployItem object to construct from.
 */
inline void to_json(nlohmann::json& j, const TransferDeployItem& p) {
  // TODO:
}

/**
 * @brief Construct a TransferDeployItem object from a JSON
 * object.
 *
 * @param j JSON object to construct the object from.
 * @param p TransferDeployItem object to construct.
 */
inline void from_json(const nlohmann::json& j, TransferDeployItem& p) {
  // TODO:
}

struct ExecutableDeployItem {
  std::optional<ModuleBytes> module_bytes = std::nullopt;
  std::optional<StoredContractByHashDeployItem> stored_contract_by_hash =
      std::nullopt;
  std::optional<StoredContractByNameDeployItem> stored_contract_by_name =
      std::nullopt;
  std::optional<StoredVersionedContractByHashDeployItem>
      stored_versioned_contract_by_hash = std::nullopt;
  std::optional<StoredVersionedContractByNameDeployItem>
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
  // TODO:
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
