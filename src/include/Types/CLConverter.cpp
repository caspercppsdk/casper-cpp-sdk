#include "Types/CLConverter.h"
#include "date/date.h"
#include <chrono>
namespace Casper {

uint64_t strToTimestamp(std::string str_date) {
  using namespace date;
  using namespace std;
  using namespace std::chrono;

  istringstream in{str_date};
  in.exceptions(ios::failbit);
  sys_time<milliseconds> tp;
  in >> parse("%FT%TZ", tp);
  cout << tp << " = " << tp.time_since_epoch() << '\n';
  return duration_cast<milliseconds>(tp.time_since_epoch()).count();
}

CryptoPP::SecByteBlock hexDecode(std::string hex) {
  CryptoPP::StringSource ss(hex, true, new CryptoPP::HexDecoder);
  CryptoPP::SecByteBlock decoded((size_t)ss.MaxRetrievable());
  ss.Get(decoded, decoded.size());
  return decoded;
}

std::string hexEncode(CryptoPP::SecByteBlock decoded) {
  std::string encoded;

  CryptoPP::StringSource ss(
      decoded, decoded.size(), true,
      new CryptoPP::HexEncoder(new CryptoPP::StringSink(encoded),
                               false)  // HexEncoder
  );
  return encoded;
}

big_int hexToBigInteger(std::string hex_input, int len) {
  std::stringstream ss;

  if (len == 512) {
    std::string hex_str = "0x" + hex_input;
    using uint512_t = math::wide_integer::uint512_t;
    const uint512_t a(hex_str.c_str());
    ss << a;
  } else if (len == 256) {
    std::string hex_str = "0x" + hex_input;
    using uint256_t = math::wide_integer::uint256_t;
    const uint256_t a(hex_str.c_str());
    ss << a;
  } else if (len == 128) {
    std::string hex_str = "0x" + hex_input;
    using uint128_t = math::wide_integer::uint128_t;
    const uint128_t a(hex_str.c_str());
    ss << a;
  } else {
    throw std::runtime_error("Invalid length in hexToBigInteger");
  }

  return big_int(ss.str());
  // TODO: Check if hex is 0 and activate below
  /*
    if (hex_input.length() == 0 ||
        std::count(hex_input.begin(), hex_input.end(), '0') ==
    hex_input.length()) { return big_int(0);
    }
  */

  /*
    std::cout << "hexToBigInteger: " << hex << std::endl;
    uint32_t bytes_length = 2 * hexToInteger<uint8_t>(hex.substr(0, 2));
    std::cout << "1: " << bytes_length << std::endl;
    std::string bytes_str = hex.substr(hex.length() - bytes_length);
    std::cout << "2: " << bytes_str << std::endl;
    std::reverse(bytes_str.begin(), bytes_str.end());
    std::cout << "3: " << bytes_str << std::endl;
    big_int ret = 0;
    std::cout << "middle of the hexToBigInteger: " << hex << std::endl;

    for (uint32_t i = 0; i < bytes_length / 2; i++) {
      std::string byte_str = bytes_str.substr(i * 2, 2);
      std::reverse(byte_str.begin(), byte_str.end());
      uint8_t byte_val = hexToInteger<uint8_t>(byte_str);
      ret *= 256;
      ret += byte_val;
    }
    std::cout << "end of the hexToBigInteger: " << hex << std::endl;
  */
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

std::string bigIntegerToHex(big_int val, int len) {
  if (val == 0) {
    return "00";
  }
  std::cout << "bigIntegerToHex: " << val << std::endl;
  std::vector<std::uint8_t> bytes = to_bytes(val);

  CryptoPP::SecByteBlock byte_block(bytes.size());
  std::copy(bytes.begin(), bytes.end(), byte_block.begin());
  std::cout << bytes.size() << std::endl;
  std::string bytes_str = hexEncode(byte_block);
  std::cout << "bytes str: " << bytes_str << std::endl;

  uint8_t bytes_length = bytes_str.size() / 2;
  std::string bytes_length_str = integerToHex<uint8_t>(bytes_length);
  std::cout << "bytes_length_str: " << bytes_length_str << std::endl;

  StringUtil::toLower(bytes_length_str);
  StringUtil::toLower(bytes_str);
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
  return hexToBigInteger(byte_str, 128);
}

std::string u128Encode(big_int val) {
  //
  return bigIntegerToHex(val, 128);
}

big_int u256Decode(const std::string& byte_str) {
  //
  return hexToBigInteger(byte_str, 128);
}

std::string u256Encode(big_int val) {
  //
  return bigIntegerToHex(val, 256);
}

big_int u512Decode(const std::string& byte_str) {
  //
  return hexToBigInteger(byte_str, 512);
}

std::string u512Encode(big_int val) {
  //
  return bigIntegerToHex(val, 512);
}

std::string stringDecode(const std::string& byte_str) {
  return Casper::StringUtil::hexToString(byte_str);
}

std::string stringEncode(const std::string& val) {
  return Casper::StringUtil::stringToHex(val);
}

// Check this and pkdecode, maybe checksum convert
GlobalStateKey urefDecode(const std::string& byte_str) {
  CryptoPP::SecByteBlock uref_bytes;
  uref_bytes = hexDecode(byte_str);

  return URef::FromString(URef::byteToStringWithAccessRights(uref_bytes));
}

PublicKey publicKeyDecode(const std::string& byte_str) {
  CryptoPP::SecByteBlock public_key_bytes;
  public_key_bytes = hexDecode(byte_str);

  return PublicKey::FromBytes(public_key_bytes);
}

}  // namespace Casper
