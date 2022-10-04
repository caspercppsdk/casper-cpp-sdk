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
#include <boost/variant/recursive_variant.hpp>
#include <boost/variant/get.hpp>

namespace Casper {
enum class CLTypeEnum : uint8_t {
  /// <summary>
  /// Boolean primitive.
  /// </summary>
  Bool = 0,
  /// <summary>
  /// Signed 32-bit integer primitive.
  /// </summary>
  I32 = 1,
  /// <summary>
  /// Signed 64-bit integer primitive.
  /// </summary>
  I64 = 2,
  /// <summary>
  /// Unsigned 8-bit integer primitive.
  /// </summary>
  U8 = 3,
  /// <summary>
  /// Unsigned 32-bit integer primitive.
  /// </summary>
  U32 = 4,
  /// <summary>
  /// Unsigned 64-bit integer primitive.
  /// </summary>
  U64 = 5,
  /// <summary>
  /// Unsigned 128-bit integer primitive.
  /// </summary>
  U128 = 6,
  /// <summary>
  /// Unsigned 256-bit integer primitive.
  /// </summary>
  U256 = 7,
  /// <summary>
  /// Unsigned 512-bit integer primitive.
  /// </summary>
  U512 = 8,
  /// <summary>
  /// Singleton value without additional semantics.
  /// </summary>
  Unit = 9,
  /// <summary>
  /// A string. e.g. "Hello, World!".
  /// </summary>
  String = 10,
  /// <summary>
  /// Global state key.
  /// </summary>
  Key = 11,
  /// <summary>
  /// Unforgeable reference.
  /// </summary>
  URef = 12,
  /// <summary>
  /// Optional value of the given type Option(CLType).
  /// </summary>
  Option = 13,
  /// <summary>
  /// Variable-length list of values of a single `CLType` List(CLType).
  /// </summary>
  List = 14,
  /// <summary>
  /// Fixed-length list of a single `CLType` (normally a Byte).
  /// </summary>
  ByteArray = 15,
  /// <summary>
  /// Co-product of the the given types; one variant meaning success, the other
  /// failure.
  /// </summary>
  Result = 16,
  /// <summary>
  /// Key-value association where keys and values have the given types
  /// Map(CLType, CLType).
  /// </summary>
  Map = 17,
  /// <summary>
  /// Single value of the given type Tuple1(CLType).
  /// </summary>
  Tuple1 = 18,
  /// <summary>
  /// Pair consisting of elements of the given types Tuple2(CLType, CLType).
  /// </summary>
  Tuple2 = 19,
  /// <summary>
  /// Triple consisting of elements of the given types Tuple3(CLType, CLType,
  /// CLType).
  /// </summary>
  Tuple3 = 20,
  /// <summary>
  /// Indicates the type is not known.
  /// </summary>
  Any = 21,
  /// <summary>
  /// A Public key.
  /// </summary>
  PublicKey = 22
};

using CLTypeRVA = boost::make_recursive_variant<
    CLTypeEnum,                                       // primitives
    std::vector<boost::recursive_variant_>,                         // check this
    std::map<boost::recursive_variant_, boost::recursive_variant_>,               // map
    std::map<std::string, boost::recursive_variant_>,               // opt, list,
    std::map<std::string, std::vector<boost::recursive_variant_>>,  // tuple1,t2,t3
    std::map<std::string, int32_t>                    // byte array
    >::type;

inline void to_json(nlohmann::json& j, const CLTypeRVA& p) {
  /// bool, i32, i64, u8, u32, u64, u128, u256, u512, unit, string, key, uref,
  /// any, public key
  if (p.which() == 0) 
  {
    auto& p_type = boost::get<CLTypeEnum>(p);

    // check if the enum is primitive
    if (p_type == CLTypeEnum::Bool || p_type == CLTypeEnum::I32 ||
        p_type == CLTypeEnum::I64 || p_type == CLTypeEnum::U8 ||
        p_type == CLTypeEnum::U32 || p_type == CLTypeEnum::U64 ||
        p_type == CLTypeEnum::U128 || p_type == CLTypeEnum::U256 ||
        p_type == CLTypeEnum::U512 || p_type == CLTypeEnum::Unit ||
        p_type == CLTypeEnum::String || p_type == CLTypeEnum::Key ||
        p_type == CLTypeEnum::URef || p_type == CLTypeEnum::Any ||
        p_type == CLTypeEnum::PublicKey) {
      j = magic_enum::enum_name(p_type);
    }
  }
  /// inner type - maybe delete
  else if (p.which() == 1) {
    SPDLOG_DEBUG("boost::get<std::vector<CLTypeRVA>>(p)");
    auto& p_type = boost::get<std::vector<CLTypeRVA>>(p);
    // TODO: should not be called, be careful check this.
    j = p_type;

  }
  /// map
  else if (p.which() == 2) {
    auto& p_type = boost::get<std::map<CLTypeRVA, CLTypeRVA>>(p);
    j["Map"] = {{"key", p_type.begin()->first},
                {"value", p_type.begin()->second}};
  }
  /// option, list, result
  else if (p.which() == 3) {
    auto& p_type = boost::get<std::map<std::string, CLTypeRVA>>(p);
    std::string key_type = p_type.begin()->first;

    if (key_type == "Option") {
      j = {{"Option", p_type.begin()->second}};
    } else if (key_type == "List") {
      j = {{"List", p_type.begin()->second}};
    } else if (key_type == "Result") {
      auto inner_map = boost::get<std::map<std::string, CLTypeRVA>>(p_type.begin()->second);
      nlohmann::json inner_val = {{"Ok", inner_map["Ok"]},
                                  {"Err", inner_map["Err"]}};
      j = {"Result", inner_val};
    }
  }
  /// tuple1, tuple2, tuple3
  else if (p.which() == 4) {
    auto& p_type = boost::get<std::map<std::string, std::vector<CLTypeRVA>>>(p);
    std::string key_type = p_type.begin()->first;
    /*
      "cl_type":{"Tuple1":["Bool"]}
      "cl_type":{"Tuple2":["Bool","I32"]}
      "cl_type":{"Tuple3":[{"ByteArray":3},{"ByteArray":34},"String"]}
      */
    if (key_type == "Tuple1" || key_type == "Tuple2" || key_type == "Tuple3") {
      std::vector<CLTypeRVA> inner_types;
      for (auto& inner_type : p_type.begin()->second) {
        inner_types.push_back(inner_type);
      }
      j = {{key_type, inner_types}};
    }

  } else if (p.which() == 5) {
    auto& p_type = boost::get<std::map<std::string, int32_t>>(p);
    std::string key_type = p_type.begin()->first;
    if (key_type == "ByteArray") {
      j["ByteArray"] = p_type.begin()->second;
    }
  }
}

inline void from_json(const nlohmann::json& j, CLTypeRVA& p) {
  if (j.is_string()) {
    auto p_type = j.get<std::string>();
    auto enum_opt = magic_enum::enum_cast<CLTypeEnum>(p_type);
    if (enum_opt.has_value()) {
      p = enum_opt.value();
    } else {
      throw std::runtime_error("Invalid CLType");
    }
  } else if (j.is_object()) {
    std::string key_str = j.begin().key();
    if (key_str == "Option") {
      auto option = std::map<std::string, CLTypeRVA>();
      CLTypeRVA inner;
      from_json(j.at("Option"), inner);
      option.insert({"Option", inner});
      p = option;
    } else if (key_str == "List") {
      auto list = std::map<std::string, CLTypeRVA>();
      CLTypeRVA inner;
      from_json(j.at("List"), inner);
      list.insert({"List", inner});
      p = list;
    } else if (key_str == "ByteArray") {
      std::map<std::string, int32_t> byte_array;
      int32_t inner;
      j.at("ByteArray").get_to(inner);
      byte_array["ByteArray"] = inner;
      p = byte_array;
    } else if (key_str == "Result") {
      auto result = std::map<std::string, CLTypeRVA>();
      CLTypeRVA innerOk;
      CLTypeRVA innerErr;
      from_json(j.at("Result").at("Ok"), innerOk);
      from_json(j.at("Result").at("Err"), innerErr);

      result.insert({"Ok", innerOk});
      result.insert({"Err", innerErr});
      p = result;
    } else if (key_str == "Tuple1") {
      auto tuple1 = std::map<std::string, std::vector<CLTypeRVA>>();
      auto inner_vec = std::vector<CLTypeRVA>();
      CLTypeRVA inner;
      from_json(j.at("Tuple1").at(0), inner);
      inner_vec.push_back(inner);
      tuple1.insert({"Tuple1", inner_vec});
      p = tuple1;
    } else if (key_str == "Tuple2") {
      auto tuple2 = std::map<std::string, std::vector<CLTypeRVA>>();
      auto inner_vec = std::vector<CLTypeRVA>();
      CLTypeRVA inner1;
      CLTypeRVA inner2;
      from_json(j.at("Tuple2").at(0), inner1);
      from_json(j.at("Tuple2").at(1), inner2);
      inner_vec.push_back(inner1);
      inner_vec.push_back(inner2);
      tuple2.insert({"Tuple2", inner_vec});
      p = tuple2;
    } else if (key_str == "Tuple3") {
      auto tuple3 = std::map<std::string, std::vector<CLTypeRVA>>();
      auto inner_vec = std::vector<CLTypeRVA>();
      CLTypeRVA inner1;
      CLTypeRVA inner2;
      CLTypeRVA inner3;
      from_json(j.at("Tuple3").at(0), inner1);
      from_json(j.at("Tuple3").at(1), inner2);
      from_json(j.at("Tuple3").at(2), inner3);
      inner_vec.push_back(inner1);
      inner_vec.push_back(inner2);
      inner_vec.push_back(inner3);
      tuple3.insert({"Tuple3", inner_vec});
      p = tuple3;
    } else if (key_str == "Map") {
      auto mp = std::map<CLTypeRVA, CLTypeRVA>();

      CLTypeRVA key;
      CLTypeRVA value;
      from_json(j.at("Map").at("key"), key);
      from_json(j.at("Map").at("value"), value);

      mp.insert({key, value});
      p = mp;
    } else {
      throw std::runtime_error("Invalid CLType");
    }
  } else if (j.is_array()) {
    std::cout << "arraycltype" << std::endl;
    auto inner_vec = std::vector<CLTypeRVA>();
    for (auto& inner : j) {
      CLTypeRVA inner_val;
      from_json(inner, inner_val);
      inner_vec.push_back(inner_val);
    }
    p = inner_vec;
  }
}

struct CLType {
  CLTypeRVA type;
  // TODO: ADD TAG
  CLType() : type(CLTypeEnum::Any) {}
  CLType(CLTypeRVA type) : type(type) {}

