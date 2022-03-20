#pragma once

#include <sstream>
#include <stdexcept>
#include <string>

// Utils
#include "Utils/CryptoUtil.h"

// CryptoPP
#include <cryptopp/xed25519.h>

#include "cryptopp/blake2.h"
#include "cryptopp/cryptlib.h"
#include "cryptopp/files.h"
#include "cryptopp/hex.h"
#include "cryptopp/secblock.h"

using namespace CryptoPP;

namespace Casper {
class CEP57Checksum {
 private:
  static SecByteBlock _bytes_to_nibbles(SecByteBlock bytes);

  static std::vector<bool> _bytes_to_bits_cycle(SecByteBlock bytes);

 public:
  static bool HasChecksum(std::string hex);

  static std::string Encode(SecByteBlock decoded);

  static SecByteBlock Decode(std::string encoded);
};

}  // namespace Casper
