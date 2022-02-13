#pragma once

#include "Base.h"

#include "Types/AccessRights.h"
#include "Types/GlobalStateKey.h"

// Crypto
#include "cryptopp/secblock.h"

// JSON
#include "nlohmann/json.hpp"

namespace Casper {
/// <summary>
/// Unforgeable Reference. This key type is used for storing any type of value
/// except Account. Additionally, URefs used in contracts carry permission
/// information to prevent unauthorized usage of the value stored under the key.
/// </summary>
struct URef : public GlobalStateKey {
  AccessRights access_rights;

  URef();

  URef(std::string value);

  std::string byteToStringWithAccessRights(SecByteBlock bytes);

  std::string byteToString(SecByteBlock bytes, AccessRights rights);

  URef(SecByteBlock bytes);

  URef(SecByteBlock rawBytes, AccessRights accessRights);

  SecByteBlock GetBytes();

  std::string ToString() const;

 protected:
  SecByteBlock _GetRawBytesFromKey(std::string key);
};

/**
 * @brief Construct a JSON object from a URef object.
 *
 * @param j JSON object to construct.
 * @param p URef object to construct from.
 */

inline void to_json(nlohmann::json& j, const URef& p) {
  nlohmann::to_json(j, static_cast<GlobalStateKey>(p));
  j.update({{"access_rights", p.access_rights}});
}

/**
 * @brief Construct a URef object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p URef object to construct.
 */

inline void from_json(const nlohmann::json& j, URef& p) {
  nlohmann::from_json(j, static_cast<GlobalStateKey&>(p));
  j.at("access_rights").get_to(p.access_rights);
}

}  // namespace Casper
