#pragma once

#include "Base.h"

// Crypto
#include <cryptopp/secblock.h>

namespace Casper {
struct CryptoUtil {
  static CBytes hexDecode(std::string hex);

  static std::string hexEncode(CBytes bytes);
};

}  // namespace Casper
