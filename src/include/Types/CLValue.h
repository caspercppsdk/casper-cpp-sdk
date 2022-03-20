#pragma once

#include "Base.h"
#include "Types/CLType.h"
#include "cryptopp/secblock.h"

#include "Utils/CEP57Checksum.h"
#include "nlohmann/json.hpp"

namespace Casper {
struct CLValue {
  CLType cl_type;
  SecByteBlock bytes;

  // TODO: object parsed;

  CLValue() {}
};
// to json
inline void to_json(nlohmann::json& j, const CLValue& p) {
  j = nlohmann::json{};

  j["cl_type"] = p.cl_type;

  try {
    j["bytes"] = CEP57Checksum::Encode(p.bytes);
  } catch (const std::exception& e) {
    std::cout << "CLValue-to_json-bytes what(): " << e.what() << std::endl;
  }

  // TODO: parsed
}

// from json
inline void from_json(const nlohmann::json& j, CLValue& p) {
  j.at("cl_type").get_to(p.cl_type);

  try {
    std::string hex_bytes_str = j.at("bytes").get<std::string>();
    p.bytes = CEP57Checksum::Decode(hex_bytes_str);
  } catch (const std::exception& e) {
    std::cout << "CLValue-from_json-bytes what(): " << e.what() << std::endl;
  }

  // TODO: parsed}
}
}  // namespace Casper
