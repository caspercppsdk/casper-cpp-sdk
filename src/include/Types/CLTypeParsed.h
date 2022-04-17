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
  } else if (p.index() == 7) {
    auto& p_type = rva::get<std::string>(p);
    j = p_type;
  } else if (p.index() == 8) {
    auto& p_type = rva::get<URef>(p);
    std::cout << "\nURef to_json\n" << std::endl;
    j = p_type.ToString();
  } else if (p.index() == 9) {
    auto p_type = rva::get<GlobalStateKey>(p);
    j = p_type.ToString();
  } else if (p.index() == 10) {
    auto p_type = rva::get<PublicKey>(p);
    j = p_type.ToString();
  } else if (p.index() == 11) {
    auto p_type = rva::get<std::vector<CLTypeParsedRVA>>(p);
    j = p_type;
  } else if (p.index() == 12) {
    auto& p_type = rva::get<std::map<std::string, CLTypeParsedRVA>>(p);
    j = p_type;
  } else if (p.index() == 13) {
    auto& p_type = rva::get<std::map<CLTypeParsedRVA, CLTypeParsedRVA>>(p);
    j = p_type;
  } else if (p.index() == 14) {
    auto& p_type = rva::get<std::nullptr_t>(p);
    j = p_type;
  }
}

inline void from_json(const nlohmann::json& j, CLTypeParsedRVA& p,
                      int ser_idx = 0) {
  std::string bytes_str = j.at("bytes").get<std::string>();

  if (j.at("cl_type").is_string()) {
    std::string cl_type = j.at("cl_type").get<std::string>();

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
    } else if (iequals(cl_type, "String")) {
      p = stringDecode(bytes_str);
    } else if (iequals(cl_type, "URef")) {
      p = urefDecode(bytes_str);
    } else if (iequals(cl_type, "Key")) {
      CryptoPP::SecByteBlock bytes = CEP57Checksum::Decode(bytes_str);
      p = GlobalStateKey::FromBytes(bytes);
    } else if (iequals(cl_type, "PublicKey")) {
      CryptoPP::SecByteBlock bytes = CEP57Checksum::Decode(bytes_str);

      p = PublicKey::FromBytes(bytes);
    } else if (iequals(cl_type, "Any") || iequals(cl_type, "Unit")) {
      p = std::nullptr_t();
    }
  } else if (j.at("cl_type").is_object()) {
    std::string cl_type = j.at("cl_type").begin().key();

    // bytes_str

    if (iequals(cl_type, "Map")) {
      std::map<CLTypeParsedRVA, CLTypeParsedRVA> map;
      uint32_t map_size =
          u32Decode(j.at("bytes").get<std::string>().substr(0, 8));
      CLTypeRVA key_type = j.at("cl_type").at("Map").at("key").get<CLTypeRVA>();
      CLTypeRVA value_type =
          j.at("cl_type").at("Map").at("value").get<CLTypeRVA>();

      nlohmann::json key_out;
      to_json(key_out, key_type);

      nlohmann::json value_out;
      to_json(value_out, value_type);
    }
    /*
    else if (iequals(cl_type, "List")) {
      p = listDecode(bytes_str);
    } else if (iequals(cl_type, "Tuple1")) {
      p = tuple1Decode(bytes_str);
    } else if (iequals(cl_type, "Tuple2")) {
      p = tuple2Decode(bytes_str);
    } else if (iequals(cl_type, "Tuple3")) {
      p = tuple3Decode(bytes_str);
    } else if (iequals(cl_type, "Map")) {
      p = mapDecode(bytes_str);
    } else if (iequals(cl_type, "Option")) {
      p = optionDecode(bytes_str);
    } else if (iequals(cl_type, "ByteArray")) {
      p = byteArrayDecode(bytes_str);
    } else if (iequals(cl_type, "Result")) {
      p = resultDecode(bytes_str);
    } else if (iequals(cl_type, "ResultOk")) {
      p = resultOkDecode(bytes_str);
    } else if (iequals(cl_type, "ResultErr")) {
      p = resultErrDecode(bytes_str);
    } else if (iequals(cl_type, "Any")) {
      p = anyDecode(bytes_str);
    }
    */
  } else {
    // TODO: check all
  }

  ////////////////////////////
  /*
    CLTypeRVA cl_type;
    // from_json(j.at("cl_type"), cl_type);

    /// Primitives
    if (cl_type.index() == 0) {
      CLTypeEnum cl_type_enum = std::get<0>(cl_type);

      if (cl_type_enum == CLTypeEnum::Bool) {
        p = boolDecode(bytes_str);
      } else if (cl_type_enum == CLTypeEnum::I32) {
        p = i32Decode(bytes_str);
      } else if (cl_type_enum == CLTypeEnum::I64) {
        p = i64Decode(bytes_str);
      } else if (cl_type_enum == CLTypeEnum::U8) {
        p = u8Decode(bytes_str);
      } else if (cl_type_enum == CLTypeEnum::U32) {
        p = u32Decode(bytes_str);
      } else if (cl_type_enum == CLTypeEnum::U64) {
        p = u64Decode(bytes_str);
      } else if (cl_type_enum == CLTypeEnum::U128) {
        p = u128Decode(bytes_str);
      } else if (cl_type_enum == CLTypeEnum::U256) {
        p = u256Decode(bytes_str);
      } else if (cl_type_enum == CLTypeEnum::U512) {
        p = u512Decode(bytes_str);
      } else if (cl_type_enum == CLTypeEnum::String) {
        p = stringDecode(bytes_str);
      }
    }
    */
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
