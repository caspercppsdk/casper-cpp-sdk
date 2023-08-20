#pragma once

#include <utility>

#include "Base.h"
#include "Types/PublicKey.h"
#include "Types/Signature.h"
#include "nlohmann/json.hpp"

namespace Casper
{
/// <summary>
/// Public Key and Signature of the signer.
/// </summary>
struct DeployApproval
{
    /// <summary>
    /// Public Key that generates the signature.
    /// </summary>
    PublicKey signer;

    /// <summary>
    /// Signature of a deploy.
    /// </summary>
    Signature signature;

    DeployApproval() = default;

    DeployApproval(PublicKey signer, Signature signature)
        : signer(std::move(signer))
        , signature(std::move(signature))
    {
    }
};

// to_json of DeployApproval
inline void to_json(nlohmann::json& j, const DeployApproval& p)
{
    j = nlohmann::json{{"signer", p.signer}, {"signature", p.signature}};
}

// from_json of DeployApproval
inline void from_json(const nlohmann::json& j, DeployApproval& p)
{
    j.at("signer").get_to(p.signer);
    j.at("signature").get_to(p.signature);
}

} // namespace Casper
