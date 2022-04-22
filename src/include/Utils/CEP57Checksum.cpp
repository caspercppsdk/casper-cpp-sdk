#include "Utils/CEP57Checksum.h"
#include "Utils/StringUtil.h"
namespace Casper {
constexpr const int SMALL_BYTES_COUNT = 75;
constexpr const char HexChars[]{'0', '1', '2', '3', '4', '5', '6', '7',
                                '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

SecByteBlock CEP57Checksum::_bytes_to_nibbles(SecByteBlock bytes) {
  SecByteBlock nibbles(bytes.size() * 2);
  for (int i = 0; i < bytes.size(); i++) {
    nibbles[i * 2] = (bytes.data()[i] & 0xF0) >> 4;
    nibbles[i * 2 + 1] = bytes.data()[i] & 0x0F;
  }
  return nibbles;
}

std::vector<bool> CEP57Checksum::_bytes_to_bits_cycle(SecByteBlock bytes) {
  size_t bit_size = bytes.size() * 8;
  std::vector<bool> bits(bit_size);
  for (int i = 0, k = 0; i < bytes.size(); i++)
    for (int j = 0; j < 8; j++)
      bits[k++] = ((bytes.data()[i] >> j) & 0x01) == 0x01;
  return bits;
}

bool CEP57Checksum::HasChecksum(std::string hex) {
  int mix = 0;
  for (auto& c : hex) {
    if (c >= '0' && c <= '9')
      mix |= 0x00;
    else if (c >= 'a' && c <= 'f')
      mix |= 0x01;
    else if (c >= 'A' && c <= 'F')
      mix |= 0x02;
    else
      throw std::invalid_argument("Invalid hex character.");
  }
  return mix > 2;
}

std::string CEP57Checksum::Encode(SecByteBlock decoded) {
  if (decoded.size() > SMALL_BYTES_COUNT) {
    std::string encoded;

    StringSource ss(decoded, decoded.size(), true,
                    new HexEncoder(new StringSink(encoded))  // HexEncoder
    );                                                       // StringSource
    return encoded;
  }

  SecByteBlock nibbles = _bytes_to_nibbles(decoded);

  BLAKE2b hash(32u);
  hash.Update(decoded.data(), decoded.size());
  SecByteBlock digest_bytes(hash.DigestSize());
  hash.Final(digest_bytes.data());

  std::vector<bool> hashBits = _bytes_to_bits_cycle(digest_bytes);

  std::string encoded_bytes(nibbles.size(), '0');

  int k = 0;
  int i = 0;

  for (auto& n : nibbles) {
    char c = HexChars[n];
    if ((c >= 'a' && c <= 'f') && hashBits[k++])
      encoded_bytes[i++] = (char)(c - ('a' - 'A'));
    else
      encoded_bytes[i++] = c;
  }

  return encoded_bytes;
}

SecByteBlock CEP57Checksum::Decode(std::string encoded) {
  CryptoPP::SecByteBlock decoded = CryptoUtil::hexDecode(encoded);
  if (decoded.size() > SMALL_BYTES_COUNT || !HasChecksum(encoded)) {
    return decoded;
  }

  std::string computed = Encode(decoded);
  if (computed != encoded) {
    throw std::runtime_error("Invalid Checksum");
  }

  return decoded;
}
}  // namespace Casper
