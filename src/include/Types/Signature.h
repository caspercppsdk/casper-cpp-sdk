#pragma once

#include "Base.h"
#include "Types/KeyAlgo.h"
#include "Utils/CEP57Checksum.h"
#include "cryptopp/hex.h"
#include "cryptopp/secblock.h"

using namespace CryptoPP;

namespace Casper {
/// <summary>
/// A wrapper for a cryptographic signature.
/// </summary>
struct Signature {
  /// <summary>
  /// Byte array without the Key algorithm identifier.
  /// </summary>
  SecByteBlock raw_bytes;

  KeyAlgo key_algorithm;

  // TODO: Check this ctor
  Signature() {}

 protected:
  Signature(SecByteBlock raw_bytes_, KeyAlgo key_algorithm_)
      : raw_bytes(raw_bytes_), key_algorithm(key_algorithm_) {}

  /// <summary>
  /// Creates a Signature object from an hexadecimal string (containing the
  /// Key algorithm identifier).
  /// </summary>
 public:
  static Signature FromHexString(const std::string& signature) {
    // TODO: add try catch blocks
    SecByteBlock rawBytes = CEP57Checksum::Decode(signature.substr(2));
    /*
      if (checksumResult == CEP57Checksum.InvalidChecksum)
        throw std::invalid_argument("Public key checksum mismatch.");
  */
    if (signature.substr(0, 2) == "01") {
      return FromRawBytes(rawBytes, KeyAlgo::ED25519);
    } else if (signature.substr(0, 2) == "02") {
      return FromRawBytes(rawBytes, KeyAlgo::SECP256K1);
    } else {
      throw std::invalid_argument("Invalid key algorithm identifier.");
    }
  }

  /// <summary>
  /// Creates a PublicKey object from a byte array (containing the
  /// Key algorithm identifier).
  /// </summary>

  static Signature FromBytes(const SecByteBlock& bytes) {
    if (bytes.empty())
      throw std::invalid_argument("Signature bytes cannot be empty.");

    KeyAlgo algoIdent;

    if (bytes[0] == 0x01) {
      algoIdent = KeyAlgo::ED25519;
    } else if (algoIdent == 0x02) {
      algoIdent = KeyAlgo::SECP256K1;
    } else {
      throw std::invalid_argument("Wrong signature algorithm identifier");
    }

    SecByteBlock data_bytes(bytes.size() - 1);
    std::copy(bytes.begin() + 1, bytes.end(), data_bytes.begin());
    // TODO: copy check
    return Signature(data_bytes, algoIdent);
  }

  /// <summary>
  /// Creates a Signature object from a byte array and the key algorithm
  /// identifier.
  /// </summary>

  static Signature FromRawBytes(const SecByteBlock& rawBytes, KeyAlgo keyAlgo) {
    return Signature(rawBytes, keyAlgo);
  }

  /// <summary>
  /// Returns the bytes of the signature, including the Key algorithm as the
  /// first byte.
  /// </summary>

  SecByteBlock GetBytes() {
    SecByteBlock bytes = SecByteBlock(raw_bytes.SizeInBytes() + 1);
    if (key_algorithm == KeyAlgo::ED25519) {
      bytes[0] = 0x01;
    } else if (key_algorithm == KeyAlgo::SECP256K1) {
      bytes[0] = 0x02;
    } else {
      bytes[0] = 0x00;
    }
    std::copy(raw_bytes.begin(), raw_bytes.end(), bytes.begin() + 1);
    return bytes;
  }

  /// <summary>
  /// Returns the signature as an hexadecimal string, including the key
  /// algorithm in the first position.
  /// </summary>

  std::string ToHexString() const {
    if (key_algorithm == KeyAlgo::ED25519)
      return "01" + CEP57Checksum::Encode(raw_bytes);
    else
      return "02" + CEP57Checksum::Encode(raw_bytes);
  }

  std::string ToString() const { return ToHexString(); }

  /*
    class SignatureConverter : JsonConverter<Signature> {
     public
      override Signature Read(ref Utf8JsonReader reader,
                              Type typeToConvert,
                              JsonSerializerOptions options) {
        {
          try {
            return Signature.FromHexString(reader.GetString());
          } catch (Exception e) {
            throw new JsonException(e.Message);
          }
        }
      }

     public
      override void Write(Utf8JsonWriter writer,
                          Signature signature,
                          JsonSerializerOptions options) =
          > writer.WriteStringValue(signature.ToHexString());
    }
    */
};

// to_json of Signature
inline void to_json(nlohmann::json& j, const Signature& s) {
  // j = s.ToHexString();
  // TODO:fill here
  // j
}

// from_json of Signature
inline void from_json(const nlohmann::json& j, Signature& s) {
  // s
  //  TODO: write the inner code of fromhexstring here
  //  TODO: fill here
  //  s = Signature::FromHexString(j.get<std::string>());
}

}  // namespace Casper
