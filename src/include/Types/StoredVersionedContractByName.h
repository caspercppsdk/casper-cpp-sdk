#pragma once

#include <optional>
#include <utility>

#include "Base.h"
#include "Types/NamedArg.h"
#include "nlohmann/json.hpp"

namespace Casper
{
/// Stored versioned contract referenced by a named key existing in the signer's
/// account context, entry point and an instance of [`RuntimeArgs`].
struct StoredVersionedContractByName
{
    /// Named key.
    std::string name;
    /// An optional version of the contract to call. It will default to the
    /// highest enabled version if no value is specified.
    std::optional<uint32_t> version = std::nullopt;
    /// Entry point name.
    std::string entry_point;
    /// Runtime arguments.
    std::vector<NamedArg> args;

    StoredVersionedContractByName() = default;

    StoredVersionedContractByName(std::string name, const uint32_t version, std::string entry_point,
                                  const std::vector<NamedArg>& args)
        : name(std::move(name))
        , version(version)
        , entry_point(std::move(entry_point))
        , args(args)
    {
    }

    StoredVersionedContractByName(std::string name, std::string entry_point, const std::vector<NamedArg>& args = {})
        : name(std::move(name))
        , entry_point(std::move(entry_point))
        , args(args)
    {
    }

    StoredVersionedContractByName(std::string name, const uint32_t version, std::string entry_point)
        : name(std::move(name))
        , version(version)
        , entry_point(std::move(entry_point))
    {
    }
};

/**
 * @brief Construct a JSON object from a StoredVersionedContractByName object.
 *
 * @param j JSON object to construct.
 * @param p StoredVersionedContractByName object to construct from.
 */

inline void to_json(nlohmann::json& j, const StoredVersionedContractByName& p)
{
    j = nlohmann::json{
        {"name", p.name},
        {"entry_point", p.entry_point},
        {"args", p.args},
    };

    if (p.version.has_value())
    {
        j["version"] = p.version.value();
    }
}

/**
 * @brief Construct a StoredVersionedContractByName object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p StoredVersionedContractByName object to construct.
 */

inline void from_json(const nlohmann::json& j, StoredVersionedContractByName& p)
{
    j.at("name").get_to(p.name);
    p.entry_point = j.at("entry_point").get<std::string>();
    j.at("args").get_to(p.args);

    if (j.find("version") != j.end())
    {
        p.version = j.at("version").get<uint32_t>();
    }
}

} // namespace Casper