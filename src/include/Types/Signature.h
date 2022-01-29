#pragma once

#include <string>

#include "Types/KeyAlgo.h"
#include "Utils/CEP57Checksum.h"
#include "lib/cryptopp/hex.h"
#include "lib/cryptopp/secblock.h"

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

    return Signature(bytes., algoIdent);

    return new Signature(bytes[1..], algoIdent);
  }

  /// <summary>
  /// Creates a Signature object from a byte array and the key algorithm
  /// identifier.
  /// </summary>

  static Signature FromRawBytes(byte[] rawBytes, KeyAlgo keyAlgo) {
    return new Signature(rawBytes, keyAlgo);
  }

  /// <summary>
  /// Returns the bytes of the signature, including the Key algorithm as the
  /// first byte.
  /// </summary>

  byte[] GetBytes() {
    byte[] bytes = new byte[1 + RawBytes.Length];
    bytes[0] = KeyAlgorithm switch {KeyAlgo.ED25519 = > 0x01,
                                    KeyAlgo.SECP256K1 = > 0x02, _ = > 0x00};
    Array.Copy(RawBytes, 0, bytes, 1, RawBytes.Length);

    return bytes;
  }

  /// <summary>
  /// Returns the signature as an hexadecimal string, including the key
  /// algorithm in the first position.
  /// </summary>

  std::string ToHexString() {
    if (key_algorithm == KeyAlgo::ED25519)
      return "01" + CEP57Checksum.Encode(RawBytes);
    else
      return "02" + CEP57Checksum.Encode(RawBytes);
  }

  override string ToString() { return ToHexString(); }

  class SignatureConverter : JsonConverter<Signature> {
   public
    override Signature Read(ref Utf8JsonReader reader, Type typeToConvert,
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
    override void Write(Utf8JsonWriter writer, Signature signature,
                        JsonSerializerOptions options) =
        > writer.WriteStringValue(signature.ToHexString());
  }
}
}  // namespace Casper
