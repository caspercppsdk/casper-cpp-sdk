#include "Types/URef.h"
#include <sstream>

#include "Utils/CEP57Checksum.h"
#include "Utils/CryptoUtil.h"
#include "Utils/StringUtil.h"

namespace Casper {

URef::URef() {}

URef::URef(std::string value) : GlobalStateKey::GlobalStateKey(value) {
  key_identifier = KeyIdentifier::URef;
  if (!StringUtil::startsWith(value, "uref-")) {
    throw std::runtime_error("Invalid URef format");
  }

  auto parts = StringUtil::splitString(value.substr(5), "-");

  if (parts.size() != 2)
    throw std::runtime_error(
        "A URef object must end with an access rights suffix.");
  if (parts[0].length() != 64)
    throw std::runtime_error("A URef object must contain a 32 byte value.");
  if (parts[1].length() != 3)
    throw std::runtime_error(
        "A URef object must contain a 3 digit access "
        "rights suffix.");

  try {
    raw_bytes = CEP57Checksum::Decode(parts[0]);
  } catch (std::exception& e) {
    throw std::runtime_error("URef Invalid Checksum.");
  }

  std::istringstream reader(parts[1]);
  unsigned int val;
  reader >> val;
  access_rights = (AccessRights)val;
}

std::string URef::byteToStringWithAccessRights(CBytes bytes) {
  std::string prefix = "uref-";
  std::string encoded;

  CryptoPP::StringSource ss(
      bytes.data(), bytes.size() - 1, true,
      new CryptoPP::HexEncoder(new CryptoPP::StringSink(encoded))  // HexEncoder
  );  // StringSource
  std::string access_rights_str = std::to_string((uint8_t)bytes[32]);
  if (access_rights_str.length() == 1) {
    access_rights_str = "00" + access_rights_str;
  } else if (access_rights_str.length() == 2) {
    access_rights_str = "0" + access_rights_str;
  }
  return prefix + encoded + "-" + access_rights_str;
}

std::string URef::byteToString(CBytes bytes, AccessRights rights) {
  std::string prefix = "uref-";
  std::string encoded;

  CryptoPP::StringSource ss(
      bytes.data(), bytes.size(), true,
      new CryptoPP::HexEncoder(new CryptoPP::StringSink(encoded))  // HexEncoder
  );  // StringSource

  std::string access_rights_str = std::to_string((uint8_t)rights);
  return prefix + encoded + "-" + access_rights_str;
}

/// <summary>
/// Creates an URef from a 33 bytes array. Last byte corresponds to the access
/// rights.
/// </summary>

URef::URef(CBytes bytes) : URef::URef(byteToStringWithAccessRights(bytes)) {}

/// <summary>
/// Creates an URef from a 32 bytes array and the access rights.
/// </summary>
URef::URef(CBytes rawBytes, AccessRights accessRights)
    : URef::URef(byteToString(rawBytes, accessRights)) {}

CBytes URef::GetBytes() {
  CBytes returned_bytes(34);
  returned_bytes[0] = (uint8_t)key_identifier;

  std::copy(raw_bytes.begin(), raw_bytes.end(), returned_bytes.begin() + 1);
  returned_bytes[33] = (uint8_t)access_rights;

  return returned_bytes;
}

std::string URef::ToString() const {
  std::string access_rights_str = std::to_string((uint8_t)access_rights);
  if (access_rights_str.length() == 1)
    access_rights_str = "00" + access_rights_str;
  else if (access_rights_str.length() == 2)
    access_rights_str = "0" + access_rights_str;

  return "uref-" + CEP57Checksum::Encode(_GetRawBytesFromKey(key)) + "-" +
         access_rights_str;
}

CBytes URef::_GetRawBytesFromKey(std::string key) const {
  std::string new_key = key.substr(0, key.find_last_of('-'));
  return CryptoUtil::hexDecode(new_key.substr(new_key.find_last_of('-') + 1));
}

bool URef::operator<(const URef& other) const {
  return ToString() < other.ToString();
}

bool URef::operator==(const URef& other) const {
  return ToString() == other.ToString();
}

bool URef::operator!=(const URef& other) const {
  return ToString() != other.ToString();
}

}  // namespace Casper
