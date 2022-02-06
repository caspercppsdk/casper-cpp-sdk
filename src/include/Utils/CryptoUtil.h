#pragma once

#include "Base.h"

// Crypto
#include "cryptopp/secblock.h"

namespace Casper {
struct CryptoUtil {
  static CryptoPP::SecByteBlock hexDecode(const std::string& hex);

  static std::string hexEncode(const CryptoPP::SecByteBlock& bytes);
};

}  // namespace Casper