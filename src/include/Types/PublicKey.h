#pragma once
#include <cctype>
#include <iostream>
#include <vector>

#include "Types/KeyAlgo.h"
#include "Utils/CEP57Checksum.h"
#include "Utils/File.h"
#include "nlohmann/json.hpp"

namespace Casper {
struct PublicKey {
  SecByteBlock raw_bytes;
  KeyAlgo key_algorithm;

 protected:
  PublicKey(SecByteBlock raw_bytes_, KeyAlgo key_algorithm_)
      : raw_bytes(raw_bytes_), key_algorithm(key_algorithm_) {}

 public:
  /// <summary>
  /// Creates a PublicKey object from an hexadecimal string (containing the
  /// Key algorithm identifier).
  /// </summary>
  static PublicKey FromHexString(const std::string& hexBytes) {
    // TODO: add try catch blocks
    SecByteBlock rawBytes = CEP57Checksum::Decode(hexBytes.substr(2));
    /*
      if (checksumResult == CEP57Checksum.InvalidChecksum)
        throw std::invalid_argument("Public key checksum mismatch.");
  */
    if (hexBytes.substr(0, 2) == "01") {
      return FromRawBytes(rawBytes, KeyAlgo::ED25519);
    } else if (hexBytes.substr(0, 2) == "02") {
      return FromRawBytes(rawBytes, KeyAlgo::SECP256K1);
    } else {
      throw std::invalid_argument("Invalid key algorithm identifier.");
    }
  }

  /// <summary>
  /// Loads a PublicKey from a PEM file
  /// </summary>
  /*
  static PublicKey FromPem(std::string filePath) {
    using(TextReader textReader =
              new StringReader(File.ReadAllText(filePath))) {
      var reader = new PemReader(textReader);

      var pemObject = reader.ReadObject();

      if (pemObject is Ed25519PublicKeyParameters edPk) {
        byte[] rawBytes = edPk.GetEncoded();
        return new PublicKey(rawBytes, KeyAlgo.ED25519);
      }

      if (pemObject is ECPublicKeyParameters ecPk) {
        byte[] compressed = ecPk.Q.GetEncoded(true);
        return PublicKey(compressed, KeyAlgo.SECP256K1);
      }

      throw std::invalid_argument(
          "Unsupported key format or it's not a private key PEM object.");
    }
  }
*/
  /// <summary>
  /// Creates a PublicKey object from a byte array. First byte in the array must
  /// contain the key algorithm identifier.
  /// </summary>
  static PublicKey FromBytes(const SecByteBlock& bytes) {
    if (bytes.empty())
      throw std::invalid_argument("Public key bytes cannot be empty.");

    unsigned char algoIdent = bytes[0];

    int expectedPublicKeySize = -1;
    std::string algo = "";

    if (algoIdent == 0x01) {
      expectedPublicKeySize = KeyAlgo::GetKeySizeInBytes(KeyAlgo::ED25519);
      algo = KeyAlgo::GetName(KeyAlgo::ED25519);
    } else if (algoIdent == 0x02) {
      KeyAlgo::GetKeySizeInBytes(KeyAlgo::SECP256K1);
      algo = KeyAlgo::GetName(KeyAlgo::SECP256K1);
    } else {
      throw std::invalid_argument("Invalid key algorithm identifier.");
    }

    if (bytes.size() < expectedPublicKeySize)
      throw std::runtime_error("Wrong public key format. Expected length is " +
                               std::to_string(expectedPublicKeySize));

    SecByteBlock rawBytes(expectedPublicKeySize - 1);

    std::copy(bytes.begin() + 1, bytes.begin() + expectedPublicKeySize,
              rawBytes.begin());

    return PublicKey(rawBytes,
                     algoIdent == 0x01 ? KeyAlgo::ED25519 : KeyAlgo::SECP256K1);
  }

  /// <summary>
  /// Creates a PublicKey object from a byte array and the key algorithm
  /// identifier.
  /// </summary>
  static PublicKey FromRawBytes(const SecByteBlock& rawBytes, KeyAlgo keyAlgo) {
    try {
      int expectedPublicKeySize = KeyAlgo::GetKeySizeInBytes(keyAlgo) - 1;
      if (rawBytes.size() != expectedPublicKeySize) {
        throw std::runtime_error(
            "Wrong public key format. Expected length is " +
            std::to_string(expectedPublicKeySize));
      }
    } catch (std::exception& e) {
      // throw std::exception(e.what());
    }
    return PublicKey(rawBytes, keyAlgo);
  }

