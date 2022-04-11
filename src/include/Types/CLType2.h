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

// ------------------------CLOption.h---------------------- //
template <typename S>
struct CLOption {
  S value;
};

// to_json of CLOption
template <typename T>
inline void to_json(nlohmann::json& j, const CLOption<T>& type) {
  j = nlohmann::json{{"Option", type.value}};
}

// from_json of CLOption
template <typename T>
inline void from_json(const nlohmann::json& j, CLOption<T>& type) {
  j.at("Option").get_to(type.value);
}
// end of CLOption.h

// ------------------------CLMap.h---------------------- //
template <typename S, typename T>
struct CLMap {
  S key;
  T value;
};

// to_json of CLMap
template <typename S, typename T>
inline void to_json(nlohmann::json& j, const CLMap<S, T>& type) {
  j = nlohmann::json{{"key", type.key}, {"value", type.value}};
}

// from_json of CLMap
template <typename S, typename T>
inline void from_json(const nlohmann::json& j, CLMap<S, T>& type) {
  j.at("key").get_to(type.key);
  j.at("value").get_to(type.value);
}
// end of CLMap.h

using CLTypeRVA = rva::variant<CLTypeEnum, std::vector<rva::self_t>,
                               std::map<rva::self_t, rva::self_t>>;

inline void to_json(nlohmann::json& j, const CLTypeRVA& p) {
  if (p.index() == 0) {
    auto& p_type = rva::get<CLTypeEnum>(p);

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
  } else if (p.index() == 1) {
    auto& p_type = rva::get<std::vector<CLTypeRVA>>(p);
    j = {{"List", p_type.front()}};

  } else if (p.index() == 2) {
    auto& p_type = rva::get<std::map<CLTypeRVA, CLTypeRVA>>(p);
    j["Map"] = {{"key", p_type.begin()->first},
                {"value", p_type.begin()->second}};
  }
  /*
  else if (p.index() == 3) {
    auto& p_type = rva::get<std::tuple<rva::self_t>>(p);
    j = nlohmann::json{{"Tuple1", p}};
  } else if (p.index() == 4) {
    auto& p_type = rva::get<std::tuple<rva::self_t, rva::self_t>>(p);
    j = nlohmann::json{{"Tuple2", p}};
  } else if (p.index() == 5) {
    auto& p_type = rva::get<std::tuple<rva::self_t, rva::self_t, rva::self_t>>(
        p);
    j = nlohmann::json{{"Tuple3", p}};
  }
  */
}

/*

 else if (j.front().is_string()) {
    auto p_type = j.front();
    std::cout << p_type << std::endl;
    if (p_type == "List") {
      auto list = std::vector<CLTypeRVA>();
      CLTypeRVA inner;
      from_json(j.at("List"), inner);
      list.push_back(inner);
      p = list;
    } else if (p_type == "Map") {
      auto mp = std::map<CLTypeRVA, CLTypeRVA>();

      CLTypeRVA key;
      CLTypeRVA value;
      from_json(j.at("Map").at("key"), key);
      from_json(j.at("Map").at("value"), value);

      mp.insert({key, value});
      // mp[key] = value;
      p = mp;
    } else {
      std::cout << "\n\nwrong type\n\n" << std::endl << j.dump(2) << std::endl;
      throw std::runtime_error("Invalid CLType");
    }
  }

*/
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
    if (j.begin().key() == "Map") {
      auto mp = std::map<CLTypeRVA, CLTypeRVA>();

      CLTypeRVA key;
      CLTypeRVA value;
      from_json(j.at("Map").at("key"), key);
      from_json(j.at("Map").at("value"), value);

      mp.insert({key, value});
      p = mp;
    } else if (j.begin().key() == "List") {
      auto list = std::vector<CLTypeRVA>();
      CLTypeRVA inner;
      from_json(j.at("List"), inner);
      list.push_back(inner);
      p = list;
    } else {
      throw std::runtime_error("Invalid CLType");
    }
  }
  /*
   else if (j.front().is_array()) {
    auto& p_list = rva::get<std::vector<CLTypeRVA>>(p);
    p_list.push_back(CLTypeRVA{});
  } else if (j.front().is_object()) {
    auto& p_map = rva::get<std::map<CLTypeRVA, CLTypeRVA>>(p);
    p_map.insert({CLTypeRVA{}, CLTypeRVA{}});
  }
  */
}

struct CLType {
  CLTypeRVA type;
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