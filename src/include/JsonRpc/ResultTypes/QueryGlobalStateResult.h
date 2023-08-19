#pragma once

#include "JsonRpc/ResultTypes/RpcResult.h"
#include "Types/StoredValue.h"
#include "Types/Block.h"

namespace Casper
{

/// Result for the "query_global_state" rpc call.
struct QueryGlobalStateResult : public RpcResult
{

    /// <summary>
    /// The block header if a Block hash was provided.
    /// </summary>
    std::optional<BlockHeader> block_header = std::nullopt;

    /// <summary>
    /// The stored value.
    /// </summary>
    StoredValue stored_value;

    /// <summary>
    /// The merkle proof.
    /// </summary>
    std::string merkle_proof;

    QueryGlobalStateResult() {}
};

/**
 * @brief Construct a JSON object from a QueryGlobalStateResult object.
 *
 * @param j JSON object to construct.
 * @param p GetStateRootHash Result object to construct from.
 */
inline void to_json(nlohmann::json& j, const QueryGlobalStateResult& p)
{
    j = static_cast<RpcResult>(p);

    if (p.block_header.has_value())
    {
        j["block_header"] = p.block_header.value();
    }
    j["stored_value"] = p.stored_value;
    j["merkle_proof"] = p.merkle_proof;
}

/**
 * @brief Construct a QueryGlobalStateResult object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p QueryGlobalStateResult object to construct.
 */
inline void from_json(const nlohmann::json& j, QueryGlobalStateResult& p)
{
    nlohmann::from_json(j, static_cast<RpcResult&>(p));

    if (j.find("block_header") != j.end() && !j.at("block_header").is_null())
    {
        p.block_header = j.at("block_header").get<BlockHeader>();
    }

    j.at("stored_value").get_to(p.stored_value);
    j.at("merkle_proof").get_to(p.merkle_proof);
}

} // namespace Casper
