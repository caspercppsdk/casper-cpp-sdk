#pragma once

#include "Base.h"
#include "Types/CLType.h"
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
    std::string tmp_bytes = CEP57Checksum::Encode(p.bytes);
    StringUtil::toLower(tmp_bytes);
    j["bytes"] = tmp_bytes;
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
    StringUtil::toLower(hex_bytes_str);
    p.bytes = CEP57Checksum::Decode(hex_bytes_str);
  } catch (const std::exception& e) {
    std::cout << "CLValue-from_json-bytes what(): " << e.what() << std::endl;
  }

  // std::cout << j.at("parsed").dump(2) << std::endl;

  from_json(j.at("parsed"), p.parsed, p.cl_type);
}

}  // namespace Casper

namespace nlohmann {
template <typename T>
struct adl_serializer<std::map<rva::variant<T>, rva::variant<T>>> {
  static void to_json(json& j, const rva::variant<T>& var) {
    j = to_json(std::get<var.index()>(var));
  }

  static void from_json(const json& j, rva::variant<T>& var) {
    from_json(j, std::get<var.index()>(var));
  }
};
}  // namespace nlohmann

/*

namespace nlohmann {
template <typename T>
adl_serializer<std::map<Casper::CLTypeParsedRVA, T>> {
  // define to_json/from_json here
  void to_json(json & j, std::unordered_map<EC, T> const& map) {

  }
  // likewise for from_json?
}

}  // namespace nlohmann

template<typename ValueType>
struct adl_serializer {
    template<typename BasicJsonType>
    static void to_json(BasicJsonType& j, const T& value) {
        // calls the "to_json" method in T's namespace
    }

    template<typename BasicJsonType>
    static void from_json(const BasicJsonType& j, T& value) {
        // same thing, but with the "from_json" method
    }
};
*/