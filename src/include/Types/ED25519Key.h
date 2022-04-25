#pragma once
#include <string>
#include "cryptopp/secblock.h"

namespace Casper {
class Ed25519Key {
  std::string public_key_str;
  std::string private_key_str;

 public:
  /// Create a Private Key from pem file
  Ed25519Key(std::string pem_file_path);

  /// Sign a message with the private key and return the signature
  std::string sign(std::string message);

  CryptoPP::SecByteBlock sign(const CryptoPP::SecByteBlock& message);

  /// Verify the signature on the message using the public key

  bool verify(std::string message, std::string signature);

  /// Get the public key in string as hex format
  /// The first part, not Y value.
  /// Eliminate the h(0x)
  std::string getPublicKeyStr();

  /// Get the private key in string as hex format
  /// Eliminate the h(0x)
  std::string getPrivateKeyStr();
};

}  // namespace Casper
