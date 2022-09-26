#pragma once

#include "Base.h"
#include "Types/NamedArg.h"
#include "Utils/CryptoUtil.h"
#include "Types/CLConverter.h"
#include <cryptopp/secblock.h>
#include "nlohmann/json.hpp"

namespace Casper {
/// Executable specified as raw bytes that represent WASM code and an instance
/// of [`RuntimeArgs`].
struct ModuleBytes {
  /// Raw WASM module bytes with assumed "call" export as an entrypoint.
  CBytes module_bytes;
  /// Runtime arguments.
  std::vector<NamedArg> args;

  ModuleBytes() {}

  ModuleBytes(uint512_t amount) : module_bytes(0) {
    args.push_back(NamedArg("amount", CLValue::U512(amount)));
  }
};

/**
 * @brief Construct a JSON object from a ModuleBytes object.
 *
 * @param j JSON object to construct.
 * @param p ModuleBytes object to construct from.
 */

inline void to_json(nlohmann::json& j, const ModuleBytes& p) {
  j["module_bytes"] = hexEncode(p.module_bytes);
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
  p.module_bytes = hexDecode(bytesString);

  j.at("args").get_to(p.args);
}

}  // namespace Casper
