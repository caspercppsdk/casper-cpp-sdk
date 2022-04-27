#pragma once

#include "Base.h"
#include "nlohmann/json.hpp"
#include "Types/GlobalStateKey.h"
#include "Types/PublicKey.h"
#include "Types/URef.h"

#include "rva/variant.hpp"
#include <tuple>

#include <unordered_map>
#include <optional>
#include "magic_enum/magic_enum.hpp"

#include "Types/CLConverter.h"

namespace Casper {

using CLTypeParsedRVA = rva::variant<
    bool,       // 0 Bool, // boolean primitive
    int32_t,    // 1 I32, // signed 32-bit integer primitive
    int64_t,    // 2 I64, // signed 64-bit integer primitive
    uint8_t,    // 3 U8, // unsigned 8-bit integer primitive
    uint32_t,   // 4 U32, // unsigned 32-bit integer primitive
    uint64_t,   // 5 U64, // unsigned 64-bit integer primitive
    uint128_t,  // 6 U128, // unsigned 128-bit integer primitive
    uint256_t,  // 7 U256, // unsigned 256-bit integer primitive
    uint512_t,  // 8 U512, // unsigned 512-bit integer primitive
    // Unit, // singleton value without additional semantics

    std::string,  // 9 String, // e.g. "Hello, World!"

    URef,  // 10 URef, // unforgeable reference (see above)

    GlobalStateKey,  // 11 Key, // global state key (see above)

    PublicKey,  // 12 PublicKey // A Casper system PublicKey type

    //  Option(CLType), // optional value of the given type

    std::vector<rva::self_t>,  // 13 List(CLType), Tuple1(CLType),
                               // Tuple2(CLType, CLType), Tuple3(CLType, CLType,
                               // CLType)

    // ByteArray(CLType, u32), // same as `List` above, but number
    // of elements is statically known (e.g. arrays in rust)

    std::map<std::string, rva::self_t>,  // 14 result ok err, two elems

    std::map<rva::self_t, rva::self_t>,  //  15 Map(CLType, CLType), //
                                         //  key-value association
                                         //  where keys and values have
                                         //  the given types

    std::nullptr_t  // 16 Any // Indicates the type is not known

