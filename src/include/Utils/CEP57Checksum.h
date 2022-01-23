#pragma once
#include <sstream>
#include <stdexcept>
#include <string>

#include "lib/cryptopp/blake2.h"
#include "lib/cryptopp/cryptlib.h"
#include "lib/cryptopp/files.h"
#include "lib/cryptopp/hex.h"
#include "lib/cryptopp/secblock.h"
using namespace CryptoPP;

namespace Casper {
class CEP57Checksum {
 private:
  static constexpr const int SMALL_BYTES_COUNT = 75;
  static constexpr const char HexChars[]{'0', '1', '2', '3', '4', '5',
                                         '6', '7', '8', '9', 'a', 'b',
                                         'c', 'd', 'e', 'f'};

 public:
  static constexpr const int NoChecksum = 0x00;
  static constexpr const int ValidChecksum = 0x01;
  static constexpr const int InvalidChecksum = 0x02;

 private:
  static SecByteBlock _bytes_to_nibbles(const SecByteBlock& bytes) {
    SecByteBlock nibbles(bytes.SizeInBytes() * 2);
    for (int i = 0; i < bytes.SizeInBytes(); i++) {
      nibbles[i * 2] = (bytes.data()[i] & 0xF0) >> 4;
      nibbles[i * 2 + 1] = bytes.data()[i] & 0x0F;
    }
    // TODO: Check nible assignment correctness with the following code:
    // 0xFO may be redundant
    /*
    try {
      var writer = new BinaryWriter(new MemoryStream(nibbles));
      foreach (var b in bytes) {
        writer.Write((byte)(b >> 4));
        writer.Write((byte)(b & 0x0F));
      }
    } catch (Exception e) {
      Console.WriteLine(e);
      throw;
    }
*/
    return nibbles;
  }

  static std::vector<bool> _bytes_to_bits_cycle(const SecByteBlock& bytes) {
    size_t bit_size = bytes.SizeInBytes() * 8;
    std::vector<bool> bits(bit_size);
    for (int i = 0, k = 0; i < bytes.SizeInBytes(); i++)
      for (int j = 0; j < 8; j++)
        bits[k++] = ((bytes.data()[i] >> j) & 0x01) == 0x01;
    return bits;
  }

 public:
  static bool HasChecksum(const std::string& hex) {
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

  static std::string Encode(const SecByteBlock& input) {
    if (input.size() > SMALL_BYTES_COUNT) {
      std::string encoded_hex;
      StringSource ss(input.data(), input.size(), true,
                      new HexEncoder(new StringSink(encoded_hex))  // HexEncoder
      );
      return encoded_hex;
    }

    SecByteBlock nibbles = _bytes_to_nibbles(input);

    BLAKE2b hash(32u);
    hash.Update(input.data(), input.size());
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

  static SecByteBlock Decode(const std::string& hex) {
    SecByteBlock bytes(reinterpret_cast<const byte*>(&hex[0]), hex.size());

    if (bytes.SizeInBytes() > SMALL_BYTES_COUNT || !HasChecksum(hex)) {
      throw std::runtime_error("No Checksum");
    }

    std::string computed = Encode(bytes);
    if (computed != hex) {
      throw std::runtime_error("Invalid Checksum");
    }

    return bytes;
  }
};

}  // namespace Casper
