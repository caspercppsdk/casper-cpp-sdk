#pragma once
#include <string>
#include <vector>

#include "Types/EraEnd.h"
#include "Types/PublicKey.h"
#include "Types/Signature.h"

namespace Casper {
/// <summary>
/// A block header
/// </summary>
struct BlockHeader {
  /// <summary>
  /// Accumulated seed.
  /// </summary>
  std::string accumulated_seed;

  /// <summary>
  /// The body hash.
  /// </summary>
  std::string body_hash;

  /// <summary>
  /// The era end.
  /// </summary>
  EraEnd era_end;

  /// <summary>
  /// The block era id.
  /// </summary>
  uint64_t era_id;

  /// <summary>
  /// The block height.
  /// </summary>
  uint64_t height;

  /// <summary>
  /// The parent hash.
  /// </summary>
  std::string parent_hash;

  /// <summary>
  /// The protocol version.
  /// </summary>
  std::string protocol_version;

  /// <summary>
  /// Randomness bit.
  /// </summary>
  bool random_bit;

  /// <summary>
  /// The state root hash.
  /// </summary>
  std::string state_root_hash;

  /// <summary>
  /// The block timestamp.
  /// </summary>
  std::string timestamp;
};

/// <summary>
/// A block body
/// </summary>
struct BlockBody {
  /// <summary>
  /// List of Deploy hashes included in the block
  /// </summary>
  std::vector<std::string> deploy_hashes;

  /// <summary>
  /// Public key of the validator that proposed the block
  /// </summary>
  PublicKey proposer;

  /// <summary>
  /// List of Transfer hashes included in the block
  /// </summary>
  std::vector<std::string> transfer_hashes;
};

/// <summary>
/// Block's finality signature.
/// </summary>
struct BlockProof {
  /// <summary>
  /// Validator public key
  /// </summary>
  PublicKey public_key;

  /// <summary>
  /// Validator signature
  /// </summary>
  Signature signature;
};

/// <summary>
/// A block in the network
/// </summary>
struct Block {
  /// <summary>
  /// Block body
  /// </summary>
  BlockBody body;

  /// <summary>
  /// Block hash
  /// </summary>
  std::string hash;

  /// <summary>
  /// Block header
  /// </summary>
  BlockHeader header;

  /// <summary>
  /// List of proofs for this block.
  /// </summary>
  std::vector<BlockProof> proofs;
};
}  // namespace Casper
