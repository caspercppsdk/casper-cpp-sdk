#pragma once

#include <optional>

#include "Base.h"
#include "Types/NamedArg.h"
#include "nlohmann/json.hpp"

namespace Casper {

/// Stored versioned contract referenced by its [`ContractPackageHash`], entry
/// point and an instance of [`RuntimeArgs`].
struct StoredVersionedContractByHash {
  /// Contract package hash.
  std::string hash;
  /// An optional version of the contract to call. It will default to the
  /// highest enabled version if no value is specified.
  std::optional<uint32_t> version = std::nullopt;
  /// Entry point name.
  std::string entry_point;
  /// Runtime arguments.
  std::vector<NamedArg> args;

  StoredVersionedContractByHash() {}

  StoredVersionedContractByHash(const std::string& hash, const uint32_t version,
                                const std::string& entry_point,
                                const std::vector<NamedArg>& args)
      : hash(hash), version(version), entry_point(entry_point), args(args) {}

  StoredVersionedContractByHash(const std::string& hash,
                                const std::string& entry_point,
                                const std::vector<NamedArg>& args = {})
      : hash(hash), entry_point(entry_point), args(args) {}

  StoredVersionedContractByHash(const std::string& hash, const uint32_t version,
                                const std::string& entry_point)
      : hash(hash), version(version), entry_point(entry_point) {}
};

/**
 * @brief Construct a JSON object from a StoredVersionedContractByHash object.
 *
 * @param j JSON object to construct.
 * @param p StoredVersionedContractByHash object to construct from.
 */

inline void to_json(nlohmann::json& j, const StoredVersionedContractByHash& p) {
  j = nlohmann::json{
      {"hash", p.hash},
      {"entry_point", p.entry_point},
      {"args", p.args},
  };

  if (p.version.has_value()) {
    j["version"] = p.version.value();
  }
}

/**
 * @brief Construct a StoredVersionedContractByHash object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p StoredVersionedContractByHash object to construct.
 */

inline void from_json(const nlohmann::json& j,
                      StoredVersionedContractByHash& p) {
  j.at("hash").get_to(p.hash);
  p.entry_point = j.at("entry_point").get<std::string>();
  j.at("args").get_to(p.args);

  if (j.find("version") != j.end()) {
    p.version = j.at("version").get<uint32_t>();
  }
}

}  // namespace Casper