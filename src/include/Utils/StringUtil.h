#pragma once

#include "Base.h"

namespace Casper {

struct StringUtil {
  static bool startsWith(const std::string& str, const std::string& cmp);

  static std::vector<std::string> splitString(std::string str,
                                              std::string delim);
  static std::string toLower(std::string& str);
};

}  // namespace Casper