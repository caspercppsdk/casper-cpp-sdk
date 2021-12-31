#pragma once

#include "RpcResult.h"
#include "Types/Peer.h"
#include "Types/BlockInfo.h"

/**
 * @brief Result for the "info_get_status" rpc call.
 *
 */
namespace Casper {
  struct GetStatusInfoResult : public RpcResult {
  public:
    /**
     * @brief Construct a new GetStatusInfoResult object.
     *
     */
    GetStatusInfoResult() {}

    std::string api_version;
    std::string chainspec_name;
    std::string starting_state_root_hash;
    std::vector<Peer> peerList;
    BlockInfo last_added_block_info;
    std::string our_public_signing_key;
    std::string round_length;
    std::string next_upgrade;
    std::string build_version;
    std::string uptime;
  };

  /**
   * @brief Construct a JSON object from a GetStatusInfoResult object.
   *
   * @param j JSON object to construct.
   * @param p GetStatusInfoResult Result object to construct from.
   */
  inline void to_json(nlohmann::json& j, const GetStatusInfoResult& p) {
    j = nlohmann::json{{"api_version", p.api_version}};
    j["chainspec_name"] = p.chainspec_name;
    j["starting_state_root_hash"] = p.starting_state_root_hash;
    j["peerList"] = p.peerList;
    j["last_added_block_info"] = p.last_added_block_info;
    j["our_public_signing_key"] = p.our_public_signing_key;
    j["round_length"] = p.round_length;
    j["next_upgrade"] = p.next_upgrade;
    j["build_version"] = p.build_version;
    j["uptime"] = p.uptime;
  }

  /**
   * @brief Construct a GetStatusInfoResult object from a JSON object.
   *
   * @param j JSON object to construct the object from.
   * @param p GetStatusInfoResult object to construct.
   */
  inline void from_json(const nlohmann::json& j, GetStatusInfoResult& p) {
    j.at("api_version").get_to(p.api_version);

    j.at("chainspec_name").get_to(p.chainspec_name);

    j.at("starting_state_root_hash").get_to(p.starting_state_root_hash);

    if (j.at("peers").is_array()) {
        auto t = j.at("peers").begin();

        while (t != j.at("peers").end()) {
            p.peerList.push_back(Peer((*t).at("address"), (*t).at("node_id")));
            ++t;
        }
    }

    // Optional information needs to be checked against null value.
    if (!j.at("last_added_block_info").is_null())
      from_json(j.at("last_added_block_info"), p.last_added_block_info);

    if (!j.at("our_public_signing_key").is_null())
      j.at("our_public_signing_key").get_to(p.our_public_signing_key);

    if (!j.at("round_length").is_null())
      j.at("round_length").get_to(p.round_length);

    if (!j.at("next_upgrade").is_null())
      j.at("next_upgrade").get_to(p.next_upgrade);

    j.at("build_version").get_to(p.build_version);

    j.at("uptime").get_to(p.uptime);
  }
}  // namespace Casper
