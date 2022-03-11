#pragma once

#include "Base.h"
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

struct CLTypeInfo {
  CLTypeEnum type;

  CLTypeInfo() {}
  CLTypeInfo(CLTypeEnum type) : type(type) {}
  CLTypeInfo(std::string str) {
    auto typeEnum = magic_enum::enum_cast<CLTypeEnum>(str);
    if (typeEnum.has_value()) {
      type = typeEnum.value();
    } else {
      throw std::runtime_error("Invalid CLTypeInfo");
    }
  }

  operator CLTypeEnum() const { return type; }
};

// to_json
inline void to_json(nlohmann::json& j, const CLTypeInfo& p) {
  j = magic_enum::enum_name(p.type);
}

// from_json
inline void from_json(const nlohmann::json& j, CLTypeInfo& p) {
  std::string type_str = j.begin().value();
  auto type_opt = magic_enum::enum_cast<CLTypeEnum>(type_str);
  if (type_opt.has_value()) {
    p.type = type_opt.value();
  } else {
    throw std::runtime_error("CLTypeInfo-from_json-type: invalid type");
  }
}

struct CLMapTypeInfo : public CLTypeInfo {
  std::string key_type;
  std::string value_type;

  CLMapTypeInfo(std::string key_type_, std::string value_type_)
      : CLTypeInfo(CLTypeEnum::Map),
        key_type(key_type_),
        value_type(value_type_) {}
  CLMapTypeInfo() : CLTypeInfo(CLTypeEnum::Map) {}
};

// to_json
inline void to_json(nlohmann::json& j, const CLMapTypeInfo& p) {
  j = nlohmann::json{{"key", p.key_type}, {"value", p.value_type}};
}

// from_json
inline void from_json(const nlohmann::json& j, CLMapTypeInfo& p) {
  p.key_type = j.at("key").get<std::string>();
  p.value_type = j.at("value").get<std::string>();
}

struct CLResultTypeInfo : public CLTypeInfo {
  std::string ok_type;
  std::string err_type;

  CLResultTypeInfo(std::string ok_type_, std::string err_type_)
      : CLTypeInfo(CLTypeEnum::Result),
        ok_type(ok_type_),
        err_type(err_type_) {}
  CLResultTypeInfo() : CLTypeInfo(CLTypeEnum::Result) {}
};

// to_json
inline void to_json(nlohmann::json& j, const CLResultTypeInfo& p) {
  j = nlohmann::json{{"ok", p.ok_type}, {"err", p.err_type}};
}

// from_json
inline void from_json(const nlohmann::json& j, CLResultTypeInfo& p) {
  p.ok_type = j.at("ok").get<std::string>();
  p.err_type = j.at("err").get<std::string>();
}

}  // namespace Casper
