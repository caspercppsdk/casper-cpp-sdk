#pragma once

#include <optional>
#include <tuple>
#include <unordered_map>
#include <spdlog/spdlog.h>

#include "Base.h"
#include "CLType.h"
#include "Types/CLConverter.h"
#include "Types/GlobalStateKey.h"
#include "Types/PublicKey.h"
#include "Types/URef.h"
#include "magic_enum/magic_enum.hpp"
#include "nlohmann/json.hpp"
#include "rva/variant.hpp"
#include <boost/variant/get.hpp>

namespace Casper {

using CLTypeParsedRVA = boost::make_recursive_variant<
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

    std::vector<boost::recursive_variant_>,  // 13 List(CLType), Tuple1(CLType),
                               // Tuple2(CLType, CLType), Tuple3(CLType, CLType,
                               // CLType)

    // ByteArray(CLType, u32), // same as `List` above, but number
    // of elements is statically known (e.g. arrays in rust)

    std::map<std::string, boost::recursive_variant_>,  // 14 result ok err, two elems

    std::map<boost::recursive_variant_, boost::recursive_variant_>,  //  15 Map(CLType, CLType), //
                                         //  key-value association
                                         //  where keys and values have
                                         //  the given types

    std::monostate  // 16 Any // Indicates the type is not known