  // TODO: Make functions like CLValue u512, u256, u128, u64, u32, u16, u8, etc.
  bool operator<(const CLType& b) const;

  CLType(int32_t byte_array_size) {
    std::map<std::string, int32_t> byte_array;
    byte_array["ByteArray"] = byte_array_size;
    type = byte_array;
  }

  CLType(CLTypeRVA type_, CLTypeEnum tag) {
    std::map<std::string, CLTypeRVA> list_map;
    CLTypeRVA obj_type;

    switch (tag) {
      case CLTypeEnum::List:
        std::cout << "list cltype switch" << std::endl;
        obj_type = type_;
        list_map["List"] = obj_type;
        type = list_map;
        std::cout << "list cltype switch end" << std::endl;
        break;

      default:
        std::cout << "Invalid Tag" << std::endl;
        throw std::runtime_error("Invalid CLType");
    }
  }

  CLType(std::optional<CLTypeRVA>& option) {
    std::map<std::string, CLTypeRVA> option_map;
    option_map["Option"] = option.value();
    type = option_map;
  }

  CLType(CLTypeRVA ok, CLTypeRVA err, CLTypeEnum tag) {
    if (tag != CLTypeEnum::Result) {
      throw std::runtime_error("Invalid CLType");
    }
    std::map<std::string, CLTypeRVA> result_map;

    result_map["Ok"] = ok;
    result_map["Err"] = err;

    std::map<std::string, CLTypeRVA> res_mp;
    res_mp["Result"] = result_map;
    type = res_mp;
    }


};

// to_json of CLType
inline void to_json(nlohmann::json& j, const CLType& p) {
  //
  to_json(j, p.type);
}

// from_json of CLType
inline void from_json(const nlohmann::json& j, CLType& p) {
  //
  j.get_to(p.type);
}

}  // namespace Casper