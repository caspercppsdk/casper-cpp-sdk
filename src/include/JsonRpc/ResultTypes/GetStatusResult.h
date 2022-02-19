#pragma once

#include "RpcResult.h"
#include "Types/BlockInfo.h"
#include "Types/Peer.h"

/**
 * @brief Result for the "info_get_status" rpc call.
 *
 */
namespace Casper {
struct GetStatusResult : public RpcResult {
 public:
  /**
   * @brief Construct a new GetStatusResult  object.
   *
   */
  GetStatusResult() {}

  std::string chainspec_name;
  std::string starting_state_root_hash;
  // TODO: name should be "peers"
  std::vector<Peer> peers;

  std::optional<BlockInfo> last_added_block_info = std::nullopt;

  // TODO: Make PublicKey instead of std::string
  std::optional<std::string> our_public_signing_key = std::nullopt;

  // TODO: Make TimeDiff instead of std::string
  std::optional<std::string> round_length = std::nullopt;

  // make NextUpgrade instead of std::string
  std::optional<std::string> next_upgrade = std::nullopt;

  std::string build_version;

  // TODO: Make TimeDiff instead of std::string
  std::string uptime;
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

  if (j.count("last_added_block_info") != 0 &&
      !j.at("last_added_block_info").is_null()) {
    p.last_added_block_info = j.at("last_added_block_info").get<BlockInfo>();
  }

  /* Activate this after making our_public_signing_key PublicKey and remove the
  line below if (j.count("our_public_signing_key") != 0 &&
      !j.at("our_public_signing_key").is_null()) {
    p.our_public_signing_key = j.at("our_public_signing_key").get<PublicKey>();
  }
  */

  if (j.count("our_public_signing_key") != 0 &&
      !j.at("our_public_signing_key").is_null()) {
    j.at("our_public_signing_key").get_to(p.our_public_signing_key);
  }

  if (j.count("round_length") != 0 && !j.at("round_length").is_null()) {
    j.at("round_length").get_to(p.round_length);
  }

  if (j.count("next_upgrade") != 0 && !j.at("next_upgrade").is_null()) {
    j.at("next_upgrade").get_to(p.next_upgrade);
  }

  j.at("build_version").get_to(p.build_version);
  j.at("uptime").get_to(p.uptime);
}
}  // namespace Casper
