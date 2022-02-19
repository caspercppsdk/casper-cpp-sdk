#include "CryptoUtil.h"

// TODO: include Cleanup
#include "cryptopp/blake2.h"
#include "cryptopp/cryptlib.h"
#include "cryptopp/files.h"
#include "cryptopp/filters.h"
#include "cryptopp/hex.h"

namespace Casper {
CryptoPP::SecByteBlock CryptoUtil::hexDecode(std::string encoded) {
  // std::cout << "hexDecode: " << encoded << std::endl;
  CryptoPP::StringSource ss(encoded, true, new CryptoPP::HexDecoder);
  CryptoPP::SecByteBlock decoded((size_t)ss.MaxRetrievable());
  ss.Get(decoded, decoded.size());
  return decoded;
}

std::string CryptoUtil::hexEncode(CryptoPP::SecByteBlock decoded) {
  std::string encoded;

  CryptoPP::StringSource ss(
      decoded, decoded.size(), true,
      new CryptoPP::HexEncoder(new CryptoPP::StringSink(encoded))  // HexEncoder
  );  // StringSource

  return encoded;
}
}  // namespace Casper
