#include "Types/ED25519Key.h"
#include "Base.h"
#include <openssl/pem.h>
#include <openssl/evp.h>
#include "Base.h"
#include <cryptopp/osrng.h>
#include <cryptopp/filters.h>  // CryptoPP::StringSink, CryptoPP::StringSource
#include <cryptopp/files.h>
#include <cryptopp/pem.h>
#include "Utils/CEP57Checksum.h"

namespace Casper {
Ed25519Key::Ed25519Key(std::string pem_file_path)
    : pub_key(1024), priv_key(1024) {
  FILE* fp = fopen(pem_file_path.c_str(), "r");

  if (!fp) {
    printf("ERROR: file %s does not exist\n", pem_file_path.c_str());
    return;
  }
  EVP_PKEY* pkey = PEM_read_PrivateKey(fp, nullptr, nullptr, nullptr);

  if (pkey == nullptr) {
    printf("ERROR: file %s is not a valid private key\n",
           pem_file_path.c_str());
    return;
  }

  if (EVP_PKEY_id(pkey) != EVP_PKEY_ED25519) {
    printf("ERROR: file %s is not a valid ED25519 private key\n",
           pem_file_path.c_str());
    return;
  }

  fclose(fp);

  BIO* keybio = BIO_new(BIO_s_mem());

  EVP_PKEY_print_private(keybio, pkey, 0, nullptr);
  EVP_PKEY_print_public(keybio, pkey, 0, nullptr);
  BIO_free(keybio);  // Private key

  size_t priv_key_len = priv_key.size();
  EVP_PKEY_get_raw_private_key(pkey, (unsigned char*)priv_key.data(),
                               &priv_key_len);

  // resize
  priv_key.resize(priv_key_len);

  size_t pub_key_len = pub_key.size();
  EVP_PKEY_get_raw_public_key(pkey, (unsigned char*)pub_key.data(),
                              &pub_key_len);

  // resize
  pub_key.resize(pub_key_len);

  std::string priv_key_str = hexEncode(priv_key);
  std::string pub_key_str = hexEncode(pub_key);

  this->private_key_str = priv_key_str;
  this->public_key_str = pub_key_str;
}

// sign
std::string Ed25519Key::sign(std::string message_str) {
  CryptoPP::SecByteBlock message(hexDecode(message_str));
  CryptoPP::SecByteBlock signature = sign(message);
  std::string signature_str = hexEncode(signature);
  return signature_str;
}

CryptoPP::SecByteBlock Ed25519Key::sign(const CryptoPP::SecByteBlock& message) {
  CryptoPP::AutoSeededRandomPool prng;
  CryptoPP::ed25519Signer signer(priv_key.data());

  size_t siglen = signer.MaxSignatureLength();
  std::string signature(siglen, 0x00);
  siglen = signer.SignMessage(prng, message.BytePtr(), message.size(),
                              (CryptoPP::byte*)signature.data());
  signature.resize(siglen);

  std::string encoded;
  CryptoPP::HexEncoder encoder;
  encoder.Put((CryptoPP::byte*)signature.data(), signature.size());
  encoder.MessageEnd();
  CryptoPP::word64 size = encoder.MaxRetrievable();
  if (size) {
    encoded.resize(size);
    encoder.Get((CryptoPP::byte*)encoded.data(), encoded.size());
  } else {
    throw std::runtime_error("Error encoding signature to hex");
  }

  std::cout << "signature: " << encoded << std::endl;

  CryptoPP::SecByteBlock signature_block(hexDecode(encoded));

  return signature_block;
}

bool Ed25519Key::verify(const CryptoPP::SecByteBlock& message,
                        const CryptoPP::SecByteBlock& signature) {
  CryptoPP::ed25519Verifier verifier(pub_key.data());

  // verify
  bool is_valid = verifier.VerifyMessage(message.BytePtr(), message.size(),
                                         (CryptoPP::byte*)signature.data(),
                                         signature.size());
  std::cout << "Verification: " << std::boolalpha << is_valid << std::endl;
  return is_valid;
}

bool Ed25519Key::verify(std::string message, std::string signature) {
  CryptoPP::SecByteBlock message_block(hexDecode(message));
  CryptoPP::SecByteBlock signature_block(hexDecode(signature));

  return verify(message_block, signature_block);
}

std::string Ed25519Key::getPrivateKeyStr() { return this->private_key_str; }

std::string Ed25519Key::getPublicKeyStr() { return this->public_key_str; }

}  // namespace Casper
