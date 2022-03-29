#pragma once

#include "nlohmann/json.hpp"

namespace Casper {
/// <summary>
/// Information about the next protocol upgrade.
/// </summary>
struct NextUpgrade {
  /// <summary>
  /// Era Id when the next upgrade will be activated.
  /// According to rpc schema, it can be also a Timestamp
  /// </summary>
  uint64_t activation_point;

  /// <summary>
  /// The protocol version of the next upgrade
  /// </summary>
  std::string protocol_version;

  NextUpgrade() {}
};

/**
 * @brief Construct a JSON object from a NextUpgrade object.
 *
 * @param j JSON object to construct.
 * @param p NextUpgrade object to construct from.
 */
inline void to_json(nlohmann::json& j, const NextUpgrade& p) {
  j = nlohmann::json{{"activation_point", p.activation_point},
                     {"protocol_version", p.protocol_version}};
}

/**
 * @brief Construct a NextUpgrade object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p NextUpgrade object to construct.
 */
inline void from_json(const nlohmann::json& j, NextUpgrade& p) {
  j.at("activation_point").get_to(p.activation_point);
  j.at("protocol_version").get_to(p.protocol_version);
}

}  // namespace Casper