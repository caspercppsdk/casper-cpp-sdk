#pragma once

#include "Base.h"
#include "Types/CLType2.h"
#include "Types/CLTypeParsed.h"
#include "cryptopp/secblock.h"

#include "Utils/CEP57Checksum.h"
#include "nlohmann/json.hpp"

namespace Casper {

/// A Casper value, i.e. a value which can be stored and manipulated by smart
/// contracts.
///
/// It holds the underlying data as a type-erased, serialized `Vec<u8>` and also
/// holds the [`CLType`] of the underlying data as a separate member.
struct CLValue {
  CLType cl_type;
  SecByteBlock bytes;

  CLTypeParsed parsed;

  CLValue() {}
};
// to json
inline void to_json(nlohmann::json& j, const CLValue& p) {
  j = nlohmann::json{};

  to_json(j["cl_type"], p.cl_type);

  try {
    j["bytes"] = CEP57Checksum::Encode(p.bytes);
  } catch (const std::exception& e) {
    std::cout << "CLValue-to_json-bytes what(): " << e.what() << std::endl;
  }

  to_json(j["parsed"], p.parsed);
}

// from json
inline void from_json(const nlohmann::json& j, CLValue& p) {
  from_json(j.at("cl_type"), p.cl_type);

  try {
    std::string hex_bytes_str = j.at("bytes").get<std::string>();
    p.bytes = CEP57Checksum::Decode(hex_bytes_str);
  } catch (const std::exception& e) {
    std::cout << "CLValue-from_json-bytes what(): " << e.what() << std::endl;
  }

  from_json(j, p.parsed);
}

}  // namespace Casper
