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

    int i = 0;
    for (auto& [key, value] : p_type) {
      j[i++] = {{"key", key}, {"value", value}};
    }

    // j = p_type;
  } else if (p.index() == 14) {
    auto& p_type = rva::get<std::nullptr_t>(p);
    j = p_type;
  }
}

inline void from_json(const nlohmann::json& j, CLTypeParsedRVA& p,
                      CLType& cl_type_) {
  bool is_primitive = false;
  if (cl_type_.type.index() == 0) {
    is_primitive = true;
  }
  std::cout << "\nstart from_json\n" << std::endl;
  if (is_primitive) {
    std::cout << "\nprimitive from_json\n" << std::endl;
    switch (rva::get<CLTypeEnum>(cl_type_.type)) {
      case CLTypeEnum::Bool:
        p = j.get<bool>();
        break;

      case CLTypeEnum::I32:
        p = j.get<int32_t>();
        break;

      case CLTypeEnum::I64:
        p = j.get<int64_t>();
        break;

      case CLTypeEnum::U8:
        p = j.get<uint8_t>();
        break;

      case CLTypeEnum::U32:
        p = j.get<uint32_t>();
        break;

      case CLTypeEnum::U64:
        p = j.get<uint64_t>();
        break;

      case CLTypeEnum::U128:
      case CLTypeEnum::U256:
      case CLTypeEnum::U512:
        p = big_int(j.get<std::string>());
        break;

      case CLTypeEnum::Unit:
        p = std::nullptr_t();
        break;

      case CLTypeEnum::String:
        p = j.get<std::string>();
        break;

      case CLTypeEnum::URef:
        p = URef::FromString(j.get<std::string>());
        break;

      case CLTypeEnum::Key:
        p = GlobalStateKey::FromString(j.begin().value().get<std::string>());
        break;

      case CLTypeEnum::PublicKey:
        p = PublicKey::FromHexString(j.get<std::string>());
        break;
    }
  } else if (cl_type_.type.index() == 1) {
    // vector<CLTypeRVA>
    std::cout << "\nvector<CLTypeRVA> from_json\n" << std::endl;
  } else if (cl_type_.type.index() == 2) {
    std::cout << "\nstd::map<CLTypeRVA, CLTypeRVA> from_json\n" << std::endl;

    auto parsed_map = std::map<CLTypeParsedRVA, CLTypeParsedRVA>();

    if (j.is_array()) {
      for (auto& item : j) {
        CLType key_type;
        key_type.type = std::get<std::map<CLTypeRVA, CLTypeRVA>>(cl_type_.type)
                            .begin()
                            ->first;

        CLType value_type;
        value_type.type =
            std::get<std::map<CLTypeRVA, CLTypeRVA>>(cl_type_.type)
                .begin()
                ->second;

        CLTypeParsedRVA key_parsed;
        CLTypeParsedRVA value_parsed;

        key_parsed = item.at("key").get<CLTypeParsedRVA>();
        value_parsed = item.at("value").get<CLTypeParsedRVA>();

        parsed_map[key_parsed] = value_parsed;
      }

      p = parsed_map;
    } else {
      // TODO: CHECK COPILOT
      // auto& p_type = rva::get<std::map<CLTypeParsedRVA, CLTypeParsedRVA>>(p);
      // j.get_to(p_type);
    }

    /*
        if (iequals(cl_type, "Map")) {
          std::map<CLTypeParsedRVA, CLTypeParsedRVA> map;
          uint32_t map_size =
              u32Decode(j.at("bytes").get<std::string>().substr(0, 8));
          CLTypeRVA key_type =
       j.at("cl_type").at("Map").at("key").get<CLTypeRVA>(); CLTypeRVA
       value_type = j.at("cl_type").at("Map").at("value").get<CLTypeRVA>();

          nlohmann::json key_out;
          to_json(key_out, key_type);

          nlohmann::json value_out;
          to_json(value_out, value_type);
        }


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
    std::cout << "\nCLTypeRVA from_json\n" << std::endl;
    // TODO: check all
  }

  std::cout << "\nend from_json\n" << std::endl;
  ////////////////////////////
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
inline void from_json(const nlohmann::json& j, CLTypeParsed& p,
                      CLType& cl_type) {
  from_json(j, p.parsed, cl_type);
}

}  // namespace Casper
