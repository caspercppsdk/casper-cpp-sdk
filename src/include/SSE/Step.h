#pragma once

#include "Base.h"
#include "Types/ExecutionEffect.h"
#include "nlohmann/json.hpp"

namespace Casper
{

/// <summary>
/// The journal of execution transforms from an Era.
/// </summary>
struct Step
{
    Step() = default;

    /// <summary>
    /// The era in which the change occurred.
    /// </summary>
    uint64_t era_id;

    /// <summary>
    /// The effect of executing the deploy.
    /// </summary>
    ExecutionEffect execution_effect;
};

inline void to_json(nlohmann::json& j, const Step& p)
{
    j = {{"era_id", p.era_id}, {"execution_effect", p.execution_effect}};
}

inline void from_json(const nlohmann::json& j, Step& p)
{
    j.at("era_id").get_to(p.era_id);
    j.at("execution_effect").get_to(p.execution_effect);
}

} // namespace Casper
