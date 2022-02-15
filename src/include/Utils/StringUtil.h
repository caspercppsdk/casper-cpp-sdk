#pragma once

#include "Base.h"

namespace Casper {
struct StringUtil {
  static bool startsWith(const std::string& str, const std::string& cmp);

  static std::vector<std::string> splitString(const std::string& str,
                                              const std::string& delim);
  static std::string StringUtil::toLower(std::string str);
};

}  // namespace Casper