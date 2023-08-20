#pragma once

#include "Base.h"
#include "Types/PublicKey.h"
#include "nlohmann/json.hpp"

namespace Casper
{

/// <summary>
/// Generic representation of validator's fault in an era.
/// </summary>
struct Fault
{
    Fault() = default;

    /// <summary>
    /// The era in which the fault occurred.
    /// </summary>
    uint64_t era_id;

    /// <summary>
    /// The timestamp in which the fault occurred.
    /// </summary>
    std::string timestamp;

    /// <summary>
    /// Equivocator public key.
    /// </summary>
    PublicKey public_key;
};

inline void to_json(nlohmann::json& j, const Fault& p)
{
    j = {{"era_id", p.era_id}, {"timestamp", p.timestamp}, {"public_key", p.public_key}};
}

inline void from_json(const nlohmann::json& j, Fault& p)
{
    j.at("era_id").get_to(p.era_id);
    j.at("timestamp").get_to(p.timestamp);
    j.at("public_key").get_to(p.public_key);
}

} // namespace Casper
