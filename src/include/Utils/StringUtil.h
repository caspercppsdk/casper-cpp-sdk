#pragma once

#include "Base.h"

namespace Casper {

struct StringUtil {
  static bool startsWith(const std::string& str, const std::string& cmp);

  static std::vector<std::string> splitString(std::string str,
                                              std::string delim);
  static std::string toLower(std::string& str);

  static uint32_t hexStrToUint32(const std::string& str);

  static std::string hexToUTF8(const std::string& str);

  static std::string getStringBytesWithoutLength(const std::string& str);

  static std::string hexToString(const std::string& bytes_str);

  static std::string stringToHex(const std::string& str);
};

}  // namespace Casper