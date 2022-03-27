#pragma once

#include "JsonRpc/ResultTypes/RpcResult.h"
#include "Types/StoredValue.h"

namespace Casper {

/// Result for the "state_get_dictionary_item" rpc call.
struct GetDictionaryItemResult : public RpcResult {
  /// <summary>
  /// The key under which the value is stored.
  /// </summary>
  std::string dictionary_key;

  /// <summary>
  /// The stored value.
  /// </summary>
  StoredValue stored_value;

  /// <summary>
  /// The merkle proof.
  /// </summary>
  std::string merkle_proof;

  GetDictionaryItemResult() {}
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
