#pragma once

#include <string>

#include "Types/AccessRights.h"
#include "Types/GlobalStateKey.h"
#include "Utils/CryptoUtil.h"
#include "Utils/StringUtil.h"
#include "cryptopp/cryptlib.h"
#include "cryptopp/hex.h"
#include "cryptopp/secblock.h"

namespace Casper {
/// <summary>
/// Unforgeable Reference. This key type is used for storing any type of value
/// except Account. Additionally, URefs used in contracts carry permission
/// information to prevent unauthorized usage of the value stored under the key.
/// </summary>
struct URef : public GlobalStateKey {
  AccessRights access_rights;

  URef(std::string value) : GlobalStateKey(value) {
    key_identifier = KeyIdentifier::UREF;

    if (!startsWith(value, "uref-")) {
      throw std::runtime_error("Invalid URef format");
    }

    auto parts = splitString(value.substr(5), "-");

    if (parts.size() != 2)
      throw std::runtime_error(
          "A URef object must end with an access rights suffix.");
    if (parts[0].length() !=
        64)  // TODO: check if this is correct, 32 may be the correct size
      throw std::runtime_error("A URef object must contain a 32 byte value.");
    if (parts[1].length() != 3)
      throw std::runtime_error(
          "A URef object must contain a 3 digit access "
          "rights suffix.");
    try {
      CEP57Checksum::Decode(parts[0]);
    } catch (std::exception& e) {
      throw "URef checksum mismatch.";
    }

    std::istringstream reader(parts[1]);
    unsigned int val;
    reader >> val;
    access_rights = (AccessRights)val;
  }

  std::string byteToStringWithAccessRights(SecByteBlock bytes) {
    std::string prefix = "uref-";
    std::string encoded;

    StringSource ss(bytes.data(), bytes.size() - 1, true,
                    new HexEncoder(new StringSink(encoded))  // HexEncoder
    );                                                       // StringSource

    std::string access_rights_str = std::to_string((uint8_t)bytes[32]);
    return prefix + encoded + "-" + access_rights_str;
  }

  std::string byteToString(SecByteBlock bytes, AccessRights rights) {
    std::string prefix = "uref-";
    std::string encoded;

    StringSource ss(bytes.data(), bytes.size(), true,
                    new HexEncoder(new StringSink(encoded))  // HexEncoder
    );                                                       // StringSource

    std::string access_rights_str = std::to_string((uint8_t)rights);
    return prefix + encoded + "-" + access_rights_str;
  }

  /// <summary>
  /// Creates an URef from a 33 bytes array. Last byte corresponds to the access
  /// rights.
  /// </summary>

  URef(SecByteBlock bytes) : URef(byteToStringWithAccessRights(bytes)) {}

  /// <summary>
  /// Creates an URef from a 32 bytes array and the access rights.
  /// </summary>
  URef(SecByteBlock rawBytes, AccessRights accessRights)
      : URef(byteToString(rawBytes, accessRights)) {}

  SecByteBlock GetBytes() {
    SecByteBlock returned_bytes(34);
    returned_bytes[0] = (uint8_t)key_identifier;

    std::copy(raw_bytes.begin(), raw_bytes.end(), returned_bytes.begin() + 1);
    returned_bytes[33] = (uint8_t)access_rights;

    return returned_bytes;
  }

  std::string ToString() {
    return "uref-" + CEP57Checksum::Encode(raw_bytes) + "-" +
           std::to_string((uint8_t)access_rights);
  }

 protected:
  SecByteBlock _GetRawBytesFromKey(std::string key) {
    key = key.substr(0, key.find_last_of('-'));
    return hexDecode(key.substr(key.find_last_of('-') + 1));
  }
};

}  // namespace Casper
