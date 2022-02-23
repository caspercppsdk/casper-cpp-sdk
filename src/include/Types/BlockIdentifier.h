#pragma once

#include <string>

#include "nlohmann/json.hpp"

namespace Casper {

struct BlockIdentifier {
  BlockIdentifier(std::string hash_, uint64_t height_)
      : hash(hash_), height(height_) {}

  BlockIdentifier() {}

  std::string hash;
  uint64_t height;
};

/**
 * @brief Construct a JSON object from a BlockIdentifier object.
 *
 * @param j JSON object to construct.
 * @param p BlockIdentifier object to construct from.
 */
inline void to_json(nlohmann::json& j, const BlockIdentifier& p) {
  j = nlohmann::json{
      {"Hash", p.hash},
      {"Height", p.height},
  };
}

/**
 * @brief Construct a BlockIdentifier object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p BlockIdentifier object to construct.
 */
inline void from_json(const nlohmann::json& j, BlockIdentifier& p) {
  j.at("Hash").get_to(p.hash);
  j.at("Height").get_to(p.height);
}

}  // namespace Casper