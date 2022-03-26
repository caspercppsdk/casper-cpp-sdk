#pragma once
#include "Base.h"
#include "Types/EntryPoint.h"
#include "Types/NamedKey.h"
#include "nlohmann/json.hpp"

namespace Casper {
// Information, entry points and named keys belonging to a Contract

/**
 * @brief Structure that contains information about a contract such as its entry
 * points and named keys
 *
 */
struct Contract {
  /// <summary>
  /// Key of the ContractPackage object
  /// </summary>
  std::string contract_package_hash;

  /// <summary>
  /// Key of the ContractWasm object
  /// </summary>
  std::string contract_wasm_hash;

  /// <summary>
  ///  List of NamedKeys in the contract
  /// </summary>
  std::vector<NamedKey> named_keys;

  /// <summary>
  /// List of entry points or methods in the contract
  /// </summary>
  std::vector<EntryPoint> entry_points;

  /// <summary>
  /// The protocol version when the contract was deployed
  /// </summary>
  std::string protocol_version;

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
