#pragma once

#include "Base.h"
#include "Types/PublicKey.h"
#include "Types/Signature.h"
#include "nlohmann/json.hpp"

namespace Casper {
/// <summary>
/// Signature and Public Key of the signer.
/// </summary>
struct DeployApproval {
  /// <summary>
  /// Signature of a deploy.
  /// </summary>
  Signature signature;

  /// <summary>
  /// Public Key that generates the signature.
  /// </summary>
  PublicKey signer;
};
}  // namespace Casper
