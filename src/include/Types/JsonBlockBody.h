#pragma once

#include <string>
#include <vector>

#include "nlohmann/json.hpp"

namespace Casper {

struct JsonBlockBody {
  JsonBlockBody(std::vector<std::string> deploy_hashes_, std::string proposer_,
                std::vector<std::string> transfer_hashes_)
      : deploy_hashes(deploy_hashes_),
        proposer(proposer_),
        transfer_hashes(transfer_hashes_) {}

  JsonBlockBody() {}

  std::vector<std::string> deploy_hashes;
  std::string proposer;
  std::vector<std::string> transfer_hashes;
};

/**
 * @brief Construct a JSON object from a JsonBlockBody object.
 *
 * @param j JSON object to construct.
 * @param p JsonBlockBody object to construct from.
 */
inline void to_json(nlohmann::json& j, const JsonBlockBody& p) {
  j = nlohmann::json{
      {"deploy_hashes", p.deploy_hashes},
      {"proposer", p.proposer},
      {"transfer_hashes", p.transfer_hashes},
  };
}

/**
 * @brief Construct a JsonBlockBody object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p JsonBlockBody object to construct.
 */
inline void from_json(const nlohmann::json& j, JsonBlockBody& p) {
  if (j.at("deploy_hashes").is_array()) {
    auto t = j.at("deploy_hashes").begin();

    while (t != j.at("deploy_hashes").end()) {
      p.deploy_hashes.push_back(*t);
      ++t;
    }
  }

  j.at("proposer").get_to(p.proposer);

  if (j.at("transfer_hashes").is_array()) {
    auto t = j.at("transfer_hashes").begin();

    while (t != j.at("transfer_hashes").end()) {
      p.transfer_hashes.push_back(*t);
      ++t;
    }
  }
}

}  // namespace Casper