#pragma once

#include "JsonRpc/ResultTypes/RpcResult.h"
#include "Types/StoredValue.h"

/**
 * @brief Result for the "state_get_dictionary_item" rpc call.
 *
 */
namespace Casper {
struct GetDictionaryItemResult : public RpcResult {
 public:
  /**
   * @brief Construct a new GetDictionaryItemResult object.
   *
   */
  GetDictionaryItemResult(std::string dictionary_key_,
                          StoredValue stored_value_,
                          std::string merkle_proof_)
      : dictionary_key(dictionary_key_),
        stored_value(stored_value_),
        merkle_proof(merkle_proof_) {}

  GetDictionaryItemResult() {}

  std::string dictionary_key;
  StoredValue stored_value;
  std::string merkle_proof;
};

/**
 * @brief Construct a JSON object from a GetDictionaryItemResult object.
 *
 * @param j JSON object to construct.
 * @param p GetDictionaryItemResult object to construct from.
 */
inline void to_json(nlohmann::json& j, const GetDictionaryItemResult& p) {
  j = static_cast<RpcResult>(p);
  j["dictionary_key"] = p.dictionary_key;
  j["stored_value"] = p.stored_value;
  j["merkle_proof"] = p.merkle_proof;
}

/**
 * @brief Construct a GetDictionaryItemResult object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p GetDictionaryItemResult object to construct.
 */
inline void from_json(const nlohmann::json& j, GetDictionaryItemResult& p) {
  nlohmann::from_json(j, static_cast<RpcResult&>(p));
  j.at("dictionary_key").get_to(p.dictionary_key);
  j.at("stored_value").get_to(p.stored_value);
  j.at("merkle_proof").get_to(p.merkle_proof);
}
}  // namespace Casper
