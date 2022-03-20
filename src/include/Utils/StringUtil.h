#pragma once

#include "Base.h"

namespace Casper {
struct StringUtil {
  static bool startsWith(std::string str, std::string cmp);

  static std::vector<std::string> splitString(std::string str,
                                              std::string delim);
  static std::string toLower(std::string str);
};

}  // namespace Casper