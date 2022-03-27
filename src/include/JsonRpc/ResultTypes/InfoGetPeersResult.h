#pragma once

#include <vector>

#include "RpcResult.h"
#include "Types/Peer.h"

namespace Casper {

/// Result for "info_get_peers" RPC response.
struct InfoGetPeersResult : public RpcResult {
  /// <summary>
  /// The node ID and network address of each connected peer.
  /// </summary>
  std::vector<Peer> peers;

  InfoGetPeersResult() {}
};

/**
 * @brief Construct a JSON object from a InfoGetPeersResult object.
 *
 * @param j JSON object to construct.
 * @param p InfoGetPeersResult Result object to construct from.
 */
inline void to_json(nlohmann::json& j, const InfoGetPeersResult& p) {
  j = static_cast<RpcResult>(p);
  j["peers"] = p.peers;
}

/**
 * @brief Construct a InfoGetPeersResult object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p InfoGetPeersResult object to construct.
 */
inline void from_json(const nlohmann::json& j, InfoGetPeersResult& p) {
  nlohmann::from_json(j, static_cast<RpcResult&>(p));
  j.at("peers").get_to(p.peers);
}

}  // namespace Casper