    >;

inline void to_json(nlohmann::json& j, const CLTypeParsedRVA& p) {
  if (p.index() == 0) {
    auto& p_type = rva::get<bool>(p);
    j = p_type;
  } else if (p.index() == 1) {
    auto& p_type = rva::get<int32_t>(p);
    j = p_type;
  } else if (p.index() == 2) {
    auto& p_type = rva::get<int64_t>(p);
    j = p_type;
  } else if (p.index() == 3) {
    auto& p_type = rva::get<uint8_t>(p);
    j = p_type;
  } else if (p.index() == 4) {
    auto& p_type = rva::get<uint32_t>(p);
    j = p_type;
  } else if (p.index() == 5) {
    auto& p_type = rva::get<uint64_t>(p);
    j = p_type;
  } else if (p.index() == 6) {
    auto p_type = rva::get<uint128_t>(p);
    j = p_type;
  } else if (p.index() == 7) {
    auto p_type = rva::get<uint256_t>(p);
    j = p_type;
  } else if (p.index() == 8) {
    auto p_type = rva::get<uint512_t>(p);
    j = p_type;
  } else if (p.index() == 9) {
    auto& p_type = rva::get<std::string>(p);
    j = p_type;
  } else if (p.index() == 10) {
    auto& p_type = rva::get<URef>(p);
    std::cout << "\nURef to_json\n" << std::endl;
    j = p_type.ToString();
  } else if (p.index() == 11) {
    auto p_type = rva::get<GlobalStateKey>(p);
    std::string key_identifier{magic_enum::enum_name(p_type.key_identifier)};

    // URef does not have a key_identifier as an enum in parsed
    if (iequals(key_identifier, "URef")) {
      j = p_type.ToString();
    } else {
      j[key_identifier] = p_type.ToString();
    }

  } else if (p.index() == 12) {
    auto p_type = rva::get<PublicKey>(p);
    j = p_type.ToString();
  } else if (p.index() == 13) {
    auto p_type = rva::get<std::vector<CLTypeParsedRVA>>(p);
    j = p_type;
  } else if (p.index() == 14) {
    auto& p_type = rva::get<std::map<std::string, CLTypeParsedRVA>>(p);
    j = p_type;
  } else if (p.index() == 15) {
    auto& p_type = rva::get<std::map<CLTypeParsedRVA, CLTypeParsedRVA>>(p);

    int i = 0;
    for (auto& [key, value] : p_type) {
      j[i++] = {{"key", key}, {"value", value}};
    }

    // j = p_type;
  } else if (p.index() == 16) {
    auto& p_type = rva::get<std::nullptr_t>(p);
    j = p_type;
  }
}

inline void from_json(const nlohmann::json& j, CLTypeParsedRVA& p,
                      CLType& cl_type_) {
  // std::cout << "from_json, idx: " << p.index() << std::endl;
  bool is_primitive = false;
  if (cl_type_.type.index() == 0) {
    is_primitive = true;
  }

  if (is_primitive) {
    // std::cout << "enum: "
    //           << magic_enum::enum_name(rva::get<CLTypeEnum>(cl_type_.type))
    //           << std::endl;
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
        p = u128FromDec(j.get<std::string>());
        break;
      case CLTypeEnum::U256:
        p = u256FromDec(j.get<std::string>());
        break;
      case CLTypeEnum::U512:
        p = u512FromDec(j.get<std::string>());
        break;
      case CLTypeEnum::Unit:
      case CLTypeEnum::Any:
        p = std::nullptr_t();
        break;
      case CLTypeEnum::String:
        p = j.get<std::string>();
        break;
      case CLTypeEnum::URef:  // compare with a CLTypeEnum::URef examle
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
    // std::cout << "\nvector<CLTypeRVA> from_json\n" << std::endl;
  } else if (cl_type_.type.index() == 2) {
    // Map(CLType, CLType)
    auto parsed_map = std::map<CLTypeParsedRVA, CLTypeParsedRVA>();

    if (j.is_array()) {
      // Multiple key-value pairs
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
      // Single key-value pair
      CLType key_type;
      key_type.type = std::get<std::map<CLTypeRVA, CLTypeRVA>>(cl_type_.type)
                          .begin()
                          ->first;

      CLType value_type;
      value_type.type = std::get<std::map<CLTypeRVA, CLTypeRVA>>(cl_type_.type)
                            .begin()
                            ->second;

      CLTypeParsedRVA key_parsed;
      CLTypeParsedRVA value_parsed;

      key_parsed = j.at("key").get<CLTypeParsedRVA>();
      value_parsed = j.at("value").get<CLTypeParsedRVA>();

      parsed_map[key_parsed] = value_parsed;
      p = parsed_map;
    }

  } else if (cl_type_.type.index() == 3) {
    std::cout << "\nCLTypeRVA from_json 3\n" << std::endl;
    /// option, list, result

    auto obj = std::get<std::map<std::string, CLTypeRVA>>(cl_type_.type);

    // Type of the current object
    std::string type_name = obj.begin()->first;

    // Type of the object's value to be parsed inside the from_json below
    CLType inner_type;
    inner_type.type = obj.begin()->second;

    // object to be parsed below
    CLTypeParsedRVA parsed_obj;

    // Option parsing
    if (type_name == "Option") {
      // parse with inner type
      if (j.is_null()) {
        parsed_obj = std::nullptr_t();
      } else {
        from_json(j, parsed_obj, inner_type);
      }

      // assign parsed value to option
      p = parsed_obj;

    }
    // List parsing
    else if (type_name == "List") {
      std::vector<CLTypeParsedRVA> parsed_list;

      // parse with inner type
      for (auto& item : j) {
        CLTypeParsedRVA parsed_item;
        from_json(item, parsed_item, inner_type);
        parsed_list.push_back(parsed_item);
      }

      // assign parsed value to list
      p = parsed_list;

    }
    // Result Parsing
    // Result is a map with two keys: Ok and Err
    else if (type_name == "Result") {
      // TODO: implement result parsing

    } else {
      std::cout << "Unknown type\n" << std::endl;
      // TODO: Check this case, maybe error
    }
  }
  // Tuple1, Tuple2, and Tuple3
  else if (cl_type_.type.index() == 4) {
    std::vector<CLTypeParsedRVA> parsed_list;

    auto inner_types =
        std::get<std::map<std::string, std::vector<CLTypeRVA>>>(cl_type_.type)
            .begin()
            ->second;

    CLType inner_type;

    uint8_t tuple_idx = 0;
    for (auto& item : j) {
      CLTypeParsedRVA parsed_item;
      inner_type.type = inner_types[tuple_idx++];
      from_json(item, parsed_item, inner_type);
      parsed_list.push_back(parsed_item);
    }

    p = parsed_list;

  }
  // ByteArray
  else if (cl_type_.type.index() == 5) {
    p = j.get<std::string>();
  }

  else {
    std::cout << "\nERROR CLTypeRVA from_json 4\n" << std::endl;
  }

  ////////////////////////////
}

struct CLTypeParsed {
  CLTypeParsedRVA parsed;

  CLTypeParsed() : parsed(std::nullptr_t()) {}

  CLTypeParsed(CLTypeParsedRVA parsed) : parsed(parsed) {}
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
