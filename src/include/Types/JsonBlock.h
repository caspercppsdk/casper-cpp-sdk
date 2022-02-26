#pragma once

#include "Base.h"
#include "Types/JsonBlockBody.h"
#include "Types/JsonBlockHeader.h"
#include "Types/JsonProof.h"
#include "nlohmann/json.hpp"

namespace Casper {

struct JsonBlock {
  std::string hash;
  JsonBlockHeader header;
  JsonBlockBody body;
  std::vector<JsonProof> proofs;

  JsonBlock() {}
};

/**
 * @brief Construct a JSON object from a JsonBlock object.
 *
 * @param j JSON object to construct.
 * @param p JsonBlock object to construct from.
 */
inline void to_json(nlohmann::json& j, const JsonBlock& p) {
  j = nlohmann::json{
      {"hash", p.hash},
      {"header", p.header},
      {"body", p.body},
      {"proofs", p.proofs},
  };
}

/**
 * @brief Construct a JsonBlock object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p JsonBlock object to construct.
 */
inline void from_json(const nlohmann::json& j, JsonBlock& p) {
  j.at("hash").get_to(p.hash);

  from_json(j.at("header"), p.header);

  from_json(j.at("body"), p.body);

  if (j.at("proofs").is_array()) {
    auto t = j.at("proofs").begin();

    while (t != j.at("proofs").end()) {
      JsonProof proof;
      from_json(*t, proof);
      p.proofs.push_back(proof);
      ++t;
    }
  }
}

}  // namespace Casper