#pragma once
#include <cctype>
#include <iostream>
#include <vector>

#include "Types/KeyAlgo.h"
#include "Utils/CEP57Checksum.h"
#include "Utils/File.h"
#include "Utils/StringUtil.h"
#include <cryptopp/pem.h>
#include "nlohmann/json.hpp"

namespace Casper {

/// <summary>
/// A wrapper for a Public Key. Provides signature verification functionality.
/// </summary>
struct PublicKey {
  /// <summary>
  /// Byte array without the Key algorithm identifier.
  /// </summary>
  CBytes raw_bytes;
  KeyAlgo key_algorithm;

 protected:
  PublicKey(CBytes raw_bytes_, KeyAlgo key_algorithm_)
      : raw_bytes(raw_bytes_), key_algorithm(key_algorithm_) {}

 public:
  PublicKey() {}

  /// <summary>
  /// Creates a PublicKey object from an hexadecimal string (containing the
  /// Key algorithm identifier).
  /// </summary>
  static Casper::PublicKey FromHexString(const std::string& hexKey) {
    try {
      CBytes rawBytes = CEP57Checksum::Decode(hexKey.substr(2));
      if (hexKey.substr(0, 2) == "01") {
        return FromRawBytes(rawBytes, KeyAlgo::ED25519);
      } else if (hexKey.substr(0, 2) == "02") {
        return FromRawBytes(rawBytes, KeyAlgo::SECP256K1);
      } else {
        throw std::invalid_argument("Wrong public algorithm identifier.");
      }
    } catch (std::exception& e) {
      std::cerr << e.what() << std::endl;
    }
    return Casper::PublicKey();
  }

  /// <summary>
  /// Loads a PublicKey from a PEM file
  /// </summary>
  static Casper::PublicKey FromPemFile(const std::string& pemFilePath) {
    throw std::runtime_error(
        "Not implemented: static Casper::PublicKey FromPemFile(const "
        "std::string& pemFilePath)");

    try {
      CryptoPP::FileSource fs1(pemFilePath.c_str(), true);
      if (CryptoPP::PEM_GetType(fs1) == CryptoPP::PEM_EC_PUBLIC_KEY) {
        CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PublicKey publicKey;

        publicKey.Load(fs1);

        // TODOMS3: Check the false below if any error occurs
        CBytes rawBytes(
            publicKey.GetGroupParameters().GetEncodedElementSize(false));

        // TODOMS3: Check the false below if any error occurs
        publicKey.GetGroupParameters().EncodeElement(
            false, publicKey.GetPublicElement(), rawBytes);

        return PublicKey(rawBytes, KeyAlgo::SECP256K1);

      } else {
        CryptoPP::ed25519PublicKey k1;
        k1.Load(fs1);
        CBytes rawBytes(k1.GetPublicElement().MinEncodedSize());
        k1.GetPublicElement().Encode(rawBytes, rawBytes.size());
        return PublicKey(rawBytes, KeyAlgo::ED25519);
      }
    } catch (std::exception& e) {
      std::cerr << "Unsupported key format or it's not a public key PEM object."
                << std::endl;
    }
      return {};
  }

  /// <summary>
  /// Creates a PublicKey object from a byte array. First byte in the array
  /// must contain the key algorithm identifier.
  /// </summary>
  static Casper::PublicKey FromBytes(const CBytes& bytes) {
    if (bytes.empty())
      throw std::invalid_argument("Public key bytes cannot be empty.");

    unsigned char algoIdent = bytes[0];

    int expectedPublicKeySize = -1;
    std::string algo = "";

    if (algoIdent == 0x01) {
      expectedPublicKeySize = KeyAlgo::GetKeySizeInBytes(KeyAlgo::ED25519);
      algo = KeyAlgo::GetName(KeyAlgo::ED25519);
    } else if (algoIdent == 0x02) {
      expectedPublicKeySize = KeyAlgo::GetKeySizeInBytes(KeyAlgo::SECP256K1);
      algo = KeyAlgo::GetName(KeyAlgo::SECP256K1);
    } else {
      throw std::invalid_argument("Invalid key algorithm identifier.");
    }

    if (bytes.size() < expectedPublicKeySize)
      throw std::runtime_error("Wrong public key format. Expected length is " +
                               std::to_string(expectedPublicKeySize));

    CBytes rawBytes(expectedPublicKeySize - 1);

    std::copy(bytes.begin() + 1, bytes.begin() + expectedPublicKeySize,
              rawBytes.begin());

    return Casper::PublicKey(
        rawBytes, algoIdent == 0x01 ? KeyAlgo::ED25519 : KeyAlgo::SECP256K1);
  }

