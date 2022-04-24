#include "Types/ED25519Key.h"
#include "Base.h"
#include <openssl/pem.h>
#include <openssl/evp.h>

namespace Casper {

int do_sign(EVP_PKEY *ed_key, unsigned char *msg, size_t msg_len) {
  size_t sig_len;
  unsigned char *sig = NULL;
  EVP_MD_CTX *md_ctx = EVP_MD_CTX_new();

  EVP_DigestSignInit(md_ctx, NULL, NULL, NULL, ed_key);

  EVP_DigestSign(md_ctx, NULL, &sig_len, msg, msg_len);
  sig = static_cast<unsigned char *>(OPENSSL_zalloc(sig_len));

  EVP_DigestSign(md_ctx, sig, &sig_len, msg, msg_len);
  OPENSSL_free(sig);
  EVP_MD_CTX_free(md_ctx);
}
/*
int main() {
  int ret = EXIT_FAILURE;
  const char *str = "I am watching you!I am watching you!";
  unsigned char *sig = NULL;
  size_t slen = 0;
  unsigned char msg[BUFFSIZE];
  size_t mlen = 0;

  EVP_PKEY *key = read_secret_key_from_file(KEYFILE);
  if (!key) goto err;

  for (int i = 0; i < N; i++) {
    if (snprintf((char *)msg, BUFFSIZE, "%s %d", str, i + 1) < 0) goto err;
    mlen = strlen((const char *)msg);
    if (!do_sign(key, msg, mlen, &sig, &slen)) goto err;
    OPENSSL_free(sig);
    sig = NULL;
    printf("\"%s\" -> siglen=%lu\n", msg, slen);
  }

  printf("DONE\n");
  ret = EXIT_SUCCESS;

err:
  if (ret != EXIT_SUCCESS) {
    ERR_print_errors_fp(stderr);
    fprintf(stderr, "Something broke!\n");
  }

  if (key) EVP_PKEY_free(key);

  exit(ret);
}
*/
/*
void do_sign(EVP_PKEY *ed_key, unsigned char *msg, size_t msg_len) {
  size_t sig_len;
  unsigned char *sig = NULL;
  EVP_MD_CTX *md_ctx = EVP_MD_CTX_new();

  EVP_DigestSignInit(md_ctx, NULL, NULL, NULL, ed_key);
  /* Calculate the requires size for the signature by passing a NULL buffer
  EVP_DigestSign(md_ctx, NULL, &sig_len, msg, msg_len);
  sig = static_cast<unsigned char *>(OPENSSL_zalloc(sig_len));

  EVP_DigestSign(md_ctx, sig, &sig_len, msg, msg_len);

  OPENSSL_free(sig);
  EVP_MD_CTX_free(md_ctx);
}
*/
void FromPemFile(std::string filename) {
  FILE *fp = fopen(filename.c_str(), "r");

  if (!fp) {
    printf("ERROR: file %s does not exist\n", filename.c_str());
    return;
  }

  EVP_PKEY *pkey = PEM_read_PrivateKey(fp, nullptr, nullptr, nullptr);

  if (pkey == nullptr) {
    printf("ERROR: file %s is not a valid private key\n", filename.c_str());
    return;
  }

  if (EVP_PKEY_id(pkey) != EVP_PKEY_ED25519) {
    printf("ERROR: file %s is not a valid ED25519 private key\n",
           filename.c_str());
    return;
  }

  fclose(fp);

  //   std::string output_pem_path =
  //       "/home/yusuf/casper-cpp-sdk/test/data/KeyPair/generated_key_25519.pem";

  BIO *keybio = BIO_new(BIO_s_mem());

  EVP_PKEY_print_private(keybio, pkey, 0, nullptr);
  EVP_PKEY_print_public(keybio, pkey, 0, nullptr);

  unsigned char priv_key_buf[1024];
  size_t priv_key_len;
  EVP_PKEY_get_raw_private_key(pkey, priv_key_buf, &priv_key_len);

  unsigned char pub_key_buf[1024];
  size_t pub_key_len;
  EVP_PKEY_get_raw_public_key(pkey, pub_key_buf, &pub_key_len);

  std::stringstream priv_key_ss;
  priv_key_ss << std::hex << std::setfill('0');
  for (size_t i = 0; i < priv_key_len; i++) {
    priv_key_ss << std::setw(2) << (unsigned int)priv_key_buf[i];
  }

  std::stringstream pub_key_ss;
  pub_key_ss << std::hex << std::setfill('0');
  for (size_t i = 0; i < pub_key_len; i++) {
    pub_key_ss << std::setw(2) << (unsigned int)pub_key_buf[i];
  }

  std::string priv_key_str = priv_key_ss.str();
  std::string pub_key_str = pub_key_ss.str();

  std::cout << "Private Key: " << priv_key_str << std::endl;
  std::cout << "Public Key: " << pub_key_str << std::endl;

  //
  char buffer[1024];
  std::string res = "";
  while (BIO_read(keybio, buffer, 1024) > 0) {
    res += buffer;
  }
  std::cout << "test prev" << std::endl;
  std::cout << res << std::endl;
  std::cout << "test end" << std::endl;

  //
  //
  BIO_free(keybio);  // Private key

  /*
    const char *str = "I am watching you!I am watching you!";
    unsigned char *sig = NULL;
    size_t slen = 0;
    unsigned char msg[BUFFSIZE];
    size_t mlen = 0;

    for (int i = 0; i < N; i++) {
      if (snprintf((char *)msg, BUFFSIZE, "%s %d", str, i + 1) < 0) {
        printf("ERROR: snprintf failed\n");
        return;
      }
      mlen = strlen((const char *)msg);
      if (!do_sign(pkey, msg, mlen)) {
        printf("ERROR: do_sign failed\n");
        return;
      }
    }

    printf("DONE\n");
    if (pkey) EVP_PKEY_free(pkey);
    */
}

int edKeyTest() {
  std::string pem_priv_path =
      "/home/yusuf/casper-cpp-sdk/test/data/KeyPair/eddsa_secret_key.pem";
  FromPemFile(pem_priv_path);

  return 1;
}
}  // namespace Casper
