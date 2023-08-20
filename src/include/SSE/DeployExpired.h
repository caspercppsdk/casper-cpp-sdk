#pragma once

#include "Base.h"
#include "nlohmann/json.hpp"

namespace Casper
{

/// <summary>
/// A deploy that has expired before being processed.
/// </summary>
struct DeployExpired
{
    DeployExpired() = default;

    /// <summary>
    /// The hash of the expired deploy.
    /// </summary>
    std::string deploy_hash;
};

inline void to_json(nlohmann::json& j, const DeployExpired& p)
{
    j = {{"deploy_hash", p.deploy_hash}};
}

inline void from_json(const nlohmann::json& j, DeployExpired& p)
{
    j.at("deploy_hash").get_to(p.deploy_hash);
}

} // namespace Casper
