#pragma once

#include "Base.h"

// Crypto
#include "cryptopp/secblock.h"

namespace Casper {
struct CryptoUtil {
  static CryptoPP::SecByteBlock hexDecode(std::string hex);

  static std::string hexEncode(CryptoPP::SecByteBlock bytes);
};

}  // namespace Casper