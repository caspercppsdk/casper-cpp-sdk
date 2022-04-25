#pragma once

#include "RpcResult.h"
#include "Types/BlockInfo.h"
#include "Types/NextUpgrade.h"
#include "Types/Peer.h"

namespace Casper {

/// Result for "info_get_status" RPC response.
struct GetStatusResult : public RpcResult {
  /// <summary>
  /// The chainspec name.
  /// </summary>
  std::string chainspec_name;

  /// <summary>
  /// The state root hash used at the start of the current session.
  /// </summary>
  std::string starting_state_root_hash;

  /// <summary>
  /// The node ID and network address of each connected peer.
  /// </summary>
  std::vector<Peer> peers;

  /// <summary>
  /// The minimal info of the last block from the linear chain.
  /// </summary>
  std::optional<BlockInfo> last_added_block_info = std::nullopt;

  /// <summary>
  /// Our public signing key.
  /// </summary>
  std::optional<PublicKey> our_public_signing_key = std::nullopt;

  /// <summary>
  /// The next round length if this node is a validator.
  /// </summary>
  std::optional<std::string> round_length = std::nullopt;

  /// <summary>
  /// Information about the next scheduled upgrade.
  /// </summary>
  std::optional<NextUpgrade> next_upgrade = std::nullopt;

  /// <summary>
  /// The compiled node version.
  /// </summary>
  std::string build_version;

  /// <summary>
  /// Time that passed since the node has started.
  /// </summary>
  std::string uptime;

  GetStatusResult() {}
};

/**
 * @brief Construct a JSON object from a GetStatusResult  object.
 *
 * @param j JSON object to construct.
 * @param p GetStatusResult  Result object to construct from.
 */
inline void to_json(nlohmann::json& j, const GetStatusResult& p) {
  j = static_cast<RpcResult>(p);
  j["chainspec_name"] = p.chainspec_name;
  j["starting_state_root_hash"] = p.starting_state_root_hash;
  j["peers"] = p.peers;

  if (p.last_added_block_info.has_value()) {
    j["last_added_block_info"] = p.last_added_block_info.value();
  }

  if (p.our_public_signing_key.has_value()) {
    j["our_public_signing_key"] = p.our_public_signing_key.value();
  }
  if (p.round_length.has_value()) {
    j["round_length"] = p.round_length.value();
  }

  if (p.next_upgrade.has_value()) {
    j["next_upgrade"] = p.next_upgrade.value();
  }

  j["build_version"] = p.build_version;
  j["uptime"] = p.uptime;
}

/**
 * @brief Construct a GetStatusResult  object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p GetStatusResult  object to construct.
 */
inline void from_json(const nlohmann::json& j, GetStatusResult& p) {
  nlohmann::from_json(j, static_cast<RpcResult&>(p));

  j.at("chainspec_name").get_to(p.chainspec_name);
  j.at("starting_state_root_hash").get_to(p.starting_state_root_hash);
  j.at("peers").get_to(p.peers);

  if (j.find("last_added_block_info") != j.end() &&
      !j.at("last_added_block_info").is_null()) {
    p.last_added_block_info = j.at("last_added_block_info").get<BlockInfo>();
  }

  if (j.find("our_public_signing_key") != j.end() &&
      !j.at("our_public_signing_key").is_null()) {
    p.our_public_signing_key = j.at("our_public_signing_key").get<PublicKey>();
  }

  if (j.find("round_length") != j.end() && !j.at("round_length").is_null()) {
    p.round_length = j.at("round_length").get<std::string>();
  }

  if (j.find("next_upgrade") != j.end() && !j.at("next_upgrade").is_null()) {
    p.next_upgrade = j.at("next_upgrade").get<NextUpgrade>();
  }

  j.at("build_version").get_to(p.build_version);
  j.at("uptime").get_to(p.uptime);
}

}  // namespace Casper
