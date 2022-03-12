#pragma once

#include <tuple>

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

struct CLOptionTypeInfo : public CLTypeInfo {
  std::string option_type;

  CLOptionTypeInfo(std::string option_type_)
      : CLTypeInfo(CLTypeEnum::Option), option_type(option_type_) {}
  CLOptionTypeInfo() : CLTypeInfo(CLTypeEnum::Option) {}
};

// to_json
inline void to_json(nlohmann::json& j, const CLOptionTypeInfo& p) {
  j = nlohmann::json{{p.option_type}};
}

// from_json
inline void from_json(const nlohmann::json& j, CLOptionTypeInfo& p) {
  p.option_type = j.get<std::string>();
}

struct CLListTypeInfo : public CLTypeInfo {
  std::string list_type;

  CLListTypeInfo(std::string list_type_)
      : CLTypeInfo(CLTypeEnum::List), list_type(list_type_) {}
  CLListTypeInfo() : CLTypeInfo(CLTypeEnum::List) {}
};

// to_json
inline void to_json(nlohmann::json& j, const CLListTypeInfo& p) {
  j = nlohmann::json{{p.list_type}};
}

// from_json
inline void from_json(const nlohmann::json& j, CLListTypeInfo& p) {
  p.list_type = j.get<std::string>();
}

struct CLByteArrayTypeInfo : public CLTypeInfo {
  int size;

  CLByteArrayTypeInfo(int size_)
      : CLTypeInfo(CLTypeEnum::ByteArray), size(size_) {}
  CLByteArrayTypeInfo() : CLTypeInfo(CLTypeEnum::ByteArray) {}
};

// to_json
inline void to_json(nlohmann::json& j, const CLByteArrayTypeInfo& p) {
  j = nlohmann::json{{p.size}};
}

// from_json
inline void from_json(const nlohmann::json& j, CLByteArrayTypeInfo& p) {
  p.size = j.get<uint32_t>();
}

struct CLTuple1TypeInfo : public CLTypeInfo {
  std::string type0;

  CLTuple1TypeInfo(std::string type0_)
      : CLTypeInfo(CLTypeEnum::Tuple1), type0(type0_) {}
  CLTuple1TypeInfo() : CLTypeInfo(CLTypeEnum::Tuple1) {}
};

// to_json
inline void to_json(nlohmann::json& j, const CLTuple1TypeInfo& p) {
  j = nlohmann::json{{p.type0}};
}

// from_json
inline void from_json(const nlohmann::json& j, CLTuple1TypeInfo& p) {
  p.type0 = j.get<std::string>();
}

struct CLTuple2TypeInfo : public CLTypeInfo {
  std::string type0;
  std::string type1;

  CLTuple2TypeInfo(std::string type0_, std::string type1_)
      : CLTypeInfo(CLTypeEnum::Tuple2), type0(type0_), type1(type1_) {}
  CLTuple2TypeInfo() : CLTypeInfo(CLTypeEnum::Tuple2) {}
};

// to_json
inline void to_json(nlohmann::json& j, const CLTuple2TypeInfo& p) {
  j = nlohmann::json{{p.type0}, {p.type1}};
}

// from_json
inline void from_json(const nlohmann::json& j, CLTuple2TypeInfo& p) {
  p.type0 = j[0].get<std::string>();
  p.type1 = j[1].get<std::string>();
}

struct CLTuple3TypeInfo : public CLTypeInfo {
  std::string type0;
  std::string type1;
  std::string type2;

  CLTuple3TypeInfo(std::string type0_, std::string type1_, std::string type2_)
      : CLTypeInfo(CLTypeEnum::Tuple3),
        type0(type0_),
        type1(type1_),
        type2(type2_) {}
  CLTuple3TypeInfo() : CLTypeInfo(CLTypeEnum::Tuple3) {}
};

// to_json
inline void to_json(nlohmann::json& j, const CLTuple3TypeInfo& p) {
  j = nlohmann::json{{p.type0}, {p.type1}, {p.type2}};
}

// from_json
inline void from_json(const nlohmann::json& j, CLTuple3TypeInfo& p) {
  p.type0 = j[0].get<std::string>();
  p.type1 = j[1].get<std::string>();
  p.type2 = j[2].get<std::string>();
}

}  // namespace Casper
