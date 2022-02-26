#pragma once

#include "Base.h"
#include "Types/PublicKey.h"
#include "Types/Signature.h"
#include "nlohmann/json.hpp"

namespace Casper {
/// <summary>
/// Public Key and Signature of the signer.
/// </summary>
struct DeployApproval {
  /// <summary>
  /// Public Key that generates the signature.
  /// </summary>
  // TODO: Make PublicKey instead of std::string
  std::string signer;

  /// <summary>
  /// Signature of a deploy.
  /// </summary>
  // TODO: [JsonConverter(typeof(Signature.SignatureConverter))]
  Signature signature;

  DeployApproval() {}
};

// to_json of DeployApproval
inline void to_json(nlohmann::json& j, const DeployApproval& p) {
  j = nlohmann::json{{"signer", p.signer}, {"signature", p.signature}};
}

// from_json of DeployApproval
inline void from_json(const nlohmann::json& j, DeployApproval& p) {
  // TODO: Make signer PublicKey instead of std::string
  j.at("signer").get_to(p.signer);
  j.at("signature").get_to(p.signature);
}

}  // namespace Casper
