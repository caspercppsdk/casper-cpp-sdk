#pragma once

#include <vector>
#include "RpcResult.h"
#include "Types/Peer.h"

/**
 * @brief Result for the "info_get_peers" rpc call.
 *
 */
namespace Casper {
struct InfoGetPeersResult : public RpcResult {
 public:
  /**
   * @brief Construct a new InfoGetPeersResult object.
   *
   */
  InfoGetPeersResult() : peers() {}

  /// The peers as a vector of Peer objects.
  std::vector<Peer> peers;
};

/**
 * @brief Construct a JSON object from a InfoGetPeersResult object.
 *
 * @param j JSON object to construct.
 * @param p InfoGetPeersResult Result object to construct from.
 */
inline void to_json(nlohmann::json& j, const InfoGetPeersResult& p) {
  j = nlohmann::json{{"peers", p.peers}};
}

/**
 * @brief Construct a InfoGetPeersResult object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p InfoGetPeersResult object to construct.
 */
inline void from_json(const nlohmann::json& j, InfoGetPeersResult& p) {
  j.at("peers").get_to(p.peers);
}
}  // namespace Casper
