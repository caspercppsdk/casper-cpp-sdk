#pragma once

#include "Base.h"
#include "Types/AccessRights.h"
#include "Types/GlobalStateKey.h"
#include "Utils/CEP57Checksum.h"
#include "Utils/CryptoUtil.h"
#include "Utils/StringUtil.h"
// Crypto
#include <cryptopp/secblock.h>

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

  static std::string byteToStringWithAccessRights(CBytes bytes);

  std::string byteToString(CBytes bytes, AccessRights rights);

  URef(CBytes bytes);

  URef(CBytes rawBytes, AccessRights accessRights);

  CBytes GetBytes();

  std::string ToString() const;

  bool operator<(const URef& other) const;

  bool operator==(const URef& other) const;

  bool operator!=(const URef& other) const;

 protected:
  CBytes _GetRawBytesFromKey(std::string key) const;
};

/**
 * @brief Construct a JSON object from a URef object.
 *
 * @param j JSON object to construct.
 * @param p URef object to construct from.
 */

inline void to_json(nlohmann::json& j, const URef& p) {
  j = static_cast<GlobalStateKey>(p);
  // j.update(p.access_rights);
}

/**
 * @brief Construct a URef object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p URef object to construct.
 */

inline void from_json(const nlohmann::json& j, URef& p) {
  std::string value = j.get<std::string>();
  p.key_identifier = KeyIdentifier::URef;
  p.key = value;

  if (!StringUtil::startsWith(value, "uref-")) {
    throw std::runtime_error("Invalid URef format");
  }

  auto parts = StringUtil::splitString(value.substr(5), "-");

  if (parts.size() != 2) {
    throw std::runtime_error(
        "A URef object must end with an access rights suffix.");
  }

  if (parts[0].length() != 64) {
    throw std::runtime_error("A URef object must contain a 32 byte value.");
  }

  if (parts[1].length() != 3) {
    throw std::runtime_error(
        "A URef object must contain a 3 digit access "
        "rights suffix.");
  }

  try {
    p.raw_bytes = CEP57Checksum::Decode(parts[0]);
  } catch (std::exception& e) {
    throw std::runtime_error("URef checksum mismatch.");
  }

  std::istringstream reader(parts[1]);
  unsigned int val;
  reader >> val;
  p.access_rights = (AccessRights)val;
}

}  // namespace Casper
