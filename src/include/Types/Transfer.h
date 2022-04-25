#pragma once

#include <optional>

#include "Base.h"
#include "Types/URef.h"
#include "nlohmann/json.hpp"

namespace Casper {

/// <summary>
/// Represents a transfer from one purse to another
/// </summary>
struct Transfer {
  /// <summary>
  /// Deploy that created the transfer
  /// </summary>
  std::string deploy_hash;

  /// <summary>
  /// Account hash from which transfer was executed
  /// </summary>
  AccountHashKey from;

  /// <summary>
  /// Account to which funds are transferred
  /// </summary>
  std::optional<AccountHashKey> to = std::nullopt;

  /// <summary>
  /// Source purse
  /// </summary>
  URef source;

  /// <summary>
  /// Target purse
  /// </summary>
  URef target;

  /// <summary>
  /// Transfer amount
  /// </summary>
  uint512_t amount;

  /// <summary>
  /// Gas
  /// </summary>
  uint512_t gas;

  /// <summary>
  /// User-defined id
  /// </summary>
  std::optional<uint64_t> id = std::nullopt;

  Transfer() {}
};

/**
 * @brief Construct a JSON object from a Transfer object.
 *
 * @param j JSON object to construct.
 * @param p Transfer object to construct from.
 */

inline void to_json(nlohmann::json& j, const Transfer& p) {
  j = nlohmann::json{{"deploy_hash", p.deploy_hash}, {"from", p.from},
                     {"source", p.source},           {"target", p.target},
                     {"amount", p.amount},           {"gas", p.gas}};

  if (p.id.has_value()) {
    j["id"] = p.id.value();
  }

  if (p.to.has_value()) {
    j["to"] = p.to.value();
  }
}

/**
 * @brief Construct a Transfer object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p Transfer object to construct.
 */

inline void from_json(const nlohmann::json& j, Transfer& p) {
  j.at("deploy_hash").get_to(p.deploy_hash);
  j.at("from").get_to(p.from);
  j.at("source").get_to(p.source);
  j.at("target").get_to(p.target);
  j.at("amount").get_to(p.amount);
  j.at("gas").get_to(p.gas);

  if (j.count("id") != 0 && !j.at("id").is_null()) {
    p.id = j.at("id").get<uint64_t>();
  }
  if (j.count("to") != 0 && !j.at("to").is_null()) {
    p.to = j.at("to").get<std::string>();
  }
}

}  // namespace Casper