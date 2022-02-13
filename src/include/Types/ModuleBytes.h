#pragma once

#include <string>

#include "Types/Definitions.h"
#include "Types/ExecutableDeployItem.h"
#include "Types/URef.h"
#include "nlohmann/json.hpp"

namespace Casper {

struct ModuleBytes : public ExecutableDeployItemBase {
  ModuleBytes(std::vector<byte> module_bytes_, std::string args_)
      : ExecutableDeployItemBase(ExecutableDeployItemType::MODULEBYTES), module_bytes(module_bytes_), args(args_) {}

  ModuleBytes() : ExecutableDeployItemBase(ExecutableDeployItemType::MODULEBYTES) {}

  std::vector<byte> module_bytes;
  std::string args;
};

/**
 * @brief Construct a JSON object from a ModuleBytes object.
 *
 * @param j JSON object to construct.
 * @param p ModuleBytes object to construct from.
 */

inline void to_json(nlohmann::json& j, const ModuleBytes& p) {
  j = static_cast<ExecutableDeployItemBase>(p);
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
  nlohmann::from_json(j, static_cast<ExecutableDeployItemBase&>(p));
  j.at("module_bytes").get_to(p.module_bytes);
  j.at("args").get_to(p.args);
}

}  // namespace Casper