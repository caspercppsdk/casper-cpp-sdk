#pragma once

#include "RpcResult.h"
#include "Types/BlockInfo.h"
#include "Types/Definitions.h"
#include "Types/Peer.h"

namespace Casper {
/**
 * @brief Result for the "info_get_status" rpc call.
 *
 */
struct GetStatusResult : public RpcResult {
 public:
  /**
   * @brief Construct a new GetStatusResult  object.
   *
   */
  GetStatusResult() {}

  std::string chainspec_name;
  std::string starting_state_root_hash;
  std::vector<Peer> peers;
  std::optional<BlockInfo> last_added_block_info = std::nullopt;
  std::optional<std::string> our_public_signing_key = std::nullopt;
  std::optional<TimeDiff> round_length = std::nullopt;
  std::optional<std::string> next_upgrade = std::nullopt;
  std::string build_version;
  TimeDiff uptime = 0;
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
  p.chainspec_name = j.at("chainspec_name");
  p.starting_state_root_hash = j.at("starting_state_root_hash");

  j.at("peers").get_to(p.peers);

  if (j.contains("last_added_block_info") && !j.at("last_added_block_info").is_null())
    p.last_added_block_info = BlockInfo();
    j.at("last_added_block_info").get_to(p.last_added_block_info.value());

  if (j.contains("our_public_signing_key") && !j.at("our_public_signing_key").is_null())
    p.our_public_signing_key = j.at("our_public_signing_key");

  if (j.contains("round_length") && !j.at("round_length").is_null())
    p.round_length = string_to_timediff(j.at("round_length"));

  if (j.contains("next_upgrade") && !j.at("next_upgrade").is_null())
    p.next_upgrade = j.at("next_upgrade");

  p.build_version = j.at("build_version");

  p.uptime = string_to_timediff(j.at("uptime"));
}
}  // namespace Casper
