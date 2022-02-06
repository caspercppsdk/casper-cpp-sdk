#pragma once
#include <string>
#include <vector>

#include "Utils/StringUtil.h"
#include "cryptopp/blake2.h"
#include "cryptopp/cryptlib.h"
#include "cryptopp/files.h"
#include "cryptopp/filters.h"
#include "cryptopp/hex.h"
#include "cryptopp/secblock.h"

using namespace CryptoPP;
namespace Casper {
SecByteBlock hexDecode(const std::string& hex) {
  /*
  std::string decoded;
  StringSource ss(hex, true, new HexDecoder(new StringSink(decoded)));
  return SecByteBlock(reinterpret_cast<const unsigned char*>(decoded.data()),
                      decoded.size());
                      */
  return SecByteBlock(1);
}

std::string hexEncode(const SecByteBlock& bytes) {
  /*
  std::string encoded;
  StringSource ss(bytes.data(), bytes.size(), true,
                  new HexEncoder(new StringSink(encoded)));
  return encoded;
  */
  return "";
}
}  // namespace Casper