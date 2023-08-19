#pragma once

#include "Base.h"
#include "JsonRpc/ResultTypes/RpcResult.h"
#include "Types/ChainspecRawBytes.h"

namespace Casper
{

/// Result for the "info_get_chainspec" rpc call.
struct GetChainspecResult : public RpcResult
{

    /// <summary>
    /// The chainspec file bytes.
    /// </summary>
    ChainspecRawBytes chainspec_bytes;

    GetChainspecResult() {}
};

/**
 * @brief Construct a JSON object from a GetChainspecResult object.
 *
 * @param j JSON object to construct.
 * @param p GetChainspecResult Result object to construct from.
 */
inline void to_json(nlohmann::json& j, const GetChainspecResult& p)
{
    j = static_cast<RpcResult>(p);
    j["chainspec_bytes"] = p.chainspec_bytes;
}

/**
 * @brief Construct a GetChainspecResult object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p GetChainspecResult object to construct.
 */
inline void from_json(const nlohmann::json& j, GetChainspecResult& p)
{
    nlohmann::from_json(j, static_cast<RpcResult&>(p));
    j.at("chainspec_bytes").get_to(p.chainspec_bytes);
}

} // namespace Casper
