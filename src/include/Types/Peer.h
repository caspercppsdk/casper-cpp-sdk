#pragma once
#include "Base.h"
#include "nlohmann/json.hpp"

namespace Casper {

/// <summary>
/// A node in the network.
/// </summary>
struct Peer {
  /// <summary>
  /// Node Id.
  /// </summary>
  std::string node_id;

  /// <summary>
  /// Concatenation of the Node IP address and the port as a string.
  /// </summary>
  std::string address;

  Peer() {}
};

/**
 * @brief Construct a JSON object from a Peer object.
 *
 * @param j JSON object to construct.
 * @param p Peer object to construct from.
 */
inline void to_json(nlohmann::json& j, const Peer& p) {
  j = nlohmann::json{{"node_id", p.node_id}, {"address", p.address}};
}

/**
 * @brief Construct a Peer object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p Peer object to construct.
 */
inline void from_json(const nlohmann::json& j, Peer& p) {
  j.at("node_id").get_to(p.node_id);
  j.at("address").get_to(p.address);
}

}  // namespace Casper