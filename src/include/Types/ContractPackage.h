#pragma once

#include "Base.h"
#include "Types/URef.h"
#include "nlohmann/json.hpp"

namespace Casper {
/// <summary>
/// A disabled version of a contract.
/// </summary>
struct DisabledVersion {
  /// <summary>
  /// Contract version.
  /// </summary>
  uint8_t contract_version;

  /// <summary>
  /// Contract protocol major version.
  /// </summary>
  uint8_t protocol_version_major;

  DisabledVersion() {}
};

// from_json of DisabledVersion
inline void from_json(const nlohmann::json& j, DisabledVersion& p) {
  j.at("contract_version").get_to(p.contract_version);
  j.at("protocol_version_major").get_to(p.protocol_version_major);
}

// to_json of DisabledVersion
inline void to_json(nlohmann::json& j, const DisabledVersion& p) {
  j = {{"contract_version", p.contract_version},
       {"protocol_version_major", p.protocol_version_major}};
}

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
  uint8_t contract_version;

  /// <summary>
  /// Contract protocol major version.
  /// </summary>
  uint8_t protocol_version_major;

  ContractVersion() {}
};

// from_json of ContractVersion
inline void from_json(const nlohmann::json& j, ContractVersion& p) {
  j.at("contract_hash").get_to(p.contract_hash);
  j.at("contract_version").get_to(p.contract_version);
  j.at("protocol_version_major").get_to(p.protocol_version_major);
}

// to_json of ContractVersion
inline void to_json(nlohmann::json& j, const ContractVersion& p) {
  j = {{"contract_hash", p.contract_hash},
       {"contract_version", p.contract_version},
       {"protocol_version_major", p.protocol_version_major}};
}

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

  Group() {}
};

// from_json of Group
inline void from_json(const nlohmann::json& j, Group& p) {
  j.at("group").get_to(p.group);
  j.at("keys").get_to(p.keys);
}

// to_json of Group
inline void to_json(nlohmann::json& j, const Group& p) {
  j = {{"group", p.group}, {"keys", p.keys}};
}

/// <summary>
/// Contract definition, metadata, and security container.
/// </summary>
struct ContractPackage {
  URef access_key;

  /// <summary>
  /// List of active versions of a contract.
  /// </summary>
  std::vector<ContractVersion> versions;

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

  ContractPackage() {}
};

// from_json of ContractPackage
inline void from_json(const nlohmann::json& j, ContractPackage& p) {
  j.at("access_key").get_to(p.access_key);
  j.at("versions").get_to(p.versions);
  j.at("disabled_versions").get_to(p.disabled_versions);
  j.at("groups").get_to(p.groups);
}

// to_json of ContractPackage
inline void to_json(nlohmann::json& j, const ContractPackage& p) {
  j = {{"access_key", p.access_key},
       {"versions", p.versions},
       {"disabled_versions", p.disabled_versions},
       {"groups", p.groups}};
}

}  // namespace Casper
