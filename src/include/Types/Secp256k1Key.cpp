#include "Types/Secp256k1Key.h"
#include "Base.h"
#include <cryptopp/osrng.h>
#include <cryptopp/filters.h>  // CryptoPP::StringSink, CryptoPP::StringSource
#include <cryptopp/files.h>
#include <cryptopp/pem.h>
#include "Utils/CEP57Checksum.h"
namespace Casper {

Secp256k1Key::Secp256k1Key(std::string pem_file_path) {
  CryptoPP::AutoSeededRandomPool prng;

  /// Create a Private Key from pem file
  CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PrivateKey temp_private_key;
  CryptoPP::FileSource fs1(pem_file_path.c_str(), true);  // Load the PEM file
  CryptoPP::PEM_Load(fs1, temp_private_key);  // Load private key from PEM file
  CryptoPP::Integer temp_param = temp_private_key.GetPrivateExponent();

  /// Initialize the private key in secp256k1 format
  _private_key.Initialize(CryptoPP::ASN1::secp256k1(), temp_param);

  /// Check if the private key is valid
  if (_private_key.Validate(prng, 3) == false) {
    throw std::runtime_error("Unable to verify the SECP256K1 Private Key");
  }

  /// Initialize the public key
  _private_key.MakePublicKey(_public_key);

  if (_public_key.Validate(prng, 3) == false) {
    throw std::runtime_error("Unable to verify the SECP256K1 Public Key");
  }

  CryptoPP::ECP::Point q = _public_key.GetPublicElement();

  uint8_t pub_key_prefix;
  if (q.y.IsEven()) {
    pub_key_prefix = 0x02;
  } else {
    pub_key_prefix = 0x03;
  }

  std::stringstream ss;
  ss << integerToHex<uint8_t>(pub_key_prefix);
  ss << std::hex << q.x;
  std::string out_str = ss.str();

  std::string out_str_no_h = out_str.substr(0, 66);
  // std::cout << "out_str_no_h: " << out_str_no_h << std::endl;
  // std::cout << "out_str_no_h size: " << out_str_no_h.size() << std::endl;

  // Convert CryptoPP::Integer values to std::string with eliminate the h(0x)
  private_key_str = integerToString(_private_key.GetPrivateExponent());

  // use the first part, not Y value
  public_key_str = out_str_no_h;
}

std::string Secp256k1Key::getPublicKeyStr() { return public_key_str; }

std::string Secp256k1Key::getPrivateKeyStr() { return private_key_str; }

std::string Secp256k1Key::sign(std::string message) {
  CryptoPP::AutoSeededRandomPool prng;
  CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::Signer signer(_private_key);

  size_t siglen = signer.MaxSignatureLength();
  std::string signature(siglen, 0x00);

  siglen = signer.SignMessage(prng, (const CryptoPP::byte*)&message[0],
                              message.size(), (CryptoPP::byte*)&signature[0]);
  signature.resize(siglen);

  return signature;
}

CryptoPP::SecByteBlock Secp256k1Key::sign(
    const CryptoPP::SecByteBlock& message) {
  CryptoPP::AutoSeededRandomPool prng;
  CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::Signer signer(_private_key);

  size_t siglen = signer.MaxSignatureLength();
  CryptoPP::SecByteBlock sig_bytes(siglen);

  do {
    siglen = signer.SignMessage(prng, (const CryptoPP::byte*)&message[0],
                                message.size(), sig_bytes);
    sig_bytes.resize(siglen);

    std::cout << "sig bytes while loop\n";

  } while ((sig_bytes[32] & 0x80) == 0x80);

  std::cout << "signature size: " << sig_bytes.size() << std::endl;
  std::cout << "aftter sig decode: " << sig_bytes.size() << std::endl;
  return sig_bytes;
}

bool Secp256k1Key::verify(std::string message, std::string signature) {
  CryptoPP::AutoSeededRandomPool prng;

  CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::Verifier verifier(
      _public_key);

  bool result = verifier.VerifyMessage(
      (const CryptoPP::byte*)&message[0], message.size(),
      (const CryptoPP::byte*)&signature[0], signature.size());

  if (result) {
    std::cout << "SECP256K1 signature is successfully verified" << std::endl;
  } else {
    std::cout << "Failed to verify SECP256K1 Signature" << std::endl;
  }

  return result;
}

std::string Secp256k1Key::signatureToString(std::string signature) {
  CryptoPP::SecByteBlock sig_bytes(signature.size());
  memcpy(sig_bytes.data(), signature.data(), signature.size());
  std::string encoded = hexEncode(sig_bytes);

  return encoded;
}

std::string Secp256k1Key::integerToString(CryptoPP::Integer x) {
  std::stringstream ss;
  ss << std::hex << x;
  std::string out_str = ss.str();
  // std::cout << "out_str: " << out_str << std::endl;
  // std::cout << "out_str size: " << out_str.size() << std::endl;
  std::string out_str_no_h = out_str.substr(0, 64);
  return out_str.substr(0, 64);
}

CryptoPP::Integer Secp256k1Key::stringToInteger(std::string hex_str) {
  hex_str.insert(0, "0x");

  CryptoPP::Integer out_integer(hex_str.c_str());
  return out_integer;
}

}  // namespace Casper
