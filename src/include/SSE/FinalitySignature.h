#pragma once

#include "Base.h"
#include "Types/PublicKey.h"
#include "Types/Signature.h"
#include "nlohmann/json.hpp"

namespace Casper
{

/// <summary>
/// Server-Side event sent after each block finalization.
/// </summary>
struct FinalitySignature
{
    FinalitySignature() = default;

    /// <summary>
    /// The block hash
    /// </summary>
    std::string block_hash;

    /// <summary>
    /// The block era id.
    /// </summary>
    uint64_t era_id;

    /// <summary>
    /// Validator public key
    /// </summary>
    PublicKey public_key;

    /// <summary>
    /// Validator signature
    /// </summary>
    Signature signature;
};

inline void to_json(nlohmann::json& j, const FinalitySignature& p)
{
    j = {{"block_hash", p.block_hash}, {"era_id", p.era_id}, {"public_key", p.public_key}, {"signature", p.signature}};
}

inline void from_json(const nlohmann::json& j, FinalitySignature& p)
{
    j.at("block_hash").get_to(p.block_hash);
    j.at("era_id").get_to(p.era_id);
    j.at("public_key").get_to(p.public_key);
    j.at("signature").get_to(p.signature);
}

} // namespace Casper