  /// <summary>
  /// Creates a PublicKey object from a byte array and the key algorithm
  /// identifier.
  /// </summary>
  static Casper::PublicKey FromRawBytes(const CBytes& rawBytes,
                                        KeyAlgo keyAlgo) {
    try {
      int expectedPublicKeySize = KeyAlgo::GetKeySizeInBytes(keyAlgo) - 1;
      if (rawBytes.size() != expectedPublicKeySize) {
        std::cout << "Bytes size: " << rawBytes.size() << std::endl;

        throw std::runtime_error(
            "Wrong public key format. Expected length is " +
            std::to_string(expectedPublicKeySize));
      }
    } catch (std::exception& e) {
      std::cout << e.what() << std::endl;
    }
    return Casper::PublicKey(rawBytes, keyAlgo);
  }

  /// <summary>
  /// Saves the public key to a PEM file.
  /// </summary>
  void WriteToPem(const std::string& filePath) {
    throw std::runtime_error(
        "Not implemented: void WriteToPem(const std::string& filePath)");
    // Optional TODO: Implement this

    /*
    if (File::Exists(filePath))
      throw std::runtime_error(
          "Target file already exists. Will not overwrite.\nFile: " + filePath);

        CryptoPP::ECDSA<ECP, SHA256>::PublicKey publicKey;
        publicKey.Initialize(CryptoPP::ASN1::secp256k1(), raw_bytes.begin(),
                             raw_bytes.size());

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
            ECPublicKeyParameters pk = new ECPublicKeyParameters(q,
       domainParams); writer.WriteObject(pk); return;
          }

          throw std::runtime_error("Unsupported key type.");
        }
        */
  }

  /// <summary>
  /// Returns the Account Hash associated to this Public Key.
  /// </summary>
  std::string GetAccountHash() const {
    CBytes sb;
    std::string algo_str = KeyAlgo::GetName(key_algorithm);
    CryptoPP::SecByteBlock algo_bytes =
        hexDecode(StringUtil::getStringBytesWithoutLength(algo_str));
    CBytes interm_byte(1);
    interm_byte[0] = 0;

    sb += algo_bytes;
    sb += interm_byte;
    sb += raw_bytes;

    CryptoPP::BLAKE2b bcBl2bdigest(32u);
    bcBl2bdigest.Update(sb, sb.size());
    // std::cout << "ComputeBodyHash3" << std::endl;

    CBytes hash(bcBl2bdigest.DigestSize());
    bcBl2bdigest.Final(hash);

    return "account-hash-" + CEP57Checksum::Encode(hash);
  }

  /// <summary>
  /// Returns the key as an hexadecimal string, including the key algorithm in
  /// the first position.
  /// </summary>
  std::string ToAccountHex() const {
    std::string pk_hex = "";
    if (key_algorithm == KeyAlgo::ED25519) {
      pk_hex = "01" + CEP57Checksum::Encode(raw_bytes);
    } else if (key_algorithm == KeyAlgo::SECP256K1) {
      pk_hex = "02" + CEP57Checksum::Encode(raw_bytes);
    } else {
      throw std::runtime_error("Unsupported key type.");
    }
    return pk_hex;
  }

  /// <summary>
  /// Recall ToAccountHex()
  /// </summary>
  std::string ToString() const { return ToAccountHex(); }

  /// <summary>
  /// Returns the bytes of the public key, including the Key algorithm as the
  /// first byte.
  /// </summary>
  CBytes GetBytes() {
    CBytes bytes = CBytes(raw_bytes.size() + 1);

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
  bool VerifySignature(CBytes message, CBytes signature) {
    /*
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
*/
    throw std::runtime_error("Not implemented VerifySignature()");
    throw std::runtime_error("Unsupported key type.");
  }

  /// <summary>
  /// Verifies the signature given its value and the original message.
  /// </summary>
  bool VerifySignature(std::string message, std::string signature) {
    return VerifySignature(hexDecode(message), hexDecode(signature));
  }

  /// <summary>
  /// Converts the public key to a string.
  std::ostream& operator<<(std::ostream& os) {
    os << ToAccountHex();
    return os;
  }

  bool operator<(const Casper::PublicKey& other) const {
    return ToAccountHex() < other.ToAccountHex();
  }

  bool operator==(const Casper::PublicKey& other) const {
    return ToAccountHex() == other.ToAccountHex();
  }

  bool operator!=(const Casper::PublicKey& other) const {
    return !(*this == other);
  }
};

// to_json of PublicKey
inline void to_json(nlohmann::json& j, const Casper::PublicKey& p) {
  j = p.ToAccountHex();
}

// from_json of PublicKey
inline void from_json(const nlohmann::json& j, Casper::PublicKey& p) {
  std::string pk_str = j.get<std::string>();
  p = Casper::PublicKey::FromHexString(pk_str);
}

}  // namespace Casper
