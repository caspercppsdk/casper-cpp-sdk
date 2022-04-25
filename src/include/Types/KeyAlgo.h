#pragma once
#include <stdexcept>
// TODOMS3: Make the stdexcept a global in the project
#include <iostream>

namespace Casper {
class KeyAlgo {
 public:
  enum Value : uint8_t { ED25519 = 1, SECP256K1 = 2 };

  KeyAlgo() = default;
  constexpr KeyAlgo(Value aKeyAlgo) : value(aKeyAlgo) {}

  // Allow switch and comparisons.
  constexpr operator Value() const { return value; }

  // Prevent usage: if(keyAlgo)
  explicit operator bool() = delete;
  constexpr bool operator==(KeyAlgo a) const { return value == a.value; }
  constexpr bool operator==(Value a) const { return value == a; }
  constexpr bool operator!=(KeyAlgo a) const { return value != a.value; }

  constexpr static int GetKeySizeInBytes(Value value) {
    if (value == Value::ED25519) {
      return 33;
    } else if (value == Value::SECP256K1) {
      return 34;
    } else {
      throw std::invalid_argument("Wrong key algorithm type");
    }
  }

  static std::string GetName(Value value) {
    if (value == Value::ED25519) {
      return "ed25519";
    } else if (value == Value::SECP256K1) {
      return "secp256k1";
    } else {
      throw std::invalid_argument("Wrong key algorithm type");
    }
  }

 private:
  Value value;
};
}  // namespace Casper
