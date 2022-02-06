#include "CryptoUtil.h"

// TODO: include Cleanup
#include "cryptopp/blake2.h"
#include "cryptopp/cryptlib.h"
#include "cryptopp/files.h"
#include "cryptopp/filters.h"
#include "cryptopp/hex.h"

namespace Casper {
CryptoPP::SecByteBlock CryptoUtil::hexDecode(const std::string& hex) {
  /*
  std::string decoded;
  StringSource ss(hex, true, new HexDecoder(new StringSink(decoded)));
  return SecByteBlock(reinterpret_cast<const unsigned char*>(decoded.data()),
                      decoded.size());
                      */
  return CryptoPP::SecByteBlock(1);
}

std::string CryptoUtil::hexEncode(const CryptoPP::SecByteBlock& bytes) {
  /*
  std::string encoded;
  StringSource ss(bytes.data(), bytes.size(), true,
                  new HexEncoder(new StringSink(encoded)));
  return encoded;
  */
  return "";
}
}  // namespace Casper