  /// <summary>
  /// Saves the public key to a PEM file.
  /// </summary>
  /*
    void WriteToPem(const std::string& filePath) {
      if (File::Exists(filePath))
        throw std::runtime_error(
            "Target file already exists. Will not overwrite.\nFile: " +
    filePath);

      using(var textWriter = File.CreateText(filePath)) {
        var writer = new PemWriter(textWriter);

        if (key_algorithm == KeyAlgo.ED25519) {
          Ed25519PublicKeyParameters pk =
              new Ed25519PublicKeyParameters(RawBytes, 0);
          writer.WriteObject(pk);
          return;
        } else if (key_algorithm == KeyAlgo.SECP256K1) {
          var curve = ECNamedCurveTable.GetByName("secp256k1");
          var domainParams = new ECDomainParameters(curve.Curve, curve.G,
    curve.N, curve.H, curve.GetSeed());

          ECPoint q = curve.Curve.DecodePoint(RawBytes);
          ECPublicKeyParameters pk = new ECPublicKeyParameters(q, domainParams);
          writer.WriteObject(pk);
          return;
        }

        throw std::runtime_error("Unsupported key type.");
      }
    }
  */
  /// <summary>
  /// Returns the Account Hash associated to this Public Key.
  /// </summary>
  std::string GetAccountHash() {
    /*
    BLAKE2b hash(32u);
    std::string algo_str = KeyAlgo::GetName(key_algorithm);
    boost::to_lower(algo_str);

    hash.Update(reinterpret_cast<const byte*>(algo_str.data()),
                algo_str.size());
    hash.Update(0x00);
    hash.Update(raw_bytes.begin(), raw_bytes.size());

    SecByteBlock digest_bytes(hash.DigestSize());
    hash.Final(digest_bytes.data());

    return "account-hash-" + CEP57Checksum::Encode(digest_bytes);
    */
    // TODO:

    return "";
  }

  /// <summary>
  /// Returns the key as an hexadecimal string, including the key algorithm in
  /// the first position.
  /// </summary>

  std::string ToAccountHex() {
    if (key_algorithm == KeyAlgo::ED25519) {
      return "01" + CEP57Checksum::Encode(raw_bytes);
    } else if (key_algorithm == KeyAlgo::SECP256K1) {
      return "02" + CEP57Checksum::Encode(raw_bytes);
    } else {
      throw std::runtime_error("Unsupported key type.");
    }
  }

  std::string ToString() { return ToAccountHex(); }
  /*
    bool Equals(object obj) {
      // Check for null and compare run-time types.
      if (obj == null || !GetType().Equals(obj.GetType())) return false;

      var pk = (PublicKey)obj;
      return pk.GetBytes().SequenceEqual(this.GetBytes());
    }
  */
  int GetHashCode() {
    // TODO:
    // return this->ToAccountHex().ToLower().GetHashCode();
    return 0;
  }

  /// <summary>
  /// Returns the bytes of the public key, including the Key algorithm as the
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
  /// Verifies the signature given its value and the original message.
  /// </summary>
  /*
    bool VerifySignature(byte[] message, byte[] signature) {
      if (key_algorithm == KeyAlgo::ED25519) {
        Ed25519PublicKeyParameters edPk =
            new Ed25519PublicKeyParameters(RawBytes, 0);
        return Ed25519.Verify(signature, 0, RawBytes, 0, message, 0,
                              message.Length);
      }

      if (key_algorithm == KeyAlgo::SECP256K1) {
        var curve = ECNamedCurveTable.GetByName("secp256k1");
        var domainParams = new ECDomainParameters(curve.Curve, curve.G, curve.N,
                                                  curve.H, curve.GetSeed());

        ECPoint q = curve.Curve.DecodePoint(RawBytes);
        ECPublicKeyParameters pk = new ECPublicKeyParameters(q, domainParams);

        var signer = SignerUtilities.GetSigner("SHA-256withPLAIN-ECDSA");
        signer.Init(forSigning : false, pk);
        signer.BlockUpdate(message, 0, message.Length);
        return signer.VerifySignature(signature);
      }

      throw std::runtime_error("Unsupported key type.");
    }
  */
  /// <summary>
  /// Verifies the signature given its value and the original message.
  /// </summary>

  bool VerifySignature(std::string message, std::string signature) {
    // TODO:
    // return VerifySignature(Hex.Decode(message), Hex.Decode(signature));
    return false;
  }

  std::ostream& operator<<(std::ostream& os) {
    os << this->ToAccountHex();
    return os;
  }
};

/*
/// <summary>
/// Json converter class to serialize/deserialize a PublicKey to/from Json
/// </summary>
public
class PublicKeyConverter : JsonConverter<PublicKey> {
 public
  override PublicKey Read(ref Utf8JsonReader reader, Type typeToConvert,
                          JsonSerializerOptions options) {
    try {
      return PublicKey.FromHexString(reader.GetString());
    } catch (Exception e) {
      throw new JsonException(e.Message);
    }
  }

 public
  override void Write(Utf8JsonWriter writer, PublicKey publicKey,
                      JsonSerializerOptions options) {
    writer.WriteStringValue(publicKey.ToAccountHex());
  }
}
*/
}  // namespace Casper
