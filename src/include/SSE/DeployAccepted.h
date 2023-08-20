#pragma once

#include "Base.h"
#include "Types/Deploy.h"
#include "nlohmann/json.hpp"

namespace Casper
{

/// <summary>
/// A new Deploy received for processing in the network.
/// </summary>
struct DeployAccepted : public Deploy
{
    DeployAccepted() = default;

    //
    // This is an alias of Deploy to be used in SSE.
    //
    DeployAccepted(std::string hash_, DeployHeader header_, ExecutableDeployItem payment_,
                   ExecutableDeployItem session_, std::vector<DeployApproval> approvals_)
        : Deploy(hash_, header_, payment_, session_, approvals_)
    {
    }
};

inline void to_json(nlohmann::json& j, const DeployAccepted& p)
{
    to_json(j, static_cast<Deploy>(p));
}

inline void from_json(const nlohmann::json& j, DeployAccepted& p)
{
    from_json(j, static_cast<Deploy&>(p));
}

} // namespace Casper
