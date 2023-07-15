#pragma once

#include "Base.h"

namespace Casper
{
/// <summary>
/// The raw bytes of the chainspec.toml, genesis accounts.toml, and
/// global_state.toml files.
/// </summary>
struct ChainspecRawBytes
{
    // <summary>
    /// Hex-encoded raw bytes of the current chainspec.toml file.
    /// </summary>
    std::string chainspec_bytes;

    /// <summary>
    /// Hex-encoded raw bytes of the current genesis accounts.toml file.
    /// </summary>
    std::optional<std::string> maybe_genesis_accounts_bytes{std::nullopt};

    /// <summary>
    /// Hex-encoded raw bytes of the current global_state.toml file.
    /// </summary>
    std::optional<std::string> maybe_global_state_bytes{std::nullopt};

    ChainspecRawBytes()
    {
    }
};

/**
 * @brief Construct a JSON object from a ChainspecRawBytes object.
 *
 * @param j JSON object to construct.
 * @param p ChainspecRawBytes object to construct from.
 */
inline void to_json(nlohmann::json &j, const ChainspecRawBytes &p)
{
    j = nlohmann::json{{"chainspec_bytes", p.chainspec_bytes}};

    if (p.maybe_genesis_accounts_bytes.has_value())
    {
        j["maybe_genesis_accounts_bytes"] = p.maybe_genesis_accounts_bytes.value();
    }

    if (p.maybe_global_state_bytes.has_value())
    {
        j["maybe_global_state_bytes"] = p.maybe_global_state_bytes.value();
    }
}

/**
 * @brief Construct a ChainspecRawBytes object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p ChainspecRawBytes object to construct.
 */
inline void from_json(const nlohmann::json &j, ChainspecRawBytes &p)
{
    j.at("chainspec_bytes").get_to(p.chainspec_bytes);

    if (j.find("maybe_genesis_accounts_bytes") != j.end() && !j.at("maybe_genesis_accounts_bytes").is_null())
    {
        p.maybe_genesis_accounts_bytes = j.at("maybe_genesis_accounts_bytes").get<std::string>();
    }

    if (j.find("maybe_global_state_bytes") != j.end() && !j.at("maybe_global_state_bytes").is_null())
    {
        p.maybe_global_state_bytes = j.at("maybe_global_state_bytes").get<std::string>();
    }
}

} // namespace Casper
