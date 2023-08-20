#pragma once

#include "Base.h"
#include "Types/Block.h"
#include "nlohmann/json.hpp"

namespace Casper
{

/// <summary>
/// A block that has been added to the linear chain and stored in the node.
/// </summary>
struct BlockAdded
{
    BlockAdded() = default;

    /// <summary>
    /// The block hash.
    /// </summary>
    std::string block_hash;

    /// <summary>
    /// The block data.
    /// </summary>
    Block block;
};

inline void to_json(nlohmann::json& j, const BlockAdded& p)
{
    j = {{"block_hash", p.block_hash}, {"block", p.block}};
}

inline void from_json(const nlohmann::json& j, BlockAdded& p)
{
    j.at("block_hash").get_to(p.block_hash);
    j.at("block").get_to(p.block);
}

} // namespace Casper
