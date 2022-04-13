#include "Types/CLTypeParsedConverter.h"

namespace Casper {

big_int hexToBigInteger(const std::string& hex) {
  if (hex.length() == 0 ||
      std::count(hex.begin(), hex.end(), '0') == hex.length()) {
    return big_int(0);
  }

  uint8_t bytes_length = 2 * hexToInteger<uint8_t>(hex.substr(0, 2));
  std::string bytes_str = hex.substr(hex.length() - bytes_length);
  std::reverse(bytes_str.begin(), bytes_str.end());
  big_int ret = 0;

  for (int i = 0; i < bytes_length / 2; i++) {
    std::string byte_str = bytes_str.substr(i * 2, 2);
    std::reverse(byte_str.begin(), byte_str.end());
    uint8_t byte_val = hexToInteger<uint8_t>(byte_str);
    ret *= 256;
    ret += byte_val;
  }

  return ret;
}

std::uint8_t extract_one_byte(big_int& extract) {
  // Will always return a value on the range [0, 255]
  auto intermediate = (extract % 256).toInt();

  std::uint8_t the_byte = static_cast<std::uint8_t>(intermediate);
  extract /= 256;
  return the_byte;
}

std::vector<std::uint8_t> to_bytes(const big_int& source) {
  std::vector<std::uint8_t> ret;
  // ret.reserve(#); //pick a decent amount to reserve.
  big_int curr = source;
  do {
    ret.push_back(extract_one_byte(curr));
  } while (curr != 0);

  return ret;
}

std::string bigIntegerToHex(const big_int& val) {
  if (val == 0) {
    return "00";
  }

  std::vector<std::uint8_t> bytes = to_bytes(val);

  CryptoPP::SecByteBlock byte_block(bytes.data(), bytes.size());
  std::string bytes_str = Casper::CEP57Checksum::Encode(byte_block);

  uint8_t bytes_length = bytes_str.size() / 2;
  std::string bytes_length_str = integerToHex<uint8_t>(bytes_length);
  return bytes_length_str + bytes_str;
}

// Encoding & Decoding

bool boolDecode(const std::string& byte_str) {
  //
  return hexToInteger<bool>(byte_str);
}

std::string boolEncode(bool val) {
  //
  return integerToHex<bool>(val);
}

int32_t i32Decode(const std::string& byte_str) {
  //
  return hexToInteger<int32_t>(byte_str);
}

std::string i32Encode(int32_t val) {
  //
  return integerToHex<int32_t>(val);
}

int64_t i64Decode(const std::string& byte_str) {
  //
  return hexToInteger<int64_t>(byte_str);
}

std::string i64Encode(int64_t val) {
  //
  return integerToHex<int64_t>(val);
}

uint8_t u8Decode(const std::string& byte_str) {
  //
  return hexToInteger<uint8_t>(byte_str);
}

std::string u8Encode(uint8_t val) {
  //
  return integerToHex<uint8_t>(val);
}

uint32_t u32Decode(const std::string& byte_str) {
  //
  return hexToInteger<uint32_t>(byte_str);
}

std::string u32Encode(uint32_t val) {
  //
  return integerToHex<uint32_t>(val);
}

uint64_t u64Decode(const std::string& byte_str) {
  //
  return hexToInteger<uint64_t>(byte_str);
}

std::string u64Encode(uint64_t val) {
  //
  return integerToHex<uint64_t>(val);
}

big_int u128Decode(const std::string& byte_str) {
  //
  return hexToBigInteger(byte_str);
}

std::string u128Encode(big_int val) {
  //
  return bigIntegerToHex(val);
}

big_int u256Decode(const std::string& byte_str) {
  //
  return hexToBigInteger(byte_str);
}

std::string u256Encode(big_int val) {
  //
  return bigIntegerToHex(val);
}

big_int u512Decode(const std::string& byte_str) {
  //
  return hexToBigInteger(byte_str);
}

std::string u512Encode(big_int val) {
  //
  return bigIntegerToHex(val);
}

// unit decode

// unit encode

std::string stringDecode(const std::string& byte_str) {
  return Casper::StringUtil::hexToString(byte_str);
}

std::string stringEncode(const std::string& val) {
  return Casper::StringUtil::stringToHex(val);
}

}  // namespace Casper
