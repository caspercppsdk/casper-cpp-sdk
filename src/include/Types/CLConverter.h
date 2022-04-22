#pragma once

#include "Base.h"
#include "nlohmann/json.hpp"
#include "Types/Definitions.h"

#include "Types/GlobalStateKey.h"
#include "Types/PublicKey.h"
#include "Types/URef.h"

#include "rva/variant.hpp"
#include <tuple>

#include <unordered_map>
#include <optional>
#include "magic_enum/magic_enum.hpp"

namespace Casper {
uint64_t strToTimestamp(std::string str);

CryptoPP::SecByteBlock hexDecode(std::string hex);

std::string hexEncode(CryptoPP::SecByteBlock decoded);

// int-* types
/*
Numeric values consisting of 64 bits or less serialize in the two's complement
representation with little-endian byte order, and the appropriate number of
bytes for the bit-width.
*/
template <typename T>
T hexToInteger(const std::string& hex) {
  CryptoPP::SecByteBlock bytes = hexDecode(hex);
  T val = *(reinterpret_cast<T*>(bytes.data()));
  return val;
}

template <typename T>
std::string integerToHex(T val) {
  CryptoPP::SecByteBlock bytes(sizeof(T));
  memcpy(bytes.data(), &val, sizeof(T));
  return hexEncode(bytes);
}

// Big Integers
/*
Wider numeric values (i.e. U128, U256, U512) serialize as one byte given the
length of the next number (in bytes), followed by the two's complement
representation with little-endian byte order. The number of bytes should be
chosen as small as possible to represent the given number. This is done to
reduce the serialization size when small numbers are represented within a wide
data type.
*/
big_int hexToBigInteger(const std::string& hex);

std::uint8_t extract_one_byte(big_int& extract);

std::vector<std::uint8_t> to_bytes(const big_int& source);

std::string bigIntegerToHex(const big_int& val);

// Encoding && Decoding

bool boolDecode(const std::string& byte_str);

std::string boolEncode(bool val);

int32_t i32Decode(const std::string& byte_str);

std::string i32Encode(int32_t val);

int64_t i64Decode(const std::string& byte_str);

std::string i64Encode(int64_t val);

uint8_t u8Decode(const std::string& byte_str);

std::string u8Encode(uint8_t val);

uint32_t u32Decode(const std::string& byte_str);

std::string u32Encode(uint32_t val);

uint64_t u64Decode(const std::string& byte_str);

std::string u64Encode(uint64_t val);

big_int u128Decode(const std::string& byte_str);

std::string u128Encode(big_int val);

big_int u256Decode(const std::string& byte_str);

std::string u256Encode(big_int val);

big_int u512Decode(const std::string& byte_str);

std::string u512Encode(big_int val);

std::string stringDecode(const std::string& byte_str);

std::string stringEncode(const std::string& val);

GlobalStateKey urefDecode(const std::string& byte_str);

}  // namespace Casper