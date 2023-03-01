#pragma once

#include "Base.h"

// Crypto
#include <cryptopp/secblock.h>

namespace Casper {
struct CryptoUtil {
  static CBytes hexDecode(std::string hex);

  static std::string hexEncode(CBytes bytes);

  static std::string timeToRFC3339(time_t time);
};

}  // namespace Casper
