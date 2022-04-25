#include "Types/ED25519Key.h"
#include "Base.h"
#include <openssl/pem.h>
#include <openssl/evp.h>
#include "Base.h"
#include "cryptopp/osrng.h"
#include "cryptopp/filters.h"  // CryptoPP::StringSink, CryptoPP::StringSource
#include "cryptopp/files.h"
#include "cryptopp/pem.h"
#include "Utils/CEP57Checksum.h"

namespace Casper {
Ed25519Key::Ed25519Key(std::string pem_file_path) {
  FILE* fp = fopen(pem_file_path.c_str(), "r");

  if (!fp) {
    printf("ERROR: file %s does not exist\n", pem_file_path.c_str());
    return;
  }
  std::cout << "1" << std::endl;
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

  std::cout << "2" << std::endl;
  fclose(fp);

  //   std::string output_pem_path =
  //       "/home/yusuf/casper-cpp-sdk/test/data/KeyPair/generated_key_25519.pem";

  BIO* keybio = BIO_new(BIO_s_mem());

  EVP_PKEY_print_private(keybio, pkey, 0, nullptr);
  EVP_PKEY_print_public(keybio, pkey, 0, nullptr);
  BIO_free(keybio);  // Private key

  std::cout << "3" << std::endl;
  unsigned char priv_key_buf[1024];
  size_t priv_key_len;
  EVP_PKEY_get_raw_private_key(pkey, priv_key_buf, &priv_key_len);

  std::cout << "4" << std::endl;

  unsigned char pub_key_buf[1024];
  size_t pub_key_len;
  EVP_PKEY_get_raw_public_key(pkey, pub_key_buf, &pub_key_len);

  std::cout << "5" << std::endl;

  std::stringstream priv_key_ss;
  priv_key_ss << std::hex << std::setfill('0');
  for (size_t i = 0; i < priv_key_len; i++) {
    priv_key_ss << std::setw(2) << (unsigned int)priv_key_buf[i];
  }

  std::cout << "6" << std::endl;

  std::stringstream pub_key_ss;
  pub_key_ss << std::hex << std::setfill('0');
  for (size_t i = 0; i < pub_key_len; i++) {
    pub_key_ss << std::setw(2) << (unsigned int)pub_key_buf[i];
  }

  std::cout << "7" << std::endl;

  std::string priv_key_str = priv_key_ss.str();
  std::string pub_key_str = pub_key_ss.str();

  std::cout << "Private Key: " << priv_key_str << std::endl;
  std::cout << "Public Key: " << pub_key_str << std::endl;

  std::cout << "8" << std::endl;

  CryptoPP::SecByteBlock priv_key = hexDecode(priv_key_str);

  std::cout << "9" << std::endl;

  CryptoPP::SecByteBlock pub_key = hexDecode(pub_key_str);

  std::cout << "10" << std::endl;

  CryptoPP::AutoSeededRandomPool prng;
  CryptoPP::SecByteBlock message(hexDecode("Do or do not. There is no try."));

  CryptoPP::ed25519Signer signer(priv_key.data());
  CryptoPP::ed25519Verifier verifier(pub_key.data());

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
  }

  std::cout << "signature: " << encoded << std::endl;

  // verify
  bool is_valid = verifier.VerifyMessage(message.BytePtr(), message.size(),
                                         (CryptoPP::byte*)signature.data(),
                                         signature.size());
  std::cout << "Verification: " << std::boolalpha << is_valid << std::endl;

  this->private_key_str = priv_key_str;
  this->public_key_str = pub_key_str;
}

std::string Ed25519Key::getPrivateKeyStr() { return this->private_key_str; }

std::string Ed25519Key::getPublicKeyStr() { return this->public_key_str; }

}  // namespace Casper
