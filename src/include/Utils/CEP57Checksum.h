#pragma once

#include <sstream>
#include <stdexcept>
#include <string>

// Utils
#include "Utils/CryptoUtil.h"

// CryptoPP
#include <cryptopp/xed25519.h>

#include <cryptopp/blake2.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/files.h>
#include <cryptopp/hex.h>
#include <cryptopp/secblock.h>

namespace Casper {
class CEP57Checksum {
 private:
  static CBytes _bytes_to_nibbles(CBytes bytes);

  static std::vector<bool> _bytes_to_bits_cycle(CBytes bytes);

 public:
  static bool HasChecksum(std::string hex);

  static std::string Encode(CBytes decoded);

  static CBytes Decode(std::string encoded);
};

}  // namespace Casper
