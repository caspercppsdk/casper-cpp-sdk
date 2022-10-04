#include "Types/CLConverter.h"

#include <chrono>

#include "date/date.h"
//#include "bigint/BigIntegerLibrary.hh"
namespace Casper
{

  uint64_t strToTimestamp(std::string str_date)
  {
    using namespace date;
    using namespace std;
    using namespace std::chrono;

    istringstream in{str_date};
    in.exceptions(ios::failbit);
    date::sys_time<milliseconds> tp;
    in >> date::parse("%FT%TZ", tp);
    //cout << tp << " = " << tp.time_since_epoch() << '\n';
    return duration_cast<milliseconds>(tp.time_since_epoch()).count();
  }

  // Encoding & Decoding

  bool boolDecode(const std::string &byte_str)
  {
    //
    return hexToInteger<bool>(byte_str);
  }

  std::string boolEncode(bool val)
  {
    //
    return integerToHex<bool>(val);
  }

  int32_t i32Decode(const std::string &byte_str)
  {
    //
    return hexToInteger<int32_t>(byte_str);
  }

  std::string i32Encode(int32_t val)
  {
    //
    return integerToHex<int32_t>(val);
  }

  int64_t i64Decode(const std::string &byte_str)
  {
    //
    return hexToInteger<int64_t>(byte_str);
  }

  std::string i64Encode(int64_t val)
  {
    //
    return integerToHex<int64_t>(val);
  }

  uint8_t u8Decode(const std::string &byte_str)
  {
    //
    return hexToInteger<uint8_t>(byte_str);
  }

  std::string u8Encode(uint8_t val)
  {
    //
    return integerToHex<uint8_t>(val);
  }

  uint32_t u32Decode(const std::string &byte_str)
  {
    //
    return hexToInteger<uint32_t>(byte_str);
  }

  std::string u32Encode(uint32_t val)
  {
    //
    return integerToHex<uint32_t>(val);
  }

  uint64_t u64Decode(const std::string &byte_str)
  {
    //
    return hexToInteger<uint64_t>(byte_str);
  }

  std::string u64Encode(uint64_t val)
  {
    //
    return integerToHex<uint64_t>(val);
  }

  std::string stringDecode(const std::string &byte_str)
  {
    return Casper::StringUtil::hexToString(byte_str);
  }

  std::string stringEncode(const std::string &val)
  {
    return Casper::StringUtil::stringToHex(val);
  }

  // Check this and pkdecode, maybe checksum convert
  GlobalStateKey urefDecode(const std::string &byte_str)
  {
    CBytes uref_bytes;
    uref_bytes = hexDecode(byte_str);

    return URef::FromString(URef::byteToStringWithAccessRights(uref_bytes));
  }

  PublicKey publicKeyDecode(const std::string &byte_str)
  {
    CBytes public_key_bytes;
    public_key_bytes = hexDecode(byte_str);

    return PublicKey::FromBytes(public_key_bytes);
  }

} // namespace Casper
