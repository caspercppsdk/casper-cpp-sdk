#pragma once
#include <string>
#include <vector>

#include "Types/EntryPoint.h"
#include "Types/NamedKey.h"
#include "nlohmann/json.hpp"

namespace Casper {
struct Contract {
  std::string contract_package_hash;
  std::string contract_wasm_hash;
  std::vector<NamedKey> named_keys;
  std::vector<EntryPoint> entry_points;
  std::string protocol_version;

  Contract(std::string contract_package_hash_,
           std::string contract_wasm_hash_,
           std::vector<NamedKey> named_keys_,
           std::vector<EntryPoint> entry_points_,
           std::string protocol_version_)
      : contract_package_hash(contract_package_hash_),
        contract_wasm_hash(contract_wasm_hash_),
        named_keys(named_keys_),
        entry_points(entry_points_),
        protocol_version(protocol_version_) {}

  Contract() {}
};

/**
 * @brief Construct a JSON object from a Contract object.
 *
 * @param j JSON object to construct.
 * @param p Contract object to construct from.
 */
inline void to_json(nlohmann::json& j, const Contract& p) {
  j = {{"contract_package_hash", p.contract_package_hash},
       {"contract_wasm_hash", p.contract_wasm_hash},
       {"named_keys", p.named_keys},
       {"entry_points", p.entry_points},
       {"protocol_version", p.protocol_version}};
}

/**
 * @brief Construct a Contract object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p Contract object to construct.
 */
inline void from_json(const nlohmann::json& j, Contract& p) {
  j.at("contract_package_hash").get_to(p.contract_package_hash);
  j.at("contract_wasm_hash").get_to(p.contract_wasm_hash);
  j.at("named_keys").get_to(p.named_keys);
  j.at("entry_points").get_to(p.entry_points);
  j.at("protocol_version").get_to(p.protocol_version);
}
}  // namespace Casper
