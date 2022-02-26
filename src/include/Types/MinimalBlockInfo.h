#pragma once

#include "Base.h"
#include "Types/PublicKey.h"

namespace Casper {
/// <summary>
/// Minimal info of a `Block`.
/// </summary>
struct MinimalBlockInfo {
  /// <summary>
  /// Block hash
  /// </summary>
  std::string hash;

  /// <summary>
  /// The block timestamp.
  /// </summary>
  std::string timestamp;

  /// <summary>
  /// The block era id.
  /// </summary>
  uint64_t era_id;

  /// <summary>
  /// Height of the block
  /// </summary>
  uint64_t height;

  /// <summary>
  /// The state root hash.
  /// </summary>
  std::string state_root_hash;

  /// <summary>
  /// Validator node's public key
  /// </summary>
  // TODO: Make PublicKey instead of std::string
  std::string creator;

  MinimalBlockInfo() {}
};
}  // namespace Casper
