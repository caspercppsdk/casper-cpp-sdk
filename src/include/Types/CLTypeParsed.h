#pragma once

#include "Base.h"
#include "nlohmann/json.hpp"
#include "Types/Definitions.h"
#include "Types/GlobalStateKey.h"
#include "Types/PublicKey.h"
#include "Types/URef.h"

#include <rva/variant.hpp>
#include <tuple>

#include "Base.h"
#include <rva/variant.hpp>
#include <unordered_map>
#include <optional>
#include "magic_enum/magic_enum.hpp"
#include "nlohmann/json.hpp"

#include "Types/CLTypeParsedConverter.h"

namespace Casper {

// Helper function to compare two strings in a case insensitive way
bool iequals(const std::string& a, const std::string& b) {
  return std::equal(a.begin(), a.end(), b.begin(), b.end(),
                    [](char a, char b) { return tolower(a) == tolower(b); });
}

using CLTypeParsedRVA = rva::variant<
    bool,      // Bool, // boolean primitive
    int32_t,   // I32, // signed 32-bit integer primitive
    int64_t,   // I64, // signed 64-bit integer primitive
    uint8_t,   // U8, // unsigned 8-bit integer primitive
    uint32_t,  // U32, // unsigned 32-bit integer primitive
    uint64_t,  // U64, // unsigned 64-bit integer primitive
    big_int,   // U128, // unsigned 128-bit integer primitive

    // Unit, // singleton value without additional semantics

    std::string,  // String, // e.g. "Hello, World!"

    URef,  // URef, // unforgeable reference (see above)

    GlobalStateKey,  // Key, // global state key (see above)

    PublicKey,  // PublicKey // A Casper system PublicKey type

    //  Option(CLType), // optional value of the given type

    std::vector<rva::self_t>,  // List(CLType), Tuple1(CLType),
                               // Tuple2(CLType, CLType), Tuple3(CLType, CLType,
                               // CLType)

    // ByteArray(CLType, u32), // same as `List` above, but number
    // of elements is statically known (e.g. arrays in rust)

    std::map<std::string, rva::self_t>,  // result ok err, two elems

    std::map<rva::self_t, rva::self_t>,  //  Map(CLType, CLType), //
                                         //  key-value association
                                         //  where keys and values have
                                         //  the given types

    std::nullptr_t  // Any // Indicates the type is not known

    >;

inline void to_json(nlohmann::json& j, const CLTypeParsedRVA& p) {
  if (p.index() == 0) {
    auto& p_type = rva::get<bool>(p);
    j = boolEncode(p_type);
  } else if (p.index() == 1) {
    auto& p_type = rva::get<int32_t>(p);
    j = i32Encode(p_type);
  } else if (p.index() == 2) {
    auto& p_type = rva::get<int64_t>(p);
    j = i64Encode(p_type);
  } else if (p.index() == 3) {
    auto& p_type = rva::get<uint8_t>(p);
    j = u8Encode(p_type);
  } else if (p.index() == 4) {
    auto& p_type = rva::get<uint32_t>(p);
    j = u32Encode(p_type);
  } else if (p.index() == 5) {
    auto& p_type = rva::get<uint64_t>(p);
    j = u64Encode(p_type);
  } else if (p.index() == 6) {
    auto& p_type = rva::get<big_int>(p);
    j = p_type.toString();
  }
  // TODO:
}

inline void from_json(const nlohmann::json& j, CLTypeParsedRVA& p) {
  if (j.at("cl_type").is_string()) {
    std::cout << "CLTypeParsedRVA::from_json is string" << std::endl;
    std::string cl_type = j.at("cl_type").get<std::string>();
    std::string bytes_str = j.at("bytes").get<std::string>();

    std::cout << "bytes: " << bytes_str << std::endl;

    if (iequals(cl_type, "Bool")) {
      p = boolDecode(bytes_str);
    } else if (iequals(cl_type, "I32")) {
      p = i32Decode(bytes_str);
    } else if (iequals(cl_type, "I64")) {
      p = i64Decode(bytes_str);
    } else if (iequals(cl_type, "U8")) {
      p = u8Decode(bytes_str);
    } else if (iequals(cl_type, "U32")) {
      p = u32Decode(bytes_str);
    } else if (iequals(cl_type, "U64")) {
      p = u64Decode(bytes_str);
    } else if (iequals(cl_type, "U128")) {
      p = u512Decode(bytes_str);
    } else if (iequals(cl_type, "U256")) {
      p = u256Decode(bytes_str);
    } else if (iequals(cl_type, "U512")) {
      p = u512Decode(bytes_str);
    }
  } else {
    std::cout << "CLTypeParsedRVA::from_json is not string" << std::endl;
  }
}

struct CLTypeParsed {
  CLTypeParsedRVA parsed;
};

// to_json of CLTypeParsed
inline void to_json(nlohmann::json& j, const CLTypeParsed& p) {
  //
  to_json(j, p.parsed);
}

// from_json of CLTypeParsed
inline void from_json(const nlohmann::json& j, CLTypeParsed& p) {
  //
  j.get_to(p.parsed);
}

}  // namespace Casper
