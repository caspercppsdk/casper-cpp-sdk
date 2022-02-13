#pragma once

#include <string>

#include "Types/Definitions.h"
#include "Types/ExecutableDeployItem.h"
#include "Types/URef.h"
#include "nlohmann/json.hpp"

namespace Casper {

struct Transfer_EDI : public ExecutableDeployItemBase {
  Transfer_EDI(std::string args_) : ExecutableDeployItemBase(ExecutableDeployItemType::TRANSFER), args(args_) {}

  Transfer_EDI() : ExecutableDeployItemBase(ExecutableDeployItemType::TRANSFER) {}

  std::string args;
};

/**
 * @brief Construct a JSON object from a Transfer_EDI object.
 *
 * @param j JSON object to construct.
 * @param p Transfer_EDI object to construct from.
 */

inline void to_json(nlohmann::json& j, const Transfer_EDI& p) {
  j = static_cast<ExecutableDeployItemBase>(p);
  j["args"] = p.args;
}

/**
 * @brief Construct a Transfer_EDI object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p Transfer_EDI object to construct.
 */

inline void from_json(const nlohmann::json& j, Transfer_EDI& p) {
  nlohmann::from_json(j, static_cast<ExecutableDeployItemBase&>(p));
  j.at("args").get_to(p.args);
}

}  // namespace Casper