#pragma once

#include "Base.h"
#include "Types/NamedArg.h"
#include "nlohmann/json.hpp"

namespace Casper {

/// A native transfer which does not contain or reference a WASM code.
struct TransferDeployItem {
  /// Runtime arguments.
  std::vector<NamedArg> args;

  TransferDeployItem() {}

  TransferDeployItem(big_int amount, AccountHashKey targetAccountHash,
                     big_int id = -1) {
    std::cout << "TransferDeployItem::TransferDeployItem()" << std::endl;
    args.push_back(NamedArg("amount", CLValue::U512(amount)));
    std::cout << "after amount" << std::endl;
    args.push_back(
        NamedArg("target", CLValue::ByteArray(targetAccountHash.raw_bytes)));
    std::cout << "after target" << std::endl;
    if (id == -1) {
      std::cout << "id == -1" << std::endl;
      args.push_back(
          NamedArg("id", CLValue::OptionNone(CLType(CLTypeEnum::U64))));

    } else {
      uint64_t u64_id = id.toLongLong();
      std::cout << "u64_id: " << u64_id << std::endl;
      CLValue cl64 = CLValue::U64(u64_id);
      CLValue cl(CLValue::Option(cl64));

      // nlohmann::json j;
      // to_json(j, cl);
      // std::cout << "cl(u64): " << j.dump(2) << std::endl;

      args.push_back(NamedArg("id", cl));
    }

    nlohmann::json j;
    to_json(j, args[2]);
    std::cout << "args[2]: " << j.dump(2) << std::endl;

    std::cout << "transfer deploy end" << std::endl;
    //
  }
};

/**
 * @brief Construct a JSON object from a TransferDeployItem object.
 *
 * @param j JSON object to construct.
 * @param p TransferDeployItem object to construct from.
 */

inline void to_json(nlohmann::json& j, const TransferDeployItem& p) {
  j["args"] = p.args;
}

/**
 * @brief Construct a TransferDeployItem object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p TransferDeployItem object to construct.
 */

inline void from_json(const nlohmann::json& j, TransferDeployItem& p) {
  j.at("args").get_to(p.args);
}

}  // namespace Casper