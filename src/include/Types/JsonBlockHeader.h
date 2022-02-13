#pragma once

#include <string>

#include "nlohmann/json.hpp"

namespace Casper {

struct JsonBlockHeader {
  JsonBlockHeader(std::string parent_hash_,
                  std::string state_root_hash_,
                  std::string body_hash_,
                  bool random_bit_,
                  std::string accumulated_seed_,
                  std::string era_end_,
                  std::string timestamp_,
                  uint64_t era_id_,
                  uint64_t height_,
                  std::string protocol_version_)
      : parent_hash(parent_hash_),
        state_root_hash(state_root_hash_),
        body_hash(body_hash_),
        random_bit(random_bit_),
        accumulated_seed(accumulated_seed_),
        era_end(era_end_),
        timestamp(timestamp_),
        era_id(era_id_),
        height(height_),
        protocol_version(protocol_version_) {}

  JsonBlockHeader() {}

  std::string parent_hash;
  std::string state_root_hash;
  std::string body_hash;
  bool random_bit;
  std::string accumulated_seed;
  std::string era_end;  // Optional.
  std::string timestamp;
  uint64_t era_id;
  uint64_t height;
  std::string protocol_version;
};

/**
 * @brief Construct a JSON object from a JsonBlockHeader object.
 *
 * @param j JSON object to construct.
 * @param p JsonBlockHeader object to construct from.
 */
inline void to_json(nlohmann::json& j, const JsonBlockHeader& p) {
  j = nlohmann::json{
      {"parent_hash", p.parent_hash},
      {"state_root_hash", p.state_root_hash},
      {"body_hash", p.body_hash},
      {"random_bit", p.random_bit},
      {"accumulated_seed", p.accumulated_seed},
      {"era_end", p.era_end},
      {"timestamp", p.timestamp},
      {"era_id", p.era_id},
      {"height", p.height},
      {"protocol_version", p.protocol_version},
  };
}

/**
 * @brief Construct a JsonBlockHeader object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p JsonBlockHeader object to construct.
 */
inline void from_json(const nlohmann::json& j, JsonBlockHeader& p) {
  j.at("parent_hash").get_to(p.parent_hash);
  j.at("state_root_hash").get_to(p.state_root_hash);
  j.at("body_hash").get_to(p.body_hash);
  j.at("random_bit").get_to(p.random_bit);
  j.at("accumulated_seed").get_to(p.accumulated_seed);

  if (!j.at("era_end").is_null()) j.at("era_end").get_to(p.era_end);

  j.at("timestamp").get_to(p.timestamp);
  j.at("era_id").get_to(p.era_id);
  j.at("height").get_to(p.height);
  j.at("protocol_version").get_to(p.protocol_version);
}

}  // namespace Casper