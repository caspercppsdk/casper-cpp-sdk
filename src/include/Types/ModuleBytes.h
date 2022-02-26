#pragma once

#include "Base.h"
#include "Types/NamedArg.h"
#include "cryptopp/secblock.h"
#include "nlohmann/json.hpp"

namespace Casper {

struct ModuleBytes {
  std::vector<CryptoPP::SecByteBlock> module_bytes;
  std::vector<NamedArg> args;

  ModuleBytes() {}
};

/**
 * @brief Construct a JSON object from a ModuleBytes object.
 *
 * @param j JSON object to construct.
 * @param p ModuleBytes object to construct from.
 */

inline void to_json(nlohmann::json& j, const ModuleBytes& p) {
  j["module_bytes"] = p.module_bytes;
  j["args"] = p.args;
}

/**
 * @brief Construct a ModuleBytes object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p ModuleBytes object to construct.
 */

inline void from_json(const nlohmann::json& j, ModuleBytes& p) {
  j.at("module_bytes").get_to(p.module_bytes);
  j.at("args").get_to(p.args);
}

}  // namespace Casper