#pragma once

#include "Base.h"
#include "Types/EraEnd.h"
#include "Types/Signature.h"
#include "nlohmann/json.hpp"

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
  std::optional<EraEnd> era_end;

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

  BlockHeader() {}
};

// to_json of BlockHeader
inline void to_json(nlohmann::json& j, const BlockHeader& p) {
  j = nlohmann::json{{"accumulated_seed", p.accumulated_seed},
                     {"body_hash", p.body_hash},
                     {"era_id", p.era_id},
                     {"height", p.height},
                     {"parent_hash", p.parent_hash},
                     {"protocol_version", p.protocol_version},
                     {"random_bit", p.random_bit},
                     {"state_root_hash", p.state_root_hash},
                     {"timestamp", p.timestamp}};

  if (p.era_end.has_value()) {
    j["era_end"] = p.era_end.value();
  }
}

// from_json of BlockHeader
inline void from_json(const nlohmann::json& j, BlockHeader& p) {
  j.at("accumulated_seed").get_to(p.accumulated_seed);
  j.at("body_hash").get_to(p.body_hash);

  if (j.find("era_end") != j.end() && !j.at("era_end").is_null()) {
    p.era_end = j.at("era_end").get<EraEnd>();
  }

  j.at("era_id").get_to(p.era_id);
  j.at("height").get_to(p.height);
  j.at("parent_hash").get_to(p.parent_hash);
  j.at("protocol_version").get_to(p.protocol_version);
  j.at("random_bit").get_to(p.random_bit);
  j.at("state_root_hash").get_to(p.state_root_hash);
  j.at("timestamp").get_to(p.timestamp);
}

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

  BlockBody() {}
};

// to_json  of BlockBody
inline void to_json(nlohmann::json& j, const BlockBody& p) {
  j = nlohmann::json{
      {"deploy_hashes", p.deploy_hashes},

      {"proposer", p.proposer},
      {"transfer_hashes", p.transfer_hashes},
  };
}

// from_json of BlockBody
inline void from_json(const nlohmann::json& j, BlockBody& p) {
  j.at("deploy_hashes").get_to(p.deploy_hashes);
  j.at("proposer").get_to(p.proposer);
  j.at("transfer_hashes").get_to(p.transfer_hashes);
}

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

  BlockProof() {}
};

// to_json  of BlockProof
inline void to_json(nlohmann::json& j, const BlockProof& p) {
  j = {{"public_key", p.public_key}, {"signature", p.signature}};
}

// from_json of BlockProof
inline void from_json(const nlohmann::json& j, BlockProof& p) {
  j.at("public_key").get_to(p.public_key);
  j.at("signature").get_to(p.signature);
}

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

  Block() {}
};

// to_json  of Block
inline void to_json(nlohmann::json& j, const Block& p) {
  j = {{"body", p.body},
       {"hash", p.hash},
       {"header", p.header},
       {"proofs", p.proofs}};
}

// from_json of Block
inline void from_json(const nlohmann::json& j, Block& p) {
  j.at("body").get_to(p.body);
  j.at("hash").get_to(p.hash);
  j.at("header").get_to(p.header);
  j.at("proofs").get_to(p.proofs);
}

}  // namespace Casper
