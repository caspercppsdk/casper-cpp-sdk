#pragma once
#include <string>
#include <vector>

#include "Types/KeyAlgo.h"
#include "Utils/File.h"
#include "nlohmann/json.hpp"

namespace Casper {
struct PublicKey {
  std::vector<std::byte> raw_bytes;
  KeyAlgo key_algorithm;

 protected:
  PublicKey(std::vector<std::byte> raw_bytes_, KeyAlgo key_algorithm_)
      : raw_bytes(raw_bytes_), key_algorithm(key_algorithm_) {}

 public:
  /// <summary>
  /// Creates a PublicKey object from an hexadecimal string (containing the
  /// Key algorithm identifier).
  /// </summary>
  static PublicKey FromHexString(const std::string& hexBytes) {
    var rawBytes =
        CEP57Checksum.Decode(hexBytes.substr(2), out var checksumResult);

    if (checksumResult == CEP57Checksum.InvalidChecksum)
      throw std::invalid_argument("Public key checksum mismatch.");

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
        return new PublicKey(compressed, KeyAlgo.SECP256K1);
      }

      throw new ArgumentException(
          "Unsupported key format or it's not a private key PEM object.",
          nameof(filePath));
    }
  }

  /// <summary>
  /// Creates a PublicKey object from a byte array. First byte in the array must
  /// contain the key algorithm identifier.
  /// </summary>
  static PublicKey FromBytes(const std::vector<std::byte>& bytes) {
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

    std::vector<std::byte> rawBytes =
        std::vector<std::byte>(expectedPublicKeySize - 1);

    std::copy(bytes.begin() + 1, bytes.begin() + expectedPublicKeySize,
              rawBytes.begin());

    return PublicKey(rawBytes,
                     algoIdent == 0x01 ? KeyAlgo::ED25519 : KeyAlgo::SECP256K1);
  }

  /// <summary>
  /// Creates a PublicKey object from a byte array and the key algorithm
  /// identifier.
  /// </summary>
  static PublicKey FromRawBytes(const std::vector<std::byte>& rawBytes,
                                KeyAlgo keyAlgo) {
    try {
      int expectedPublicKeySize = KeyAlgo::GetKeySizeInBytes(keyAlgo) - 1;
      if (rawBytes.size() != expectedPublicKeySize) {
        throw std::runtime_error(
            "Wrong public key format. Expected length is " +
            std::to_string(expectedPublicKeySize));
      }
    } catch (std::exception& e) {
      throw new std::exception(e.what());
    }

    return PublicKey(rawBytes, keyAlgo);
  }

  /// <summary>
  /// Saves the public key to a PEM file.
  /// </summary>

  void WriteToPem(const std::string& filePath) {
    if (File::Exists(filePath))
      throw std::runtime_error(
          "Target file already exists. Will not overwrite.\nFile: " + filePath);

    using(var textWriter = File.CreateText(filePath)) {
      var writer = new PemWriter(textWriter);

      if (key_algorithm == KeyAlgo.ED25519) {
        Ed25519PublicKeyParameters pk =
            new Ed25519PublicKeyParameters(RawBytes, 0);
        writer.WriteObject(pk);
        return;
      } else if (key_algorithm == KeyAlgo.SECP256K1) {
        var curve = ECNamedCurveTable.GetByName("secp256k1");
        var domainParams = new ECDomainParameters(curve.Curve, curve.G, curve.N,
                                                  curve.H, curve.GetSeed());

        ECPoint q = curve.Curve.DecodePoint(RawBytes);
        ECPublicKeyParameters pk = new ECPublicKeyParameters(q, domainParams);
        writer.WriteObject(pk);
        return;
      }

      throw std::runtime_error("Unsupported key type.");
    }
  }

  /// <summary>
  /// Returns the Account Hash associated to this Public Key.
  /// </summary>
  std::string GetAccountHash() {
    var bcBl2bdigest = new Org.BouncyCastle.Crypto.Digests.Blake2bDigest(256);
    std::string algo = key_algorithm.ToString().ToLower();
    bcBl2bdigest.BlockUpdate(System.Text.Encoding.UTF8.GetBytes(algo), 0,
                             algo.Length);
    bcBl2bdigest.Update(0x00);
    bcBl2bdigest.BlockUpdate(RawBytes, 0, RawBytes.Length);

    var hash = new byte[bcBl2bdigest.GetDigestSize()];
    bcBl2bdigest.DoFinal(hash, 0);

    return "account-hash-" + CEP57Checksum.Encode(hash);
  }

  /// <summary>
  /// Returns the key as an hexadecimal string, including the key algorithm in
  /// the first position.
  /// </summary>

  std::string ToAccountHex() {
    look todo here

        if (key_algorithm == KeyAlgo::ED25519) {
      return "01" + Hex.ToHexString(
                        RawBytes);  // TODO: CEP57Checksum.Encode(RawBytes);
                                    // instead of hex.tohexstring
    }
    else if (key_algorithm == KeyAlgo::SECP256K1) {
      return "02" + Hex.ToHexString(
                        RawBytes);  // TODO: CEP57Checksum.Encode(RawBytes);
                                    // instead of hex.tohexstring
    }
    else {
      throw std::runtime_error("Unsupported key type.");
    }
  }

 public
  override string ToString() { return ToAccountHex(); }

 public
  override bool Equals(object obj) {
    // Check for null and compare run-time types.
    if (obj == null || !GetType().Equals(obj.GetType())) return false;

    var pk = (PublicKey)obj;
    return pk.GetBytes().SequenceEqual(this.GetBytes());
  }

 public
  override int GetHashCode() {
    return this.ToAccountHex().ToLower().GetHashCode();
  }

  /// <summary>
  /// Returns the bytes of the public key, including the Key algorithm as the
  /// first byte.
  /// </summary>
 public
  byte[] GetBytes() {
    byte[] bytes = new byte[1 + RawBytes.Length];
    bytes[0] = KeyAlgorithm switch {KeyAlgo.ED25519 = > 0x01,
                                    KeyAlgo.SECP256K1 = > 0x02, _ = > 0x00};
    Array.Copy(RawBytes, 0, bytes, 1, RawBytes.Length);

    return bytes;
  }

  /// <summary>
  /// Verifies the signature given its value and the original message.
  /// </summary>
 public
  bool VerifySignature(byte[] message, byte[] signature) {
    if (KeyAlgorithm == KeyAlgo.ED25519) {
      Ed25519PublicKeyParameters edPk =
          new Ed25519PublicKeyParameters(RawBytes, 0);
      return Ed25519.Verify(signature, 0, RawBytes, 0, message, 0,
                            message.Length);
    }

    if (KeyAlgorithm == KeyAlgo.SECP256K1) {
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

    throw new Exception("Unsupported key type.");
  }

  /// <summary>
  /// Verifies the signature given its value and the original message.
  /// </summary>
 public
  bool VerifySignature(string message, string signature) {
    return VerifySignature(Hex.Decode(message), Hex.Decode(signature));
  }

#region Cast operators

 public
  static explicit operator string(PublicKey pk) = > pk.ToAccountHex();

#endregion
};

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

}  // namespace Casper
