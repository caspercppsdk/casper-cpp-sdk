#pragma once
#include <cryptopp/eccrypto.h>
#include <string>

namespace Casper {

class Secp256k1Key {
 private:
  CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PrivateKey _private_key;
  CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PublicKey _public_key;

  std::string public_key_str;
  std::string private_key_str;

 public:
  /// Create a Private Key from pem file
  Secp256k1Key(std::string pem_file_path);

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

 public:
  /// Get the signature in string as hex format
  static std::string signatureToString(std::string signature);

 private:
  /// Convert CryptoPP::Integer values to std::string with eliminate the h(0x)
  /// for 64 char hex string
  std::string integerToString(CryptoPP::Integer x);

  /// Convert CryptoPP::Integer values to std::string with add the h(0x) as
  /// prefix for 64 char hex string
  CryptoPP::Integer stringToInteger(std::string hex_str);
};

}  // namespace Casper