    >::type;

inline void to_json(nlohmann::json& j, const CLTypeParsedRVA& p) {
  if (p.which() == 0) {
    auto& p_type = boost::get<bool>(p);
    j = p_type;
  } else if (p.which() == 1) {
    auto& p_type = boost::get<int32_t>(p);
    j = p_type;
  } else if (p.which() == 2) {
    auto& p_type = boost::get<int64_t>(p);
    j = p_type;
  } else if (p.which() == 3) {
    auto& p_type = boost::get<uint8_t>(p);
    j = p_type;
  } else if (p.which() == 4) {
    auto& p_type = boost::get<uint32_t>(p);
    j = p_type;
  } else if (p.which() == 5) {
    auto& p_type = boost::get<uint64_t>(p);
    j = p_type;
  } else if (p.which() == 6) {
    auto p_type = boost::get<uint128_t>(p);
    j = p_type;
  } else if (p.which() == 7) {
    auto p_type = boost::get<uint256_t>(p);
    j = p_type;
  } else if (p.which() == 8) {
    auto p_type = boost::get<uint512_t>(p);
    j = p_type;
  } else if (p.which() == 9) {
    auto& p_type = boost::get<std::string>(p);
    j = p_type;
  } else if (p.which() == 10) {
    auto& p_type = boost::get<URef>(p);
    std::cout << "\nURef to_json\n" << std::endl;
    j = p_type.ToString();
  } else if (p.which() == 11) {
    auto p_type = boost::get<GlobalStateKey>(p);
    std::string key_identifier{magic_enum::enum_name(p_type.key_identifier)};

    // URef does not have a key_identifier as an enum in parsed
    if (iequals(key_identifier, "URef")) {
      j = p_type.ToString();
    } else {
      j[key_identifier] = p_type.ToString();
    }

  } else if (p.which() == 12) {
    auto p_type = boost::get<PublicKey>(p);
    j = p_type.ToString();
  } else if (p.which() == 13) {
    auto p_type = boost::get<std::vector<CLTypeParsedRVA>>(p);
    j = p_type;
  } else if (p.which() == 14) {
    auto& p_type = boost::get<std::map<std::string, CLTypeParsedRVA>>(p);
    j = p_type;
  } else if (p.which() == 15) {
    auto& p_type = boost::get<std::map<CLTypeParsedRVA, CLTypeParsedRVA>>(p);

    int i = 0;
    for (auto& [key, value] : p_type) {
      j[i++] = {{"key", key}, {"value", value}};
    }

    // j = p_type;
  } else if (p.which() == 16) {
    j = nullptr;
  }
}

inline void from_json(const nlohmann::json& j, CLTypeParsedRVA& p,
                      CLType& cl_type_) {
  // std::cout << "from_json, idx: " << p.which() << std::endl;
  bool is_primitive = false;
  if (cl_type_.type.which() == 0) {
    is_primitive = true;
  }

  if (is_primitive) {
    // std::cout << "enum: "
    //           << magic_enum::enum_name(boost::get<CLTypeEnum>(cl_type_.type))
    //           << std::endl;
    switch (boost::get<CLTypeEnum>(cl_type_.type)) {
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
        p = std::monostate{};
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
      default:
        SPDLOG_ERROR("Unsupported type in json");
        break;
    }
  } else if (cl_type_.type.which() == 1) {
    // vector<CLTypeRVA>
    // std::cout << "\nvector<CLTypeRVA> from_json\n" << std::endl;
  } else if (cl_type_.type.which() == 2) {
    // Map(CLType, CLType)
    auto parsed_map = std::map<CLTypeParsedRVA, CLTypeParsedRVA>();

    if (j.is_array()) {
      // Multiple key-value pairs
      for (auto& item : j) {
        CLType key_type;
        key_type.type = boost::get<std::map<CLTypeRVA, CLTypeRVA>>(cl_type_.type)
                            .begin()
                            ->first;

        CLType value_type;
        value_type.type =
            boost::get<std::map<CLTypeRVA, CLTypeRVA>>(cl_type_.type)
                .begin()
                ->second;

        CLTypeParsedRVA key_parsed = item.at("key").get<CLTypeParsedRVA>();
        CLTypeParsedRVA value_parsed = item.at("value").get<CLTypeParsedRVA>();

        parsed_map.insert({key_parsed, value_parsed});
      }

      p = parsed_map;
    } else {
      // Single key-value pair
      CLType key_type;
      key_type.type = boost::get<std::map<CLTypeRVA, CLTypeRVA>>(cl_type_.type)
                          .begin()
                          ->first;

      CLType value_type;
      value_type.type = boost::get<std::map<CLTypeRVA, CLTypeRVA>>(cl_type_.type)
                            .begin()
                            ->second;

      CLTypeParsedRVA key_parsed;
      CLTypeParsedRVA value_parsed;

      key_parsed = j.at("key").get<CLTypeParsedRVA>();
      value_parsed = j.at("value").get<CLTypeParsedRVA>();

      parsed_map[key_parsed] = value_parsed;
      p = parsed_map;
    }

  } else if (cl_type_.type.which() == 3) {
    std::cout << "\nCLTypeRVA from_json 3\n" << std::endl;
    /// option, list, result

    auto obj = boost::get<std::map<std::string, CLTypeRVA>>(cl_type_.type);

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
        parsed_obj = std::monostate{};
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
      CLTypeParsedRVA parsed_ok;
      CLTypeParsedRVA parsed_err;

      // types
      CLType ok_type;
      ok_type.type = obj.at("Ok");

      CLType err_type;
      err_type.type = obj.at("Err");

      std::string bytes_parsed = j.at("bytes").get<std::string>();

      if (bytes_parsed.substr(0, 2) == "00") {
        // Err
        from_json(j.at("Err"), parsed_err, err_type);
        p = parsed_err;
      } else if (bytes_parsed.substr(0, 2) == "01") {
        // Ok
        from_json(j.at("Ok"), parsed_ok, ok_type);
        p = parsed_ok;
      } else {
        throw std::runtime_error("Invalid Result Ok/Err!");
      }

    } else {
      SPDLOG_ERROR("Unknown type");
      // TODO: Check this case, maybe error
    }
  }
  // Tuple1, Tuple2, and Tuple3
  else if (cl_type_.type.which() == 4) {
    std::vector<CLTypeParsedRVA> parsed_list;

    auto inner_types =
        boost::get<std::map<std::string, std::vector<CLTypeRVA>>>(cl_type_.type)
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
  else if (cl_type_.type.which() == 5) {
    p = j.get<std::string>();
  }

  else {
    SPDLOG_ERROR("ERROR CLTypeRVA from_json 4");
  }

  ////////////////////////////
}

struct CLTypeParsed {
  CLTypeParsedRVA parsed;

  CLTypeParsed() : parsed(std::monostate{}) {}

  CLTypeParsed(CLTypeParsedRVA parsed) : parsed(parsed) {}

  bool operator<(const CLTypeParsed& b) const;
  bool operator<(CLTypeParsed&& b) const;
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
