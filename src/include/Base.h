#pragma once

#include <optional>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include "wide-integer/uintwide_t.h"
#include <cryptopp/secblock.h>
#include <cryptopp/filters.h>  // CryptoPP::StringSink
#include <cryptopp/hex.h>      // CryptoPP::HexEncoder
#include "nlohmann/json.hpp"

using uint512_t = math::wide_integer::uint512_t;
using uint256_t = math::wide_integer::uint256_t;
using uint128_t = math::wide_integer::uint128_t;

inline bool iequals(const std::string& a, const std::string& b) {
  return std::equal(a.begin(), a.end(), b.begin(), b.end(),
                    [](char a, char b) { return tolower(a) == tolower(b); });
}

namespace Casper {
using CBytes = CryptoPP::SecByteBlock;
using CHexEncoder = CryptoPP::HexEncoder;
using CHexDecoder = CryptoPP::HexDecoder;
using CStringSink = CryptoPP::StringSink;
using CStringSource = CryptoPP::StringSource;

inline CBytes hexDecode(std::string hex) {
  CryptoPP::StringSource ss(hex, true, new CryptoPP::HexDecoder);
  CBytes decoded((size_t)ss.MaxRetrievable());
  ss.Get(decoded, decoded.size());
  return decoded;
}

inline std::string hexEncode(CBytes decoded) {
  std::string encoded;

  CryptoPP::StringSource ss(
      decoded, decoded.size(), true,
      new CryptoPP::HexEncoder(new CryptoPP::StringSink(encoded),
                               false)  // HexEncoder
  );
  return encoded;
}

/*
Numeric values consisting of 64 bits or less serialize in the two's complement
representation with little-endian byte order, and the appropriate number of
bytes for the bit-width.
*/
template <typename T>
inline T hexToInteger(const std::string& hex) {
  CBytes bytes = hexDecode(hex);
  T val = *(reinterpret_cast<T*>(bytes.data()));
  return val;
}

template <typename T>
inline std::string integerToHex(T val) {
  CBytes bytes(sizeof(T));
  memcpy(bytes.data(), &val, sizeof(T));
  return hexEncode(bytes);
}

inline void reverseHex(std::string& hex_input) {
  for (int i = 0; i < hex_input.length(); i += 2) {
    std::string byte_str = hex_input.substr(i, 2);
    std::reverse(byte_str.begin(), byte_str.end());
    hex_input.replace(i, 2, byte_str);
  }

  std::reverse(hex_input.begin(), hex_input.end());
}

inline uint128_t u128FromHex(std::string hex_str) {
  uint32_t len = hexToInteger<uint32_t>(hex_str.substr(0, 2));

  if (len < 1) {
    return uint128_t(0);
  }

  hex_str = hex_str.substr(2, len * 2);
  reverseHex(hex_str);
  hex_str = "0x" + hex_str;

  return uint128_t(hex_str.c_str());
}

inline std::string u128ToHex(uint128_t value) {
  if (value == 0) {
    // std::cout << "u128ToHex: value is 0" << std::endl;
    return "00";
  }

  std::stringstream ss;
  ss << std::hex << value;
  std::string u128_str;
  u128_str = ss.str();

  if (u128_str.length() % 2 != 0) {
    u128_str = "0" + u128_str;
  }

  //
  uint8_t bytes_length = u128_str.length() / 2;
  std::string bytes_length_str = integerToHex<uint8_t>(bytes_length);

  reverseHex(u128_str);
  // std::cout << "u128_str: " << u128_str << std::endl;

  // this string includes the length of the string and its hex representation
  std::string encoded_u128_str = bytes_length_str + u128_str;

  return encoded_u128_str;
}

inline std::string u128ToDec(uint128_t value) {
  std::stringstream ss;
  ss << value;
  std::string u128_str;
  u128_str = ss.str();

  return u128_str;
}

inline uint128_t u128FromDec(std::string dec_str) {
  return uint128_t(dec_str.c_str());
}

inline void to_json(nlohmann::json& j, const uint128_t& p) { j = u128ToDec(p); }

inline void from_json(const nlohmann::json& j, uint128_t& p) {
  p = u128FromDec(j.get<std::string>());
}

inline uint256_t u256FromHex(std::string hex_str) {
  uint32_t len = hexToInteger<uint32_t>(hex_str.substr(0, 2));

  if (len < 1) {
    return uint256_t(0);
  }

  hex_str = hex_str.substr(2, len * 2);
  reverseHex(hex_str);
  hex_str = "0x" + hex_str;

  return uint256_t(hex_str.c_str());
}

inline std::string u256ToHex(uint256_t value) {
  if (value == 0) {
    // std::cout << "u256ToHex: value is 0" << std::endl;
    return "00";
  }

  std::stringstream ss;
  ss << std::hex << value;
  std::string u256_str;
  u256_str = ss.str();

  // std::cout << "u256_str1: " << u256_str << std::endl;

  if (u256_str.length() % 2 != 0) {
    u256_str = "0" + u256_str;
  }

  // std::cout << "u256_str2: " << u256_str << std::endl;
  //
  uint8_t bytes_length = u256_str.length() / 2;
  std::string bytes_length_str = integerToHex<uint8_t>(bytes_length);

  // std::cout << "u256_str3: " << u256_str << std::endl;
  reverseHex(u256_str);

  // this string includes the length of the string and its hex representation
  std::string encoded_u256_str = bytes_length_str + u256_str;

  return encoded_u256_str;
}

inline std::string u256ToDec(uint256_t value) {
  std::stringstream ss;
  ss << value;
  std::string u256_str;
  u256_str = ss.str();
  return u256_str;
}

inline uint256_t u256FromDec(std::string dec_str) {
  return uint256_t(dec_str.c_str());
}

inline void to_json(nlohmann::json& j, const uint256_t& p) { j = u256ToDec(p); }

inline void from_json(const nlohmann::json& j, uint256_t& p) {
  p = u256FromDec(j.get<std::string>());
}

inline uint512_t u512FromHex(std::string hex_str) {
  uint32_t len = hexToInteger<uint32_t>(hex_str.substr(0, 2));

  if (len < 1) {
    return uint512_t(0);
  }

  hex_str = hex_str.substr(2, len * 2);
  reverseHex(hex_str);
  hex_str = "0x" + hex_str;

  return uint512_t(hex_str.c_str());
}

inline std::string u512ToHex(uint512_t value) {
  if (value == 0) {
    // std::cout << "u512ToHex: value is 0" << std::endl;
    return "00";
  }

  std::stringstream ss;
  ss << std::hex << value;
  std::string u512_str;
  u512_str = ss.str();

  if (u512_str.length() % 2 != 0) {
    u512_str = "0" + u512_str;
  }

  //
  uint8_t bytes_length = u512_str.length() / 2;
  std::string bytes_length_str = integerToHex<uint8_t>(bytes_length);

  // std::cout << "u512_str: " << u512_str << std::endl;
  reverseHex(u512_str);

  // this string includes the length of the string and its hex representation
  std::string encoded_u512_str = bytes_length_str + u512_str;

  return encoded_u512_str;
}

inline std::string u512ToDec(uint512_t value) {
  std::stringstream ss;
  ss << value;
  std::string u512_str;
  u512_str = ss.str();
  return u512_str;
}

inline uint512_t u512FromDec(std::string dec_str) {
  return uint512_t(dec_str.c_str());
}

inline void to_json(nlohmann::json& j, const uint512_t& p) { j = u512ToDec(p); }

inline void from_json(const nlohmann::json& j, uint512_t& p) {
  p = u512FromDec(j.get<std::string>());
}

}  // namespace Casper

namespace nlohmann {
template <>
struct adl_serializer<uint128_t> {
  static void to_json(json& j, const uint128_t& var) {
    ::Casper::to_json(j, var);
  }

  static void from_json(const json& j, uint128_t& var) {
    ::Casper::from_json(j, var);
  }
};

template <>
struct adl_serializer<uint256_t> {
  static void to_json(json& j, const uint256_t& var) {
    ::Casper::to_json(j, var);
  }

  static void from_json(const json& j, uint256_t& var) {
    ::Casper::from_json(j, var);
  }
};
template <>
struct adl_serializer<uint512_t> {
  static void to_json(json& j, const uint512_t& var) {
    ::Casper::to_json(j, var);
  }

  static void from_json(const json& j, uint512_t& var) {
    ::Casper::from_json(j, var);
  }
};
}  // namespace nlohmann
