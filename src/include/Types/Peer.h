#pragma once
#include <string>
#include "nlohmann/json.hpp"

/**
 * @brief A node in the network.
 *
 */
struct Peer {
 public:
  /**
   * @brief Construct a new Peer object
   *
   */
  Peer() : node_id(), address() {}

  Peer(std::string address_, std::string node_id_) : address(address_), node_id(node_id_) {}

  /// The node ID as a string.
  std::string node_id;

  /// Concatenation of the Node IP address and the port as a string.
  std::string address;
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