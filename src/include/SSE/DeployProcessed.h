#pragma once

#include "Base.h"
#include "Types/ExecutionResult.h"
#include "nlohmann/json.hpp"

namespace Casper
{

/// <summary>
/// A Deploy that has been executed, committed and forms part of a Block.
/// </summary>
struct DeployProcessed
{
    DeployProcessed() = default;

    /// <summary>
    /// The deploy hash.
    /// </summary>
    std::string deploy_hash;

    /// <summary>
    /// The public key of the account that originates the Deploy.
    /// </summary>
    PublicKey account;

    /// <summary>
    /// The timestamp in which the Deploy was built.
    /// </summary>
    std::string timestamp;

    /// <summary>
    /// The time-to-live of the Deploy.
    /// </summary>
    std::string ttl;

    /// <summary>
    /// A list of hashes to other deploys that have to be run before this one.
    /// </summary>
    std::vector<std::string> dependencies;

    /// <summary>
    /// The hash of the block containing this Deploy.
    /// </summary>
    std::string block_hash;

    /// <summary>
    /// The result of executing a this Deploy.
    /// </summary>
    ExecutionResult execution_result;
};

inline void to_json(nlohmann::json& j, const DeployProcessed& p)
{
    j = {{"deploy_hash", p.deploy_hash},
         {"account", p.account},
         {"timestamp", p.timestamp},
         {"ttl", p.ttl},
         {"dependencies", p.dependencies},
         {"block_hash", p.block_hash},
         {"execution_result", p.execution_result}};
}

inline void from_json(const nlohmann::json& j, DeployProcessed& p)
{
    j.at("deploy_hash").get_to(p.deploy_hash);
    j.at("account").get_to(p.account);
    j.at("timestamp").get_to(p.timestamp);
    j.at("ttl").get_to(p.ttl);
    j.at("dependencies").get_to(p.dependencies);
    j.at("block_hash").get_to(p.block_hash);
    j.at("execution_result").get_to(p.execution_result);
}

} // namespace Casper
