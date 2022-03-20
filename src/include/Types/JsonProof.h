#pragma once

#include "Base.h"
#include "nlohmann/json.hpp"

namespace Casper {

struct JsonProof {
  std::string public_key;
  std::string signature;

  JsonProof() {}
};

/**
 * @brief Construct a JSON object from a JsonProof object.
 *
 * @param j JSON object to construct.
 * @param p JsonProof object to construct from.
 */
inline void to_json(nlohmann::json& j, const JsonProof& p) {
  j = nlohmann::json{
      {"public_key", p.public_key},
      {"signature", p.signature},
  };
}

/**
 * @brief Construct a JsonProof object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p JsonProof object to construct.
 */
inline void from_json(const nlohmann::json& j, JsonProof& p) {
  j.at("public_key").get_to(p.public_key);
  j.at("signature").get_to(p.signature);
}

}  // namespace Casper