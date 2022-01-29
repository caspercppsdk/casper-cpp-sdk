#pragma once

#include <string>
#include <vector>

#include "Types/URef.h"

namespace Casper {
/// <summary>
/// A disabled version of a contract.
/// </summary>
struct DisabledVersion {
  /// <summary>
  /// Contract version.
  /// </summary>
  unsigned int contract_version;

  unsigned int protocol_version_major;
};

/// <summary>
/// Information related to an active version of a contract.
/// </summary>
struct ContractVersion {
  /// <summary>
  /// Hash for this version of the contract.
  /// </summary>
  std::string contract_hash;

  /// <summary>
  /// Contract version.
  /// </summary>
  unsigned int contract_version;

  unsigned int protocol_version_major;
};

/// <summary>
/// Groups associate a set of URefs with a label.
/// </summary>
struct Group {
  /// <summary>
  /// Group label
  /// </summary>
  std::string group;

  /// <summary>
  /// List of URefs associated with the group label.
  /// </summary>
  std::vector<URef> keys;
};

/// <summary>
/// Contract definition, metadata, and security container.
/// </summary>
struct ContractPackage {
  URef access_key;

  /// <summary>
  /// List of disabled versions of a contract.
  /// </summary>
  std::vector<DisabledVersion> disabled_versions;

  /// <summary>
  /// Groups associate a set of URefs with a label. Entry points on a contract
  /// can be given a list of labels they accept and the runtime will check that
  /// a URef from at least one of the allowed groups is present in the caller’s
  /// context before execution.
  /// </summary>
  std::vector<Group> groups;

  /// <summary>
  /// List of active versions of a contract.
  /// </summary>
  std::vector<ContractVersion> versions;
};
}  // namespace Casper
