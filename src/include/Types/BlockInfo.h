#pragma once

#include <string>
#include "nlohmann/json.hpp"

namespace Casper {

    struct BlockInfo {
        BlockInfo (std::string creator_, ulong era_id_, std::string hash_, ulong height_, std::string state_root_hash_, std::string timestamp_)
        : creator(creator_), era_id(era_id_), hash(hash_), height(height_), state_root_hash(state_root_hash_), timestamp(timestamp_) {}

        BlockInfo() {}

        std::string creator;
        ulong era_id;
        std::string hash;
        ulong height;
        std::string state_root_hash;
        std::string timestamp;
    };

    /**
     * @brief Construct a JSON object from a BlockInfo object.
     *
     * @param j JSON object to construct.
     * @param p BlockInfo object to construct from.
     */
    inline void to_json(nlohmann::json& j, const BlockInfo& p) {
        j = nlohmann::json{
            {"creator", p.creator},
            {"era_id", p.era_id},
            {"hash", p.hash},
            {"height", p.height},
            {"state_root_hash", p.state_root_hash},
            {"timestamp", p.timestamp}
        };
    }

    /**
     * @brief Construct a BlockInfo object from a JSON object.
     *
     * @param j JSON object to construct the object from.
     * @param p BlockInfo object to construct.
     */
    inline void from_json(const nlohmann::json& j, BlockInfo& p) {
        j.at("creator").get_to(p.creator);
        j.at("era_id").get_to(p.era_id);
        j.at("hash").get_to(p.hash);
        j.at("height").get_to(p.height);
        j.at("state_root_hash").get_to(p.state_root_hash);
        j.at("timestamp").get_to(p.timestamp);
    }

} // namespace Casper