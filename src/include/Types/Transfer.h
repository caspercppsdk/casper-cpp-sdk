#pragma once

#include <string>

#include "Types/Definitions.h"
#include "Types/StoredValueTypeBase.h"
#include "Types/URef.h"
#include "nlohmann/json.hpp"

namespace Casper {

struct Transfer : public StoredValueTypeBase {
  Transfer(big_int amount_, std::string deploy_hash_, std::string from_,
           big_int gas_, uint64_t id_, URef source_, URef target_,
           std::string to_)
      : StoredValueTypeBase(StoredValueType::TRANSFER),
        amount(amount_),
        deploy_hash(deploy_hash_),
        from(from_),
        gas(gas_),
        id(id_),
        source(source_),
        target(target_),
        to(to_) {}

  Transfer() : StoredValueTypeBase(StoredValueType::TRANSFER) {}

  big_int amount;
  std::string deploy_hash;
  std::string from;
  big_int gas;
  uint64_t id;
  URef source;
  URef target;
  std::string to;
};

/**
 * @brief Construct a JSON object from a Transfer object.
 *
 * @param j JSON object to construct.
 * @param p Transfer object to construct from.
 */

inline void to_json(nlohmann::json& j, const Transfer& p) {
  j = static_cast<StoredValueTypeBase>(p);
  j["amount"] = p.amount.toString();
  j["deploy_hash"] = p.deploy_hash;
  j["from"] = p.from;
  j["gas"] = p.gas.toString();
  j["id"] = p.id;
  j["source"] = p.source;
  j["target"] = p.target;
  j["to"] = p.to;
}

/**
 * @brief Construct a Transfer object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p Transfer object to construct.
 */

inline void from_json(const nlohmann::json& j, Transfer& p) {
  nlohmann::from_json(j, static_cast<StoredValueTypeBase&>(p));
  j.at("amount").get_to(p.amount);
  j.at("deploy_hash").get_to(p.deploy_hash);
  j.at("from").get_to(p.from);
  j.at("gas").get_to(p.gas);
  j.at("id").get_to(p.id);
  j.at("source").get_to(p.source);
  j.at("target").get_to(p.target);
  j.at("to").get_to(p.to);
}

}  // namespace Casper