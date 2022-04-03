#pragma once

#include "Base.h"
#include "Types/NamedArg.h"
#include "Utils/CryptoUtil.h"
#include "cryptopp/secblock.h"
#include "nlohmann/json.hpp"

namespace Casper {

struct ModuleBytes {
  // TODOMS3: [JsonConverter(typeof(HexBytesConverter))]
  CryptoPP::SecByteBlock module_bytes;
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
  j["module_bytes"] = CryptoUtil::hexEncode(p.module_bytes);
  j["args"] = p.args;
}

/**
 * @brief Construct a ModuleBytes object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p ModuleBytes object to construct.
 */

inline void from_json(const nlohmann::json& j, ModuleBytes& p) {
  std::string bytesString = j["module_bytes"].get<std::string>();
  p.module_bytes = CryptoUtil::hexDecode(bytesString);

  j.at("args").get_to(p.args);
}

}  // namespace Casper